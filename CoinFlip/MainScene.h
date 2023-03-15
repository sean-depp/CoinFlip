#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainScene.h"
#include "ChooseLevelScene.h"

class MainScene : public QMainWindow
{
	Q_OBJECT

public:
	MainScene(QWidget *parent = Q_NULLPTR);

	// 重写paintEvent用于绘制
	void paintEvent(QPaintEvent *event);

	ChooseLevelScene * levelScene = nullptr;

private:
	Ui::MainSceneClass ui;
};
