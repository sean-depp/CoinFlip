#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

	void paintEvent(QPaintEvent *event);

	QMenuBar * mBar = nullptr;
signals:
	// �Զ����ź�ֻ��Ҫ����������Ҫʵ��
	// ���ź������ӹؿ�ѡ�񷵻�������
	void backToMain();

};

#endif // CHOOSELEVELSCENE_H
