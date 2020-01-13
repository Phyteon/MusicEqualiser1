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
	std::vector<sf::Int16> samples;
	std::vector<double> d_samples;
	sf::SoundBuffer buffer;
	sf::Music music;
	std::vector<double> FFT(sf::Int16);
public:
	void LoadWaveFile(std::string);
	void ChangeAmplitude(sf::Int16);
	void PitchUp();
	void SaveWaveFile(std::string);
	WavFile();
	~WavFile();
};

