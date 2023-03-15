#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainScene.h"

class MainScene : public QMainWindow
{
	Q_OBJECT

public:
	MainScene(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainSceneClass ui;
};
