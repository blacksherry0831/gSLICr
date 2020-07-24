#include "sensor_msgs_ChannelFloat32.hpp"
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
sensor_msgs_ChannelFloat32::sensor_msgs_ChannelFloat32(const int _sz)
{
	this->initIntensityDefault(_sz);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
sensor_msgs_ChannelFloat32::sensor_msgs_ChannelFloat32()
{
	this->m_name = "intensities";
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
sensor_msgs_ChannelFloat32::~sensor_msgs_ChannelFloat32()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void sensor_msgs_ChannelFloat32::initIntensityDefault(const int _sz)
{
	this->m_name = "intensities";
	this->m_values.resize(_sz, 100);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void sensor_msgs_ChannelFloat32::initIntensityDefault(const QVector<QVector3D> _points)
{
	this->m_values.clear();
	this->m_name = "intensities";
	
	for each (auto pt in  _points){
		this->m_values.push_back(pt.x());
	}
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject sensor_msgs_ChannelFloat32::getJsonObj() const
{
	QJsonObject channel;
	const QJsonArray  values = std_vector2QJsonArray(m_values);;
	
	channel.insert("name",QString::fromStdString(this->m_name));
	channel.insert("values",values);

	return channel;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonArray sensor_msgs_ChannelFloat32::Channels2JArray(const QVector<sensor_msgs_ChannelFloat32> _channels)
{
	QJsonArray	channels;
	
	for each (const auto channel in _channels){
		channels.append(channel.getJsonObj());
	}
	
	return channels;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonArray sensor_msgs_ChannelFloat32::std_vector2QJsonArray(const std::vector<float>& _values)
{
	QJsonArray  values;	
	for each (float var in  _values) {
		values.append(var);
	}
	return values;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/