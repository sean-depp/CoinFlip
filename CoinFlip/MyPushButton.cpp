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
}

void MyPushButton::zoomUpDown(int startX, int startY, int endX, int endY) {
	QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");

	// 设置动画耗时
	anim->setDuration(200);

	// 开始位置
	anim->setStartValue(QVariant(QRect(this->x() + startX, this->y() + startY, this->width(), this->height())));

	// 结束位置
	anim->setEndValue(QVariant(QRect(this->x() + endX, this->y() + endY, this->width(), this->height())));

	// 动画曲线
	anim->setEasingCurve(QEasingCurve::OutBounce);

	// 执行动画
	anim->start();
}


// 重写鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent *e) {
	if (mPressImgPath != "") {
		QPixmap pix;
		bool ret = pix.load(mPressImgPath);

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
	}

	// 交给父类继续流程
	return QPushButton::mousePressEvent(e);
}

// 重写鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e) {
	if (mPressImgPath != "") {
		QPixmap pix;
		bool ret = pix.load(mNormalImgPath);

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
	}

	// 交给父类继续流程
	return QPushButton::mouseReleaseEvent(e);
}