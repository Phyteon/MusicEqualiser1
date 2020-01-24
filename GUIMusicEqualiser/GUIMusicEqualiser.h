#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUIMusicEqualiser.h"

class GUIMusicEqualiser : public QMainWindow
{
	Q_OBJECT

public:
	GUIMusicEqualiser(QWidget *parent = Q_NULLPTR);

private:
	Ui::GUIMusicEqualiserClass ui;
};
