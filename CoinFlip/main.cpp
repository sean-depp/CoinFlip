#include "stdafx.h"
#include "MainScene.h"
#include <QtWidgets/QApplication>
#include "DataConfig.h"
#include <QDebug>

int main(int argc, char *argv[])
{
	//DataConfig dc;
	//
	//for (int l = 1; l <= 20; ++l)
	//{

	//	for (int i = 0; i < 4; ++i)
	//	{
	//		for (int j = 0; j < 4; ++j)
	//		{
	//			qDebug() << dc.mData[l][i][j];
	//		}
	//	}
	//}

	QApplication a(argc, argv);
	MainScene w;
	w.show();
	return a.exec();
}
