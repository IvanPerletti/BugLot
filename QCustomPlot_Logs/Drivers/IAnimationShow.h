#ifndef IANIMATIONSHOW_H
#define IANIMATIONSHOW_H

#include <QObject>
#include <QWidget>
#include <QPropertyAnimation>


class IAnimationShow: public QObject
{
	Q_OBJECT
	void buildAnimation();
	void buildAnimation(QRect qrectStart, QRect qrectEnd);
	static void refineAnimation(QPropertyAnimation *animation);
	static void playAnimation(QPropertyAnimation *animation, QRect qrectStart, QRect qrectEnd);

public:
	IAnimationShow();
	static void showToLeft(QWidget *target, QRect qrectEnd);
	static void showToRight(QWidget *target, QRect qrectEnd);
	static void hideToLeft(QWidget *target, QRect qrectStart);
	static void hideToRight(QWidget *target, QRect qrectStart);
	static void hideToTop(QWidget *target, QRect qrectStart);
	static void showToBottom(QWidget *target, QRect qrectEnd);
	static void moveHeight(QWidget *target, int iEndingHeight);
	static void moveWidth(QWidget *target, int iEndingHeight);
};


#endif // IANIMATIONSHOW_H
