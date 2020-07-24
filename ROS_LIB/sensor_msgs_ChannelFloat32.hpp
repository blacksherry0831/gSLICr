#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
#include <QVector3D>
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class sensor_msgs_ChannelFloat32
{
private:
	std::string m_name;
	std::vector<float> m_values;
public:
	static QJsonArray std_vector2QJsonArray(const std::vector<float>& _values);
public:
	sensor_msgs_ChannelFloat32(const int _sz);
	sensor_msgs_ChannelFloat32();
	~sensor_msgs_ChannelFloat32();
public:
	void initIntensityDefault(const int _sz);
	void initIntensityDefault(const QVector<QVector3D> _points);

	QJsonObject getJsonObj() const;
	
	static QJsonArray	Channels2JArray(QVector<sensor_msgs_ChannelFloat32>		_channels);


};