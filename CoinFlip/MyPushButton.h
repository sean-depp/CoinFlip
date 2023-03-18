#pragma once

#include <QPushButton>

class MyPushButton : public QPushButton
{
	Q_OBJECT
public:
	//    explicit MyPushButton(QWidget *parent = nullptr);
	explicit MyPushButton(QString normalImg, QString pressImg = "", QString index = "");

	QString mNormalImgPath;
	QString mPressImgPath;

	int SCALE_SIZE = 2;

	// 按钮弹跳动画
	void zoomUpDown(int startX, int startY, int endX, int endY);

	// 重写鼠标按下事件
	void mousePressEvent(QMouseEvent *e);

	// 重写鼠标释放事件
	void mouseReleaseEvent(QMouseEvent *e);
signals:

};
