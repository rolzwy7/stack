#include <iostream>
#include <ctime>
#include "activation.h"
#include "cnn.h"
#include "cnn_schema.h"
#include "cnn_dataset.h"
#include "argparse.h"

int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Polish");
	using math::collections::Matrix;
	using neural::ConvolutionalNeuralNetwork;
	using neural::CNNSchemaGenerator;
	using neural::CNNDataset;
	using std::string;
	using std::vector;
	using std::cout;
	using std::endl;

	std::string msg;
	bool success;

	// Argument Parser
	using argparse::ArgumentParser;
	ArgumentParser parser(
		"Projekt - Sieć neuronowa\nauthor: Bartosz Nowakowski II rok III semestr Teleinformatyka",
		argc,
		argv
	);
	parser.add_argument("schema", "Path to neural network schema", argparse::tString, argparse::iPositional);
	parser.add_argument("epochs","Number of training epochs", argparse::tInt, argparse::iOptional);
	parser.add_argument("train-file", "Path to training file", argparse::tString, argparse::iOptional);
	parser.add_argument("eval-file", "Path to evaluation file", argparse::tString, argparse::iOptional);
	parser.add_argument("learning-rate", "Learning rate (double)", argparse::tDouble, argparse::iOptional);
	parser.add_argument("train", "Start training", argparse::tStoreTrue, argparse::iOptional);
	parser.add_argument("train-verbose", "Start training (verbose mode)", argparse::tStoreTrue, argparse::iOptional);
	parser.add_argument("eval-only", "Evaluate evaluation file", argparse::tStoreTrue, argparse::iOptional);
	parser.add_argument("save", "Save trained network schema to file", argparse::tString, argparse::iOptional);
	parser.add_argument("no-bias-update","Don't update biases while training", argparse::tStoreTrue, argparse::iOptional);
	parser.add_argument("generate-schema", "Prints schema file basing on provided schema code", argparse::tString, argparse::iOptional, argparse::dDrop);
	if (!parser.parse_args(argc, argv))
		return 1;

	// Assign positional arguments
	string schema;
	bool schema_set = parser.get_arg("schema", schema);

	// Assign optional arguments
	int epochs = 0;
	double learning_rate = 0.0;
	bool train = false;
	bool train_verbose = false;
	bool eval_only = false;
	string save("");
	bool no_bias_update = false;
	string generate_schema;
	string train_file("");
	string eval_file("");

	bool epochs_set			 = parser.get_arg("epochs", epochs);
	bool lr_set				 = parser.get_arg("learning-rate", learning_rate);
	bool train_set			 = parser.get_arg("train", train);
	bool train_verbose_set	 = parser.get_arg("train-verbose", train_verbose);
	bool eval_only_set		 = parser.get_arg("eval-only", eval_only);
	bool save_set		     = parser.get_arg("save", save);
	bool no_bias_update_set	 = parser.get_arg("no-bias-update", no_bias_update);
	bool generate_schema_set = parser.get_arg("generate-schema", generate_schema);

	bool train_file_set = parser.get_arg("train-file", train_file);
	bool eval_file_set = parser.get_arg("eval-file", eval_file);

	// debug: print argparse maps
	if (train_verbose) {
		parser.print_maps();
		cout << endl << endl;
	}


	// training vars
	int epochs_print_step = (int)(epochs / 10);
	double epochs_double = (double)epochs;
	double total_error = 0.0;

	// Generate schema (drop positional)
	if(generate_schema_set) {
		CNNSchemaGenerator cnn_schema_generator(generate_schema);
		if (!cnn_schema_generator.generate()) {
			cout << "[-] Couldn't generate schema. Exiting." << endl;
		}
		return 0;
	}

	// Construct neural network
	int layers;
	vector<int>    hidden_r;	   hidden_r.reserve(50);
	vector<int>    hidden_c;	   hidden_c.reserve(50);
	vector<double> hidden_weights; hidden_weights.reserve(1000);
	vector<double> hidden_biases;  hidden_biases.reserve(1000);

	neural::CNNSchemaFile cnn_schema(schema);

	if (!cnn_schema.load(msg)) {
		cout << msg << endl;
		return 2;
	}

	bool is_schema_valid = cnn_schema.validate(msg, layers, hidden_r, hidden_c, hidden_weights, hidden_biases);

	if (!is_schema_valid) {
		cout << msg << endl;
		cout << "[-] Schema invalid. Exiting." << endl;
		return 2;
	}

	ConvolutionalNeuralNetwork cnn_network(layers, learning_rate);
	cnn_network.bias_update = (no_bias_update == true) ? false : true;

	// Resize matrices: weights and biases
	for (unsigned int it = 0; it < hidden_r.size()-1; ++it) {
		cnn_network.weights[it].resize(hidden_r.at(it), hidden_c.at(it), 0);
		cnn_network.biases[it].resize(1, hidden_c.at(it), 0);
	}
	// Populate weights & biases values
	int offset_w = 0, offset_b = 0;
	for (unsigned int it = 0; it < hidden_r.size() - 1; ++it) {
		for (int it_b = 0; it_b < hidden_c.at(it); ++it_b) {
			cnn_network.biases[it].matrix[0 * hidden_c.at(it) + it_b] = hidden_biases[offset_b++];
		}
		for (int it_r = 0; it_r < hidden_r.at(it);++it_r) {
			for (int it_c = 0; it_c < hidden_c.at(it); ++it_c) {
				cnn_network.weights[it].matrix[it_r * hidden_c.at(it) + it_c] = hidden_weights[offset_w++];
			}
		}
	}
	// Transpose biases & weights
	for (unsigned int it = 0; it < cnn_network.layers; ++it) {
		cnn_network.biases[it].transpose();
	}
	for (unsigned int it = 0; it < cnn_network.layers; ++it) {
		cnn_network.weights[it].transpose();
	}

	// Train neural network
	if (train || train_verbose || eval_only) {
		if (!eval_only) {
			if (!epochs_set) {
				cout << "[-] 'epochs' optional parameter is mandatory with --train flag" << endl;
				return 21;
			}
			if ((epochs < 100) || (epochs % 100 != 0)) {
				cout << "[-] 'epochs' parameter must be >=100 and epochs % 100 == 0" << endl;
				return 21;
			}
			if (!lr_set) {
				cout << "[-] 'learning-rate' optional parameter is mandatory with --train flag" << endl;
				return 21;
			}
			if (learning_rate <= 0 || learning_rate >= 1) {
				cout << "[-] 'learning-rate' parameter must be in range (0;1)" << endl;
				return 21;
			}
			if (!train_file_set) {
				cout << "[-] 'train-file' optional parameter is mandatory with --train flag" << endl;
				return 21;
			}
			if (!eval_file_set) {
				cout << "[-] 'eval-file' optional parameter is mandatory with --train flag" << endl;
				return 21;
			}
		} else {
			if (!eval_file_set) {
				cout << "[-] 'eval-file' optional parameter is mandatory with --eval-only flag" << endl;
				return 21;
			}
			epochs_set = true;
			epochs = -1;
			lr_set = true;
			learning_rate = 0;
		}
	} else {
		cout << "[*] If you want to train loaded network you need to set --train or --train-verbose flag at the end of console arguments" << endl;
		cout << "[*] If you want to only evaluate network --eval-only at the end of console arguments" << endl;
		cout << "Mandatory arguments for training:" << endl;
		cout << " > epochs" << endl;
		cout << " > learning-rate" << endl;
		cout << " > train-file" << endl;
		cout << " > eval-file" << endl;
		return 0;
	}

	cout << "- Inputs         : " << cnn_schema.inputs << endl;
	cout << "- Outputs        : " << cnn_schema.outputs << endl;
	cout << "- Training       : " << (( (train || train_verbose) && !eval_only ) ? "Yes" : "No\n");
	if (!eval_only) {
		if (train_verbose)
			cout << " (Verbose)" << endl;
		else
			cout << endl;
		cout << "- Bias update    : " << ((cnn_network.bias_update) ? "Yes" : "No") << endl;
		cout << "- Epochs         : " << epochs << endl;
		cout << "- Learning rate  : " << learning_rate << endl << endl;
	}

	// debug: print netowork before training
	if (train_verbose) cnn_network.print_details();

	// Training file - validate
	CNNDataset training_file(train_file, cnn_schema.inputs + cnn_schema.outputs);
	std::vector<double> training_data_vec;  training_data_vec.reserve(4000);
	success = training_file.validate(msg, training_data_vec);
	if (!eval_only) {
		cout << msg << endl;
		if (!success) {
			return 2;
		};
		cout << "[*] Detected: " << training_file.datalines << " data lines in training file" << endl;
	}
	// Evaluation file - validate
	CNNDataset evaluation_file(eval_file, cnn_schema.inputs + cnn_schema.outputs);
	std::vector<double> eval_data_vec;  eval_data_vec.reserve(4000);
	success = evaluation_file.validate(msg, eval_data_vec);
	cout << msg << endl;
	if (!success) {
		return 2;
	};
	cout << "[*] Detected: " << evaluation_file.datalines << " data lines in evaluation file" << endl;

	// Training
	Matrix * inputs = new Matrix[training_file.datalines];
	Matrix * ideals = new Matrix[training_file.datalines];

	neural::populate_matrices(inputs, ideals, training_file.datalines, cnn_schema.inputs, cnn_schema.outputs, training_data_vec);
	training_data_vec.clear();

	#ifndef _DEBUG
		double duration = 0;
		clock_t start = std::clock();
	#endif // !_DEBUG

	for (int it = 0; it < epochs + 1; ++it) {
		for (int training_data_it = 0; training_data_it < training_file.datalines; ++training_data_it)
			total_error = cnn_network.train(inputs[training_data_it], ideals[training_data_it]);
		if (it % epochs_print_step == 0) 
			cout << ((it) / epochs_double) * 100 << "% | total error: " << total_error << " (it=" << it << ")" << endl;
	}

	#ifndef _DEBUG
			clock_t end = std::clock();
			duration = ((double)(end - start)) / CLOCKS_PER_SEC;
			cout << "[*] Training duration: " << duration << " s" << endl << endl;
	#endif // !_DEBUG

	// debug: print netowrk after training
	if (train_verbose) cnn_network.print_details();
	
	delete[] inputs;
	delete[] ideals;

	// Evaluation
	inputs = new Matrix[evaluation_file.datalines];
	ideals = new Matrix[evaluation_file.datalines];

	neural::populate_matrices(inputs, ideals, evaluation_file.datalines, cnn_schema.inputs, cnn_schema.outputs, eval_data_vec);
	eval_data_vec.clear();

	int guessed_correct = 0;
	math::collections::Matrix feedforward_output;
	string sign = "";
	for (int eval_data_it = 0; eval_data_it < evaluation_file.datalines; ++eval_data_it) {
		cnn_network.feedforward(inputs[eval_data_it], feedforward_output);

		int ideals_max_idx = 0;
		int guess_max_idx = 0;
		double guess_max = feedforward_output.matrix[0];
		double ideals_max = ideals[eval_data_it].matrix[0];
		for (int it = 1; it < cnn_schema.outputs; ++it) {
			if (ideals[eval_data_it].matrix[it] > ideals_max) {
				ideals_max = ideals[eval_data_it].matrix[it];
				ideals_max_idx = it;
			}
			if (feedforward_output.matrix[it] > guess_max) {
				guess_max = feedforward_output.matrix[it];
				guess_max_idx = it;
			}
		}
		if (ideals_max_idx == guess_max_idx) {
			sign = " == ";
			++guessed_correct;
		}
		else {
			sign = " != ";
		}

		// debug: print evaluation details
		if (train_verbose || eval_only) {
			cout << eval_data_it << " - Result: " << feedforward_output.transpose() << sign << ideals[eval_data_it].transpose() << endl;
		}
		
	}

	cout << "[+] Guessed correct: " << guessed_correct << "/" << evaluation_file.datalines << " "
		<< ((double)guessed_correct/(double)evaluation_file.datalines)*100.0 << "%" << endl;

	if (save_set && !eval_only) {
		cnn_network.save(save, msg);
		cout << msg << endl;
	}

	delete[] inputs;
	delete[] ideals;

	return 0;
}
