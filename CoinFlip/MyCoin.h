#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString);

	int SCALE_SIZE = 2;
	QTimer * mTimerToFlip;
	int mMin = 1;
	int mMax = 8;
	int mPoxX;
	int mPoxY;
	bool mCurFlag;

	bool mIsAnim = false;
	bool mIsWin = false;

	void flipCoin();

	void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // MYCOIN_H
