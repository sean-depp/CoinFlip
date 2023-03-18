#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "MyCoin.h"

class PlayScene : public QMainWindow
{
	Q_OBJECT
public:
	//explicit PlayScene(QWidget *parent = nullptr);
	PlayScene(int levelIndex);

	int levelIndex;

	QMenuBar * mBar = nullptr;

	void paintEvent(QPaintEvent *event);

	int mArray[4][4];
	MyCoin * mMyCoinList[4][4];
	bool mIsWin = false;

signals:
	void backToChoose();
};

#endif // PLAYSCENE_H
