#include "stdafx.h"
#include "MyCoin.h"

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg) {
	QPixmap pix;
	bool ret = pix.load(btnImg);

	if (!ret) {
		qDebug() << "图片加载失败";
		return;
	}

	// 缩放图片
	pix = pix.scaled(pix.width() * SCALE_SIZE, pix.height() * SCALE_SIZE);

	// 设置按钮大小
	this->setFixedSize(pix.width(), pix.height());

	// 设置按钮样式，使用qss
	this->setStyleSheet("QPushButton{border:0px;}");

	// 设置图标
	this->setIcon(pix);

	// 设置图标大小
	this->setIconSize(QSize(pix.width(), pix.height()));

	this->mTimerToFlip = new QTimer(this);

	connect(mTimerToFlip, &QTimer::timeout, [=]() {
		QString curImg;
		if (mCurFlag)
		{
			// 正面
			//qDebug() << "正面";
			curImg = QString(":/res/Coin000%1.png").arg(mMin++);
		}
		else {
			// 反面
			//qDebug() << "反面";
			curImg = QString(":/res/Coin000%1.png").arg(mMax--);
		}


		QPixmap pix;
		bool ret = pix.load(curImg);

		if (!ret) {
			QString imgLoad = QString("%1图片加载失败").arg(curImg);
			qDebug() << imgLoad;
			return;
		}

		// 缩放图片
		pix = pix.scaled(pix.width() * SCALE_SIZE, pix.height() * SCALE_SIZE);

		// 设置按钮大小
		this->setFixedSize(pix.width(), pix.height());

		// 设置按钮样式，使用qss
		this->setStyleSheet("QPushButton{border:0px;}");

		// 设置图标
		this->setIcon(pix);

		// 设置图标大小
		this->setIconSize(QSize(pix.width(), pix.height()));

		if (mMin > mMax) {
			mMin = 1;
			mMax = 8;
			mIsAnim = false;
			mTimerToFlip->stop();
			mCurFlag = mCurFlag ? false : true;
	/*		if (mCurFlag)
			{
				qDebug() << "现在正面";
			}
			else {
				qDebug() << "现在反面";
			}*/
		}
	});
}

void MyCoin::flipCoin() {
	mIsAnim = true;
	mTimerToFlip->start(30);
}

void MyCoin::mousePressEvent(QMouseEvent *e) {
	if (mIsAnim || mIsWin) {
		return;
	}
	else {
		return QPushButton::mousePressEvent(e);
	}
}
