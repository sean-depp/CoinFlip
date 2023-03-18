#include "stdafx.h"
#include "ChooseLevelScene.h"
#include "MyPushButton.h"
#include <QMenu>
#include <QDebug>
#include <QLabel>

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

	// 退出
	connect(actionQuit, &QAction::triggered, [=]() {
		this->close();
	});

	// 绘制返回按钮
	int SPACE8 = 8;
	int SPACE24 = 24;
	MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width() - backBtn->width() - SPACE8, this->height() - backBtn->height() - SPACE8);

	connect(backBtn, &QPushButton::clicked, [=]() {
		emit this->backToMain();
	});

	// 绘制关卡按钮
	MyPushButton * levelBtnTmp = new MyPushButton(":/res/LevelIcon.png");

	// 行列信息
	int colCount = 4;
	int levelCount = 20;
	int rowCount = levelCount / colCount;

	// 计算关卡按钮的长和宽，以及绘制的起始位置
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
						// 删除游戏场景
						delete this->playScene;
						playScene = nullptr;

						this->show();
					});
				});
			}
		});

		// 使用label实现
		// todo 我想封装到MyPushButton里面
		QLabel * label = new QLabel;
		label->setParent(this);
		label->setFixedSize(levelBtn->width(), levelBtn->height());
		label->setText(QString::number(i + 1));
		label->move(levelX + i % colCount * (levelBtn->width() + SPACE24), levelY + i / colCount * (levelBtn->height() + SPACE24));

		// 设置对齐方式
		label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

		// 设置鼠标穿透
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
