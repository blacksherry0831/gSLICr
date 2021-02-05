#include <sensor_msgs_PointCloud.hpp>
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const QString	SensorMsgsPointCloud::sensor_msgs__PointCloud = "sensor_msgs/PointCloud";
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SensorMsgsPointCloud::SensorMsgsPointCloud(
	QObject* parent,
	const QString _topic, 
	const QString _frame_id) :QObject(parent)
{
	this->m_topic = _topic.toStdString();
	this->m_header.setFrameId(_frame_id);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SensorMsgsPointCloud::SensorMsgsPointCloud(QObject* parent) :QObject(parent)
{
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SensorMsgsPointCloud::~SensorMsgsPointCloud()
{
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SensorMsgsPointCloud::init(std::string _topic, std::string _frame_id)
{
	this->m_topic = _topic;	
	this->m_header.setFrameId(QString::fromStdString(_frame_id));
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
QString SensorMsgsPointCloud::toJsonStr()
{
	QJsonObject PointCloud;

	QJsonObject header = m_header.getJsonObjInc();;
	QJsonArray  points = getJsonPointsArray();
	QJsonArray  channels = sensor_msgs_ChannelFloat32::Channels2JArray(m_channels);

	QJsonObject msg;

	msg.insert("header", header);
	msg.insert("points", points);
	msg.insert("channels", channels);

	PointCloud.insert("op", "publish");
	PointCloud.insert("topic", QString::fromStdString(m_topic));
	PointCloud.insert("msg", msg);

	return ROSBasic::Json2Str(PointCloud);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SensorMsgsPointCloud::setPoints(const QVector<QVector3D> _points)
{
	
	sensor_msgs_ChannelFloat32 channel;
	
	channel.initIntensityDefault(_points);

	m_points.clear();
	m_channels.clear();

	m_points = _points;	
	m_channels.push_back(channel);
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SensorMsgsPointCloud::SimulatePointsCircle()
{
	QVector<QVector3D>	points;
	
	const int Degree = 180;
	const float delta = rand()%5;
	const float R = 5+delta*0.1;
	
	for (int i = 0; i <Degree ; i++){
			const float	 rad=i* 3.14/180;
			const float x = R*sin(rad);
			const float y = R*cos(rad);

			QVector3D	point(x,y,0.8);
			points.push_back(point);
	}
	
	setPoints(points);

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
QJsonArray SensorMsgsPointCloud::getJsonPointsArray() const
{
	QJsonArray JsonA;

	for each (QVector3D var in m_points) {

		QJsonObject qjo;
		qjo.insert("x", var.x());
		qjo.insert("y", var.y());
		qjo.insert("z", var.z());

		JsonA.append(qjo);

	}

	return JsonA;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
