#include "stdafx.h"

#include <QDebug>
#include <QRect>
#include <QPropertyAnimation>
#include <QEasingCurve>

#include "PlayScene.h"
#include "MyPushButton.h"
#include "MyCoin.h"
#include "DataConfig.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{
//
//}

PlayScene::PlayScene(int levelIndex) {
	this->levelIndex = levelIndex;

	// 设置标题
	setWindowTitle(QString("翻金币"));

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
		emit this->backToChoose();
	});

	QString str = QString("Level: %1").arg(levelIndex + 1);
	QLabel * label = new QLabel(str);
	label->setParent(this);

	// 设置字体为微软雅黑 20
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPointSize(20);

	// 获取字体矩形宽高
	QFontMetrics fm(font);
	QRect rec = fm.boundingRect(str);
	int textWidth = rec.width();
	int textHeight = rec.height();

	label->setFont(font);
	label->setGeometry(SPACE8, this->height() - textHeight - SPACE8, textWidth, textHeight);

	QPixmap pix = QPixmap(":res/BoardNode.png");
	pix = pix.scaled(pix.width() * 2, pix.height() * 2);
	int rowCount = 4;
	int colCount = 4;

	int bgHeight = rowCount * pix.height();
	int bgWidth = colCount* pix.width();

	int bgX = (this->width() - bgWidth) / 2;
	int bgY = (this->height() - bgHeight) / 2;

	// 关卡配置
	DataConfig dataConfig;
	QString levelStr = QString("----%1----").arg(levelIndex);
	qDebug() << levelStr;
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			mArray[i][j] = dataConfig.mData[levelIndex + 1][i][j];
		}
		QString curRow = QString("%1 %2 %3 %4").arg(mArray[i][0]).arg(mArray[i][1]).arg(mArray[i][2]).arg(mArray[i][3]);
		qDebug() << curRow;
	}

	qDebug() << levelStr;

	QLabel * succImg = new QLabel;

	QPixmap tmpPix;
	tmpPix.load(":/res/LevelCompletedDialogBg.png");
	tmpPix = tmpPix.scaled(tmpPix.width() * 2, tmpPix.height() * 2);

	succImg->setPixmap(tmpPix);
	succImg->setParent(this);
	succImg->setGeometry((this->width() - tmpPix.width()) / 2, -tmpPix.height(), tmpPix.width(), tmpPix.height());

	// 金币绘制
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			// 金币背景绘制
			QLabel *label = new QLabel;
			label->setParent(this);
			label->setPixmap(pix);

			label->setGeometry(bgX + j * pix.width(), bgY + i * pix.height(), pix.width(), pix.height());

			// 依据配置文件绘制金币或者是银币
			MyCoin * coin = new MyCoin(this->mArray[i][j] == 1 ? ":/res/Coin0001.png" : ":/res/Coin0008.png");
			//MyCoin * coin = new MyCoin(":/res/Coin0001.png");
			int xDis = (pix.width() - coin->width()) / 2;
			int yDis = (pix.height() - coin->height()) / 2;
			coin->setParent(this);
			coin->setGeometry(bgX + j * pix.width() + xDis, bgY + i * pix.height() + yDis, pix.width(), pix.height());

			// 初始化正反面
			coin->mPoxX = i;
			coin->mPoxY = j;
			coin->mCurFlag = this->mArray[i][j] == 1;

			mMyCoinList[i][j] = coin;
			connect(coin, &QPushButton::clicked, [=]() {
				coin->flipCoin();
				this->mArray[i][j] = this->mArray[i][j] ? 0 : 1;
				QString arrInfo = QString("(%1, %2) %3").arg(i).arg(j).arg(mArray[i][j]);
				qDebug() << arrInfo;

				QTimer::singleShot(100, this, [=]() {
					// 上
					if (coin->mPoxY - 1 >= 0)
					{
						mMyCoinList[i][coin->mPoxY - 1]->flipCoin();
						this->mArray[i][coin->mPoxY - 1] = this->mArray[i][coin->mPoxY - 1] ? 0 : 1;
					}
					// 下
					if (coin->mPoxY + 1 <= 3)
					{
						mMyCoinList[i][coin->mPoxY + 1]->flipCoin();
						this->mArray[i][coin->mPoxY + 1] = this->mArray[i][coin->mPoxY + 1] ? 0 : 1;
					}
					// 左
					if (coin->mPoxX - 1 >= 0)
					{
						mMyCoinList[coin->mPoxX - 1][j]->flipCoin();
						this->mArray[coin->mPoxX - 1][j] = this->mArray[coin->mPoxX - 1][j] ? 0 : 1;
					}
					// 右
					if (coin->mPoxX + 1 <= 3)
					{
						mMyCoinList[coin->mPoxX + 1][j]->flipCoin();
						this->mArray[coin->mPoxX + 1][j] = this->mArray[coin->mPoxX + 1][j] ? 0 : 1;
					}

					this->mIsWin = true;
					for (int i = 0; i < 4; ++i)
					{
						for (int j = 0; j < 4; ++j)
						{
							if (mArray[i][j] == 0) {
								QString loc = QString("%1 %2 false").arg(i).arg(j);
								qDebug() << loc;

								mIsWin = false;
								break;
							}
						}
					}

					if (mIsWin) {
						qDebug() << "win";
						for (int i = 0; i < 4; ++i)
						{
							for (int j = 0; j < 4; ++j)
							{
								mMyCoinList[i][j]->mIsWin = true;
							}
						}

						// 播放胜利动画
						QPropertyAnimation * anim = new QPropertyAnimation(succImg, "geometry");
						anim->setDuration(800);
						anim->setStartValue(QRect((this->width() - tmpPix.width()) / 2, -tmpPix.height(), tmpPix.width(), tmpPix.height()));
						anim->setEndValue(QRect((this->width() - tmpPix.width()) / 2, tmpPix.height(), tmpPix.width(), tmpPix.height()));
						anim->setEasingCurve(QEasingCurve::OutBounce);
						anim->start();
					}
				});

			});
		}
	}
}

void PlayScene::paintEvent(QPaintEvent *event) {
	int SPACE8 = 8;
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/OtherSceneBg.png");
	painter.drawPixmap(0, mBar->height(), this->width(), this->height(), pix);

	pix.load(":/res/Title.png");
	pix = pix.scaled(pix.width()*1.2, pix.height()*1.2);
	painter.drawPixmap(SPACE8, mBar->height() + SPACE8, pix);
}