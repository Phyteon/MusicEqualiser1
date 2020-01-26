#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUIMusicEqualiser.h"
#include "WavFile.h"


class GUIMusicEqualiser : public QMainWindow
{
	Q_OBJECT

public:
	GUIMusicEqualiser(QWidget *parent = Q_NULLPTR);
	
private:
	WavFile music_file;
	//QObject::connect(&music_file, &WavFile::ProgressChanged,
		//this->ui, &GUIMusicEqualiser::ShowProgress);
	Ui::GUIMusicEqualiserClass ui;
public slots:

	void on_apply_caButton_clicked();
	void on_apply_downButton_clicked();
	void on_apply_upButton_clicked();
	void on_loadButton_clicked();
	void on_saveButton_clicked();
	//void ShowProgress();
	
};
