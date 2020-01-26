#include "GUIMusicEqualiser.h"

GUIMusicEqualiser::GUIMusicEqualiser(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void GUIMusicEqualiser::on_apply_downButton_clicked()
{
	sf::Int16 hertz = (sf::Int16)this->ui.caSlider->value();
	if (hertz > 44100 / 1024)
		this->music_file.PitchDown(1024, hertz);
	else
	{
		// Display 100%
	}
}

void GUIMusicEqualiser::on_apply_upButton_clicked()
{
	sf::Int16 hertz = (sf::Int16)this->ui.caSlider->value();
	if (hertz > 44100/1024)
		this->music_file.PitchUp(1024, hertz);
	else
	{
		// Display 100%
	}
}

void GUIMusicEqualiser::on_loadButton_clicked()
{
	QString Qpath = ui.targetText->text();
	std::string path = Qpath.toLocal8Bit().constData();
	this->music_file.LoadWaveFile(path);
}

void GUIMusicEqualiser::on_saveButton_clicked()
{
	QString Qpath = ui.targetText->text();
	std::string path = Qpath.toLocal8Bit().constData();
	this->music_file.SaveWaveFile(path);
}

void GUIMusicEqualiser::ShowProgress(size_t percent)
{
	this->ui.progressBar->setValue(percent);
}

void GUIMusicEqualiser::on_apply_caButton_clicked()
{
	sf::Int16 mod = (sf::Int16)this->ui.caSlider->value();
	if (mod != 1)
		this->music_file.ChangeAmplitude(mod);
	else
	{
		// Display 100%
	}
}

