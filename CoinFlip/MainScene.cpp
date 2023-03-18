#include "stdafx.h"
#include "MainScene.h"
#include "MyPushButton.h"
#include <QPainter>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 设置标题
	setWindowTitle(QString("翻金币"));

	// 设置标题栏图标
	setWindowIcon(QIcon(":/res/Coin0001.png"));

	// 设置窗口大小
	setFixedSize(640, 1200);

	// 退出
	connect(ui.action_1, &QAction::triggered, [=]() {
		this->close();
	});

	QSound * sound = new QSound(":/res/TapButtonSound.wav",this);

	MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
	startBtn->setParent(this);
	startBtn->move(this->width() *0.5 - startBtn->width()*0.5, this->height()*0.7);

	levelScene = new ChooseLevelScene;

	connect(startBtn, &QPushButton::clicked, [=]() {
		// 播放音效
		sound->play();
		// 按钮弹跳
		int DIS = 30;
		startBtn->zoomUpDown(0, 0, 0, DIS);
		startBtn->zoomUpDown(0, DIS, 0, 0);

		QTimer::singleShot(300, this, [=]() {
			// 位置保持
			levelScene->setGeometry(this->geometry());

			this->hide();
			levelScene->show();
		});
	});

	connect(levelScene, &ChooseLevelScene::backToMain, [=]() {
		this->setGeometry(levelScene->geometry());
		QTimer::singleShot(200, this, [=]() {
			
			levelScene->hide();
			this->show();
		});
	});

}

void MainScene::paintEvent(QPaintEvent *event) {
	int SPACE8 = 8;
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/OtherSceneBg.png");
	painter.drawPixmap(0, ui.menuBar->height(), this->width(), this->height(), pix);

	pix.load(":/res/Title.png");
	pix = pix.scaled(pix.width()*1.2, pix.height()*1.2);
	painter.drawPixmap(SPACE8, ui.menuBar->height() + SPACE8, pix);
}
