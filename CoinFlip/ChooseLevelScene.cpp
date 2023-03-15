#include "stdafx.h"
#include "ChooseLevelScene.h"
#include "MyPushButton.h"
#include <QMenu>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
	// 设置标题
	setWindowTitle(QString("关卡选择"));

	// 设置标题栏图标
	setWindowIcon(QIcon(":/res/Coin0001.png"));

	// 设置窗口大小
	setFixedSize(640, 1200);

	// 菜单栏添加
	mBar = menuBar();
	setMenuBar(mBar);

	// 添加开始菜单
	QMenu * menu = mBar->addMenu("开始");

	// 添加开始菜单选项
	QAction * actionQuit = menu->addAction("退出");

	connect(actionQuit, &QAction::triggered, [=]() {
		this->close();
	});

	int SPACE8 = 8;
	MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width()-backBtn->width()-SPACE8, this->height()-backBtn->height()-SPACE8);

	connect(backBtn, &QPushButton::clicked, [=]() {
	});
}

void ChooseLevelScene::paintEvent(QPaintEvent *event) {
	int SPACE8 = 8;
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/OtherSceneBg.png");
	painter.drawPixmap(0, mBar->height(), this->width(), this->height(), pix);

	pix.load(":/res/Title.png");
	pix = pix.scaled(pix.width()*2, pix.height()*2);
	painter.drawPixmap( (this->width() - pix.width()) * 0.5, mBar->height() + SPACE8, pix.width(), pix.height(), pix);

}
