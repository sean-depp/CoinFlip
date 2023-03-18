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

	// ��ť��������
	void zoomUpDown(int startX, int startY, int endX, int endY);

	// ��д��갴���¼�
	void mousePressEvent(QMouseEvent *e);

	// ��д����ͷ��¼�
	void mouseReleaseEvent(QMouseEvent *e);
signals:

};
