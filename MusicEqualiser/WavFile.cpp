#include "stdafx.h"
#include "WavFile.h"

CArray fft(CArray &x)
{
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

CArray ifft(CArray& x)
{
	// conjugate the complex numbers
	x = x.apply(std::conj);

	// forward fft
	fft(x);

	// conjugate the complex numbers again
	x = x.apply(std::conj);

	// scale the numbers
	x /= x.size();

	return x;
}

CArray WavFile::FFT(sf::Int16 NoOfSmplInChunk)
{
	if (this->c_samples.size()%NoOfSmplInChunk != 0) // Zero-padding to decrease computation time and increase resolution
	{
		// Error in zero padding
		size_t append = this->c_samples.size() % NoOfSmplInChunk;
		size_t previous_size = this->c_samples.size();
		CArray auxilary(this->c_samples);
		// Saving content of c_samples beacuse resize operation assigns zeros everywhere
		// Unhandled exception in MusicEqualiser.exe: Microsoft C++ exception: std::bad_alloc - occurs when operating on large files
		// Code needs memory optimisation
		this->c_samples.resize(previous_size + NoOfSmplInChunk - append);
		for (size_t k = 0; k < previous_size; k++)
			this->c_samples[k] = auxilary[k];
	}
	size_t smpl_arr_size = c_samples.size();

	CArray result;
	CArray temp;
	temp.resize(NoOfSmplInChunk);
	result.resize(smpl_arr_size);
	size_t index = 0;
	try
	{
		for (size_t j = 0; j < smpl_arr_size / NoOfSmplInChunk; j++)
		{
			for (size_t f = j * NoOfSmplInChunk; f < (j + 1)*NoOfSmplInChunk; f++)
			{
				temp[index] = this->c_samples[f];
				index++;
			}
			index = 0;
			fft(temp); // FFT calculation of one chunk
			for (size_t k = j * NoOfSmplInChunk; k < (j + 1)*NoOfSmplInChunk; k++)
			{
				result[k] = temp[index]; // Assigning calculation of one chunk to the result CArray
				index++;
			}
			index = 0;
		}
	}
	catch (std::bad_alloc)
	{
		std::cout << "Too much memory required\n";
		throw std::exception();
	}
	
	return result;
}

CArray WavFile::IFFT(sf::Int16 NoOfSmplInChunk, CArray& fourier) // Only to be performed on product of FFT function
{
	CArray result;
	CArray temp;
	temp.resize(NoOfSmplInChunk);
	result.resize(fourier.size());
	size_t index = 0;
	for (size_t j = 0; j < fourier.size() / NoOfSmplInChunk; j++)
	{
		for (size_t f = j * NoOfSmplInChunk; f < (j + 1)*NoOfSmplInChunk; f++)
		{
			temp[index] = fourier[f];
			index++;
		}
		index = 0;
		ifft(temp); // Inverse FFT calculation of a chunk
		for (size_t k = j * NoOfSmplInChunk; k < (j + 1)*NoOfSmplInChunk; k++)
		{
			result[k] = temp[index];
			index++;
		}
		index = 0;
	}
	return result;
}

std::vector<sf::Int16> WavFile::CastOnInt16(CArray & _CArray)
{
	std::vector<sf::Int16> cast;
	double temp;
	for (size_t i = 0; i < _CArray.size(); i++)
	{
		temp = real(_CArray[i]); // Is such approximation good?
		if (temp > (pow(2, 15) - 1) || temp < -pow(2, 15))
			temp = (abs(temp) / temp) * (pow(2, 15) - 1);
		cast.push_back((sf::Int16)temp); // Casting directly onto Int16 or first onto int and then Int16?
	}
	return cast;
}

void WavFile::LoadWaveFile(std::string path)
{
	if (!this->buffer.loadFromFile(path))
	{
		std::cout << "Unable to open file\n";
		throw std::exception();
	}
	size_t dim = (size_t)this->buffer.getSampleCount();
	this->c_samples.resize(dim);
	const sf::Int16 *temp = this->buffer.getSamples();
	try
	{
		for (size_t i = 0; i < dim; i++)
		{
			this->samples.push_back(temp[i]);
			this->d_samples.push_back((double)temp[i]);
			//this->c_samples[i] = (std::complex<double>)(double)temp[i]; // Casting twice, prone to errors
			// Unhandled exception at 0x763D19B2 in MusicEqualiser.exe: Microsoft C++ exception: std::bad_alloc at memory location 0x00AFED6C. occurred
		}
		for (size_t i = 0; i < dim; i++)
		{
			this->c_samples[i] = (std::complex<double>)d_samples[i];
			//this->c_samples[i] = (std::complex<double>)(double)temp[i]; // Casting twice, prone to errors
			// Unhandled exception at 0x763D19B2 in MusicEqualiser.exe: Microsoft C++ exception: std::bad_alloc at memory location 0x00AFED6C. occurred
		}
	}
	catch (std::bad_alloc)
	{
		std::cout << "File already exists or is opened: std::bad_alloc\n";
		throw std::exception();
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

void WavFile::PitchUp(sf::Int16 NoOfSmplInChunk, sf::Int16 FreqShift)
{
	size_t fourier_shift = (size_t)std::floor(FreqShift / (44100/NoOfSmplInChunk)); // Calculating how many positions to shift the frequency domain
	CArray fourier_domain = this->FFT(NoOfSmplInChunk);
	CArray temp;
	CArray shift;
	shift.resize(NoOfSmplInChunk);
	temp.resize(NoOfSmplInChunk);
	size_t index = 0;
	for (size_t j = 0; j < fourier_domain.size() / NoOfSmplInChunk; j++)
	{
		for (size_t f = j * NoOfSmplInChunk; f < (j + 1)*NoOfSmplInChunk; f++)
		{
			temp[index] = fourier_domain[f];
			index++;
		}
		index = 0;
		for (size_t k = fourier_shift; k < (size_t)NoOfSmplInChunk/2; k++)
		{
			shift[k] = temp[index];
			index++;
		}
		index = NoOfSmplInChunk/2;
		for (size_t k = (size_t)NoOfSmplInChunk/2 ; k < (size_t)NoOfSmplInChunk - fourier_shift; k++)
		{
			shift[k] = temp[index + fourier_shift];
			index++;
		}
		index = 0;
		for (size_t l = j * NoOfSmplInChunk; l < (j + 1)*NoOfSmplInChunk; l++)
		{
			fourier_domain[l] = shift[index];
			index++;
		}
		index = 0;
	}
	CArray time_domain;
	time_domain = this->IFFT(NoOfSmplInChunk, fourier_domain);
	std::vector<sf::Int16> new_sample = this->CastOnInt16(time_domain);
	this->buffer.loadFromSamples(&new_sample[0], new_sample.size(), 2, 44100);
}

void WavFile::PitchDown(sf::Int16 NoOfSmplInChunk, sf::Int16 FreqShift)
{
	size_t fourier_shift = (size_t)std::floor(FreqShift / (44100 / NoOfSmplInChunk)); // Calculating how many positions to shift the frequency domain
	CArray fourier_domain = this->FFT(NoOfSmplInChunk);
	CArray temp;
	CArray shift;
	shift.resize(NoOfSmplInChunk);
	temp.resize(NoOfSmplInChunk);
	size_t index = 0;
	for (size_t j = 0; j < fourier_domain.size() / NoOfSmplInChunk; j++)
	{
		for (size_t f = j * NoOfSmplInChunk; f < (j + 1)*NoOfSmplInChunk; f++)
		{
			temp[index] = fourier_domain[f];
			index++;
		}
		index = 0;
		for (size_t k = fourier_shift; k < (size_t)NoOfSmplInChunk / 2; k++)
		{
			shift[index] = temp[k];
			index++;
		}
		index = NoOfSmplInChunk / 2;
		for (size_t k = (size_t)NoOfSmplInChunk / 2; k < (size_t)NoOfSmplInChunk - fourier_shift; k++)
		{
			shift[index + fourier_shift] = temp[k];
			index++;
		}
		index = 0;
		for (size_t l = j * NoOfSmplInChunk; l < (j + 1)*NoOfSmplInChunk; l++)
		{
			fourier_domain[l] = shift[index];
			index++;
		}
		index = 0;
	}
	CArray time_domain;
	time_domain = this->IFFT(NoOfSmplInChunk, fourier_domain);
	std::vector<sf::Int16> new_sample = this->CastOnInt16(time_domain);
	this->buffer.loadFromSamples(&new_sample[0], new_sample.size(), 2, 44100);
}

void WavFile::RandomWeightMult()
{
	// Divide function by a random weight function
	srand((unsigned)time(0));
	for (size_t i = 0; i < this->samples.size(); i++)
	{
		samples[i] = samples[i] / ((rand() % (sf::Int16)pow(2, 14))+1);
	}
}

void WavFile::TestFunction()
{
	CArray fourier_domain;
	CArray time_domain;
	fourier_domain = this->FFT(1024);
	time_domain = this->IFFT(1024, fourier_domain);
	std::vector<sf::Int16> new_sample = this->CastOnInt16(time_domain);
	this->buffer.loadFromSamples(&new_sample[0], new_sample.size(), 2, 44100);
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
