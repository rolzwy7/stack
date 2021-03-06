close all; clc; clear;

prawdo_bledu = 0.75;

%%% Text
%%%%%%%%%%%%
[bin_vec, char_len] = textTransmit('text/text01.txt');
% Zakłócenie - start
[inter, n_err, N] = interference(prawdo_bledu, size(bin_vec));
fprintf('[*] Text  - BER: %.3f%%\n', (n_err/N)*100);
bin_vec = xor( bin_vec, inter );
% Zakłócenie - stop
content_text = textReceive('wyniki/text_result.txt', bin_vec, char_len);

%%% Image
%%%%%%%%%%%%
[bin_vec, image_size] = imageTransmit('image/lena.png');
% Zakłócenie - start
[inter, n_err, N] = interference(prawdo_bledu, size(bin_vec));
fprintf('[*] Image - BER: %.3f%%\n', (n_err/N)*100);
bin_vec = xor( bin_vec, inter );
bin_vec = uint8(bin_vec);
% Zakłócenie - stop
img = imageReceive('wyniki/image_result.png', bin_vec, image_size);
imshow(uint8(img));

%%% Audio
%%%%%%%%%%%%
[ bin_vec, fs, info ] = audioTransmit('audio/audio01.wav');
% Zakłócenie - start
[inter, n_err, N] = interference(prawdo_bledu, size(bin_vec));
fprintf('[*] Audio - BER: %.3f%%\n', (n_err/N)*100);
bin_vec = xor( bin_vec, inter );
% Zakłócenie - stop
audio = audioReceive( 'wyniki/audio_result.wav', bin_vec, fs, info );
