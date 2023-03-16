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
	// 自定义信号只需要声明，不需要实现
	// 此信号用来从关卡选择返回主场景
	void backToMain();

};

#endif // CHOOSELEVELSCENE_H
