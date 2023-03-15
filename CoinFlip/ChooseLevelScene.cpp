#include "stdafx.h"
#include "ChooseLevelScene.h"
#include "MyPushButton.h"
#include <QMenu>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
	// ���ñ���
	setWindowTitle(QString("�ؿ�ѡ��"));

	// ���ñ�����ͼ��
	setWindowIcon(QIcon(":/res/Coin0001.png"));

	// ���ô��ڴ�С
	setFixedSize(640, 1200);

	// �˵������
	mBar = menuBar();
	setMenuBar(mBar);

	// ��ӿ�ʼ�˵�
	QMenu * menu = mBar->addMenu("��ʼ");

	// ��ӿ�ʼ�˵�ѡ��
	QAction * actionQuit = menu->addAction("�˳�");

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
