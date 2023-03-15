#pragma once

#include <QPushButton>

class MyPushButton : public QPushButton
{
	Q_OBJECT
public:
	//    explicit MyPushButton(QWidget *parent = nullptr);
	explicit MyPushButton(QString normalImg, QString pressImg = "");

	QString normalImgPath;
	QString pressImgPath;

	int SCALE_SIZE = 2;

	void zoomUpDown(int startX, int startY, int endX, int endY);
signals:

};
