
#include "stdafx.h"
#include "MusicEqualiser.h"
#include "WavFile.h"
#include <iostream>
int main()
{
	WavFile test_file;
	std::string path1 = "C:\\Users\\pawel\\Desktop\\Rak.wav";
	std::string path2 = "C:\\Users\\pawel\\Desktop\\RakRak3.wav";
	// std::cout << "Please specify the path of the target file:\n";
	// getline(std::cin, path);
	test_file.LoadWaveFile(path1);
	// std::cout << "Please specify the path where you want to save the file:\n";
	// getline(std::cin, path);
	test_file.PitchDown(256, 200);
	test_file.SaveWaveFile(path2);

	return 0;
}