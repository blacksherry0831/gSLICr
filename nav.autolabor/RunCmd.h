#pragma once
#ifndef _RunCmd_H_
#define _RunCmd_H_
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <QQueue>
#include <QPainter>
#include <QPen>
#include <QDateTime>
#include <QDebug>
#include <QMetaEnum>
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
Q_ENUMS(RunCmd);

enum RunCmd
{
	GO_NONE = 0,

	GO_DOWN,
	GO_DOWN_LEFT,
	GO_DOWN_RIGHT,

	GO_RIGHT,
	GO_LEFT,

	GO_UP,
	GO_UP_RIGHT,
	GO_UP_LEFT,

	GO_STOP

};

Q_DECLARE_METATYPE(RunCmd);

#endif