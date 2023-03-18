#include "stdafx.h"
#include "ChooseLevelScene.h"
#include "MyPushButton.h"
#include <QMenu>
#include <QDebug>
#include <QLabel>

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

	// �˳�
	connect(actionQuit, &QAction::triggered, [=]() {
		this->close();
	});

	// ���Ʒ��ذ�ť
	int SPACE8 = 8;
	int SPACE24 = 24;
	MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width() - backBtn->width() - SPACE8, this->height() - backBtn->height() - SPACE8);

	connect(backBtn, &QPushButton::clicked, [=]() {
		emit this->backToMain();
	});

	// ���ƹؿ���ť
	MyPushButton * levelBtnTmp = new MyPushButton(":/res/LevelIcon.png");

	// ������Ϣ
	int colCount = 4;
	int levelCount = 20;
	int rowCount = levelCount / colCount;

	// ����ؿ���ť�ĳ��Ϳ��Լ����Ƶ���ʼλ��
	int levelWidth = (levelBtnTmp->width() + SPACE24)* colCount - SPACE24;
	int levelX = (this->width() - levelWidth) / 2;

	int levelHeight = (levelBtnTmp->height() + SPACE24)* rowCount - SPACE24;
	int levelY = (this->height() - levelHeight) / 2;

	for (int i = 0; i < levelCount; ++i) {
		MyPushButton * levelBtn = new MyPushButton(":/res/LevelIcon.png");
		levelBtn->setParent(this);
		levelBtn->move(levelX + i % colCount * (levelBtn->width() + SPACE24), levelY + i / colCount * (levelBtn->height() + SPACE24));

		connect(levelBtn, &QPushButton::clicked, [=]() {
			if (playScene == nullptr) {
				this->playScene = new PlayScene(i);

				playScene->setGeometry(this->geometry());
				this->hide();
				this->playScene->show();

				connect(this->playScene, &PlayScene::backToChoose, [=]() {
					QTimer::singleShot(200, this, [=]() {
						this->setGeometry(playScene->geometry());
						// ɾ����Ϸ����
						delete this->playScene;
						playScene = nullptr;

						this->show();
					});
				});
			}
		});

		// ʹ��labelʵ��
		// todo �����װ��MyPushButton����
		QLabel * label = new QLabel;
		label->setParent(this);
		label->setFixedSize(levelBtn->width(), levelBtn->height());
		label->setText(QString::number(i + 1));
		label->move(levelX + i % colCount * (levelBtn->width() + SPACE24), levelY + i / colCount * (levelBtn->height() + SPACE24));

		// ���ö��뷽ʽ
		label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

		// ������괩͸
		label->setAttribute(Qt::WA_TransparentForMouseEvents);
	}

}

void ChooseLevelScene::paintEvent(QPaintEvent *event) {
	int SPACE8 = 8;
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/OtherSceneBg.png");
	painter.drawPixmap(0, mBar->height(), this->width(), this->height(), pix);

	pix.load(":/res/Title.png");
	pix = pix.scaled(pix.width() * 2, pix.height() * 2);
	painter.drawPixmap((this->width() - pix.width()) * 0.5, mBar->height() + SPACE8, pix.width(), pix.height(), pix);

}
