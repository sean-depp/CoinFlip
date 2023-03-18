#include "stdafx.h"
#include "MyCoin.h"

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg) {
	QPixmap pix;
	bool ret = pix.load(btnImg);

	if (!ret) {
		qDebug() << "ͼƬ����ʧ��";
		return;
	}

	// ����ͼƬ
	pix = pix.scaled(pix.width() * SCALE_SIZE, pix.height() * SCALE_SIZE);

	// ���ð�ť��С
	this->setFixedSize(pix.width(), pix.height());

	// ���ð�ť��ʽ��ʹ��qss
	this->setStyleSheet("QPushButton{border:0px;}");

	// ����ͼ��
	this->setIcon(pix);

	// ����ͼ���С
	this->setIconSize(QSize(pix.width(), pix.height()));

	this->mTimerToFlip = new QTimer(this);

	connect(mTimerToFlip, &QTimer::timeout, [=]() {
		QString curImg;
		if (mCurFlag)
		{
			// ����
			//qDebug() << "����";
			curImg = QString(":/res/Coin000%1.png").arg(mMin++);
		}
		else {
			// ����
			//qDebug() << "����";
			curImg = QString(":/res/Coin000%1.png").arg(mMax--);
		}


		QPixmap pix;
		bool ret = pix.load(curImg);

		if (!ret) {
			QString imgLoad = QString("%1ͼƬ����ʧ��").arg(curImg);
			qDebug() << imgLoad;
			return;
		}

		// ����ͼƬ
		pix = pix.scaled(pix.width() * SCALE_SIZE, pix.height() * SCALE_SIZE);

		// ���ð�ť��С
		this->setFixedSize(pix.width(), pix.height());

		// ���ð�ť��ʽ��ʹ��qss
		this->setStyleSheet("QPushButton{border:0px;}");

		// ����ͼ��
		this->setIcon(pix);

		// ����ͼ���С
		this->setIconSize(QSize(pix.width(), pix.height()));

		if (mMin > mMax) {
			mMin = 1;
			mMax = 8;
			mIsAnim = false;
			mTimerToFlip->stop();
			mCurFlag = mCurFlag ? false : true;
	/*		if (mCurFlag)
			{
				qDebug() << "��������";
			}
			else {
				qDebug() << "���ڷ���";
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
