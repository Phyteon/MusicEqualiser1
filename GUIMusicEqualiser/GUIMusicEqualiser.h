#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUIMusicEqualiser.h"
//#include "WavFile.h"
#include "SFML/Audio.hpp"

class GUIMusicEqualiser : public QMainWindow
{
	Q_OBJECT

public:
	GUIMusicEqualiser(QWidget *parent = Q_NULLPTR);

private:
	Ui::GUIMusicEqualiserClass ui;
public slots:
	//void on_apply_caButton_clicked();
	//void on_apply_downButton_clicked();
	
};
