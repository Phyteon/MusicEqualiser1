#include "stdafx.h"
#include "WavFile.h"


CArray fft(std::vector<double> &data)
{
	CArray x;
	x.resize(data.size());
	for (size_t i = 0; i < data.size(); i++)
	{
		x[i]=(std::complex<double>)data[i];
	}
	// DFT
	unsigned int N = x.size(), k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
	while (k > 1)
	{
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (unsigned int l = 0; l < k; l++)
		{
			for (unsigned int a = l; a < N; a += n)
			{
				unsigned int b = a + k;
				Complex t = x[a] - x[b];
				x[a] += x[b];
				x[b] = t * T;
			}
			T *= phiT;
		}
	}
	// Decimate
	unsigned int m = (unsigned int)log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			Complex t = x[a];
			x[a] = x[b];
			x[b] = t;
		}
	}
	return x;
}

std::vector<sf::Int16> WavFile::FFT(sf::Int16 NoOfSmplInChunk)
{
	if (d_samples.size()%NoOfSmplInChunk != 0)
	{
		while (d_samples.size() % NoOfSmplInChunk != 0)
		{
			d_samples.push_back(0.0);
		}
	}
	// #TODO
	return std::vector<sf::Int16>();
}

void WavFile::LoadWaveFile(std::string path)
{
	if (!this->buffer.loadFromFile(path))
	{
		// Error handle
	}
	const sf::Int16 *temp = this->buffer.getSamples();
	for (size_t i = 0; i < this->buffer.getSampleCount(); i++)
	{
		this->samples.push_back(temp[i]);
		this->d_samples.push_back((double)temp[i]);
	}

}

void WavFile::ChangeAmplitude(sf::Int16 coeff)
{
	if (coeff == 0)
	{
		// Error handle
	}
	for (size_t i = 0; i < this->samples.size(); i++)
	{
		samples[i] = samples[i] / coeff;
	}
	this->buffer.loadFromSamples(&samples[0], samples.size(), 2, 44100);
}

void WavFile::PitchUp()
{

}

void WavFile::SaveWaveFile(std::string path)
{
	try
	{
		this->buffer.saveToFile(path);
	}
	catch(...)
	{
		std::cout << "File cannot be saved to this location\n"; // Messages should be displayed in GUI
	}
}

WavFile::WavFile()
{
}


WavFile::~WavFile()
{
}
