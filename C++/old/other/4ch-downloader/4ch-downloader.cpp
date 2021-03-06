#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "cpr/cpr.h"
#include "argparse/argparse.h"
#include "nlohmann/json.hpp"

using std::cout;
using std::endl;
using std::string;

#ifdef _DEBUG
	#define debug_log(msg, end) cout << msg << end;
#else
	#define debug_log(msg, end)
#endif

string getAPIUrl(const string& board, const string& thread_number) {
	return "https://a.4cdn.org/" + board + "/thread/" + thread_number + ".json";
}

string getResourceWebpath(const string& board, const string& resource) {
	return "http://is2.4chan.org/" + board + "/" + resource;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Polish");
	// Argument parser
	argparse::ArgumentParser parser("4chan downloader");
	string board = "board";
	string thread_number = "thread";
	parser.add_argument(board, "help", argparse::tString);
	parser.add_argument(thread_number, "help", argparse::tString);

	if (!parser.parse_args(argc, argv))
		return 1;
	else {
		parser.get_str(board, board);
		parser.get_str(thread_number, thread_number);
	}
	cout << "[*] Requesting thread: " << board << "/" << thread_number << endl;
	auto request = cpr::Get(cpr::Url(getAPIUrl(board, thread_number)));
	debug_log("Request status code: ", "");
	debug_log(request.status_code, "\n");

	if (request.status_code != 200) {
		cout << "[-] Thread no longer exists" << endl;
		return 3;
	}
	cout << "[+] Thread found" << endl;

	auto deserialized = nlohmann::json::parse(request.text);

	string filename;
	string out_string;
	std::stringstream ss;
	std::vector<string> vposts;
	auto posts = deserialized["posts"];
	for (unsigned int i = 0; i < posts.size();++i) {

		if (
			!posts[i]["tim"].empty()
			&& posts[i]["tim"].is_number()
			&& !posts[i]["filename"].empty()
			&& !posts[i]["ext"].empty()
		) {
			ss << posts[i]["tim"].get<long long>();
			out_string = ss.str();
			filename = out_string + posts[i]["ext"].get<string>();
			debug_log("post image: ", "");
			debug_log(getResourceWebpath(board, filename), "\n");
			vposts.push_back(filename);
			ss.str("");
		}

		continue;
		
		
	}

	debug_log("Appended posts: ", "");
	debug_log(vposts.size(), "\n");
	cout << "[+] Found " << vposts.size() << " images" << endl;


	// create directory
	string str_dirname = "tmp_directory";
	LPCWSTR lpcwstr_dirname = L"tmp_directory";
	CreateDirectory(lpcwstr_dirname, NULL);
	
	// Create file
	std::fstream file;
	int streamsize;
	string decoration[4] = {"-", "\\", "|", "/"};
	for (unsigned int i = 0; i < vposts.size(); ++i) {

		cout << "\r " << decoration[i%4] << " Downloading: " << vposts[i] << "\t\t";

		debug_log("downloading image: ", "");
		debug_log(getResourceWebpath(board, vposts[i]), "\n");
		auto image_request = cpr::Get(cpr::Url(getResourceWebpath(board, vposts[i])));
		debug_log("Request status code: ", "");
		debug_log(image_request.status_code, "\n");
		debug_log("Request content length: ", "");
		debug_log(image_request.header["content-length"], "\n");
		streamsize = stoi(image_request.header["content-length"]);
		filename = str_dirname + "\\" + vposts[i];
		file.open(filename.c_str(), std::ios::out | std::ios::binary);
		if (file.good()) {
			file.write(image_request.text.c_str(), streamsize);
		}
		file.close();
	}
	cout << "\n";

    return 0;
}

