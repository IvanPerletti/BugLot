#include "IAnimationShow.h"

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

#define DURATION_MS 500


IAnimationShow::IAnimationShow()
{

}
//------------------------------------------------------------------------------
void IAnimationShow::refineAnimation(QPropertyAnimation *animation)
{
	animation->setDuration(DURATION_MS);
	QEasingCurve curve;
	curve.setType(QEasingCurve::OutQuart);
	curve.setAmplitude(1.00);
	curve.setPeriod(0.40);
	animation->setEasingCurve(curve);
}
//------------------------------------------------------------------------------
void IAnimationShow::playAnimation(QPropertyAnimation *animation, QRect qrectStart, QRect qrectEnd)
{
	animation->setStartValue(qrectStart);
	animation->setEndValue(qrectEnd);
	refineAnimation(animation);
	animation->start();
}
//------------------------------------------------------------------------------
void IAnimationShow::showToLeft(QWidget *target, QRect qrectEnd)
{
	QRect qrectStart = qrectEnd;
	int width = qrectEnd.width();
	qrectStart.moveLeft(width);
	target->show();

	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	playAnimation(animation, qrectStart, qrectEnd);
	animation->start();
}
//------------------------------------------------------------------------------
void IAnimationShow::showToRight(QWidget *target, QRect qrectEnd)
{
	QRect qrectStart = qrectEnd;
	int width = qrectEnd.width();
	qrectStart.moveRight(-width);
	target->show();
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	playAnimation(animation, qrectStart, qrectEnd);
	animation->start();
}
//------------------------------------------------------------------------------
void IAnimationShow::hideToLeft(QWidget *target, QRect qrectStart)
{
	QRect qrectEnd = qrectStart;
	int width = qrectStart.width();
	qrectEnd.moveRight(-width);
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	playAnimation(animation, qrectStart, qrectEnd);
	connect(animation, SIGNAL(finished()), target, SLOT(hide()));
}
//------------------------------------------------------------------------------
void IAnimationShow::hideToRight(QWidget *target, QRect qrectStart)
{
	QRect qrectEnd = qrectStart;
	int width = qrectStart.width();
	qrectEnd.moveLeft(width);
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	playAnimation(animation, qrectStart, qrectEnd);
	connect(animation, SIGNAL(finished()), target, SLOT(hide()));
}
//------------------------------------------------------------------------------
void IAnimationShow::hideToTop(QWidget *target, QRect qrectStart)
{
	QRect qrectEnd = qrectStart;
	int height = qrectStart.height();
	qrectEnd.moveTop(height);
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	playAnimation(animation, qrectStart, qrectEnd);
	connect(animation, SIGNAL(finished()), target, SLOT(hide()));
}
//------------------------------------------------------------------------------
void IAnimationShow::showToBottom(QWidget *target, QRect qrectEnd)
{
	QRect qrectStart = qrectEnd;
	int height = qrectEnd.height();
	qrectStart.moveBottom(height);
	target->show();
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	playAnimation(animation, qrectStart, qrectEnd);
	animation->start();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void IAnimationShow::moveHeight(QWidget *target, int iEndingHeight)
{
	target->show();
	QPropertyAnimation* animation = new QPropertyAnimation( target, "maximumHeight" );
	animation->setStartValue( target->height() );
	animation->setEndValue( iEndingHeight );
	refineAnimation(animation);
	animation->start();
}
//------------------------------------------------------------------------------
void IAnimationShow::moveWidth(QWidget *target, int iEndingHeight)
{
	target->show();
	QPropertyAnimation* animation = new QPropertyAnimation( target, "maximumWidth" );
	animation->setStartValue( target->width() );
	animation->setEndValue( iEndingHeight );
	refineAnimation(animation);
	animation->start();
}
