#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "PlayScene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

	void paintEvent(QPaintEvent *event);

	QMenuBar * mBar = nullptr;
	
	PlayScene * playScene = nullptr;
signals:
	// �Զ����ź�ֻ��Ҫ����������Ҫʵ��
	// ���ź������ӹؿ�ѡ�񷵻�������
	void backToMain();

};

#endif // CHOOSELEVELSCENE_H
