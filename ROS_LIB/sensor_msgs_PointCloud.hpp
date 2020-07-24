#pragma once
/*----------------------------------------------------------------*/
#ifndef _SensorMsgsPointCloud_H_
#define _SensorMsgsPointCloud_H_
/*----------------------------------------------------------------*/
#include <QWebSocket>
#include <QQueue>
#include <QImage>
#include <QMutex>
#include <QtCore>
#include <QVector3D>
/*----------------------------------------------------------------*/
#include "ROSBasic.hpp"
/*----------------------------------------------------------------*/
#include "std_msgs_Header.hpp"
#include "sensor_msgs_ChannelFloat32.hpp"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
class SensorMsgsPointCloud : public QObject
{
	Q_OBJECT
public:
	SensorMsgsPointCloud(
		QObject *parent ,
		const QString _topic,
		const QString _frame_id);
	SensorMsgsPointCloud(QObject *parent = nullptr);
	~SensorMsgsPointCloud();
private:
	std::string								m_topic;
private:
	std_msgs_Header							m_header;
	QVector<QVector3D>						m_points;
	QVector<sensor_msgs_ChannelFloat32>		m_channels;
public:
	void setPoints(const QVector<QVector3D> _points);
public:
	void SimulatePointsCircle();
public:
	QJsonArray getJsonPointsArray() const;
public:
	void init(std::string _topic, std::string _frame_id);

	QString toJsonStr();

};

#endif 
