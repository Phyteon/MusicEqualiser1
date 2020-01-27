#include "GUIMusicEqualiser.h"

GUIMusicEqualiser::GUIMusicEqualiser(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//connect(this->ui.apply_caButton, SIGNAL(released()), this, SLOT(on_apply_caButton_clicked()));
	//connect(this->ui.apply_downButton, SIGNAL(released()), this, SLOT(on_apply_downButton_clicked()));
	//connect(this->ui.apply_upButton, SIGNAL(released()), this, SLOT(on_apply_upButton_clicked()));
	//connect(this->ui.loadButton, SIGNAL(released()), this, SLOT(on_loadButton_clicked()));
	//connect(this->ui.saveButton, SIGNAL(released()), this, SLOT(on_saveButton_clicked()));
}

void GUIMusicEqualiser::on_apply_downButton_clicked()
{
	sf::Int16 hertz = (sf::Int16)this->ui.pitch_downSlider->value();
	if (hertz > 44100 / 1024)
		this->music_file.PitchDown(1024, hertz);
	
}

void GUIMusicEqualiser::on_apply_upButton_clicked()
{
	int hertz = this->ui.pitch_upSlider->value();
	
	if (hertz > 44100/1024)
		this->music_file.PitchUp(1024, hertz);
	
}

void GUIMusicEqualiser::on_loadButton_clicked()
{
	QString Qpath = ui.targetText->text();
	std::string path = Qpath.toLocal8Bit().constData();
	this->music_file.LoadWaveFile(path);
}

void GUIMusicEqualiser::on_saveButton_clicked()
{
	QString Qpath = ui.saveText->text();
	std::string path = Qpath.toLocal8Bit().constData();
	this->music_file.SaveWaveFile(path);
}

void GUIMusicEqualiser::on_apply_hannButton_clicked()
{
	this->music_file.ApplyHannWindow(1024);
}


void GUIMusicEqualiser::on_apply_caButton_clicked()
{
	sf::Int16 mod = (sf::Int16)this->ui.caSlider->value();
	if (mod != 1)
		this->music_file.ChangeAmplitude(mod);
	
}

