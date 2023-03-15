#include "stdafx.h"
#include "MyPushButton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QRect>

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
	this->mNormalImgPath = normalImg;
	this->mPressImgPath = pressImg;

	QPixmap pix;
	bool ret = pix.load(normalImg);

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
}

void MyPushButton::zoomUpDown(int startX, int startY, int endX, int endY) {
	QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");

	// ���ö�����ʱ
	anim->setDuration(200);

	// ��ʼλ��
	anim->setStartValue(QVariant(QRect(this->x() + startX, this->y() + startY, this->width(), this->height())));

	// ����λ��
	anim->setEndValue(QVariant(QRect(this->x() + endX, this->y() + endY, this->width(), this->height())));

	// ��������
	anim->setEasingCurve(QEasingCurve::OutBounce);

	// ִ�ж���
	anim->start();
}


// ��д��갴���¼�
void MyPushButton::mousePressEvent(QMouseEvent *e) {
	if (mPressImgPath != "") {
		QPixmap pix;
		bool ret = pix.load(mPressImgPath);

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
	}

	// ���������������
	return QPushButton::mousePressEvent(e);
}

// ��д����ͷ��¼�
void MyPushButton::mouseReleaseEvent(QMouseEvent *e) {
	if (mPressImgPath != "") {
		QPixmap pix;
		bool ret = pix.load(mNormalImgPath);

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
	}

	// ���������������
	return QPushButton::mouseReleaseEvent(e);
}