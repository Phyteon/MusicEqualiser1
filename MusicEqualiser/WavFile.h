#pragma once
#include <vector>
#include <string>
#include "SFML/Audio.hpp"
#include <iostream>
#include <complex>
#include <valarray>
#include <iomanip>
#include <cmath>
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class WavFile
{
protected:
	std::vector<sf::Int16> samples; // Filled with LoadWaveFile function
	std::vector<double> d_samples; // Filled with LoadWaveFile function
	CArray c_samples; // Filled with LoadWaveFile function
	sf::SoundBuffer buffer;
	sf::Music music;
	CArray FFT(sf::Int16); // Does computations on c_samples, may alter c_samples length (zero-padding)
	CArray IFFT(sf::Int16, CArray&);
	std::vector<sf::Int16> CastOnInt16(CArray&);
public:
	void LoadWaveFile(std::string);
	void ChangeAmplitude(sf::Int16);
	void PitchUp();
	void TestFunction();
	void SaveWaveFile(std::string);
	WavFile();
	~WavFile();
};

