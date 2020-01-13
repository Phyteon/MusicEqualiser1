#pragma once
#include <vector>
#include <string>
#include "SFML/Audio.hpp"
#include <iostream>
#include <complex>
#include <valarray>
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class WavFile
{
protected:
	std::vector<sf::Int16> samples; // Filled with LoadWaveFile function
	std::vector<double> d_samples; // Filled with LoadWaveFile function
	sf::SoundBuffer buffer;
	sf::Music music;
	CArray FFT(sf::Int16); // Does computations on d_samples, may alter d_samples length (zero-padding)
	std::vector<sf::Int16> CastOnInt16(CArray&);
public:
	void LoadWaveFile(std::string);
	void ChangeAmplitude(sf::Int16);
	void PitchUp();
	void SaveWaveFile(std::string);
	WavFile();
	~WavFile();
};

