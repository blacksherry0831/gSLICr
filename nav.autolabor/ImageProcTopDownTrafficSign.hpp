#pragma once
/*-----------------------------------------*/
#include "ImageProcTopDown.hpp"
/*-----------------------------------------*/
#include "TRAFFIC_SIGN_LIB/TrafficSignParam.hpp"
#include "TRAFFIC_SIGN_LIB/TrafficSignMethod.hpp"
#include "TRAFFIC_SIGN_LIB/TrafficSignTemplete.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class ImageProcTopDownTrafficSign:public ImageProcTopDown
{
    Q_OBJECT
public:
    explicit ImageProcTopDownTrafficSign();
    ~ImageProcTopDownTrafficSign();
signals:
	void sig_point_cloud(QVector<QVector3D>);
	void sig_pose_position_orientation(QString,QVector3D,QVector4D);
private:
	void emit_pose_position_orientation(
		const QString		_color,
		const QVector3D		_c,
		const double		_a);

	void emit_pose(const IplImage * _src, const TrafficSignResult * _r);
	void emit_pointcloud(const IplImage * _src, const TrafficSignResult * _r);
		
	
private:
	TrafficSignParam									mTS_Param;
	TrafficSignTemplete									mTS_Temp;
	std::vector<std::shared_ptr<TrafficSignPropertyHu>>	mTS_Properties;
	TrafficSignMethodHu									mTS_tsm;
private:
	void initTrafficSignTemplete();
private:
	void ProcImageFrame(QSharedPointer<QImage> _img_p, const QDateTime & _time);
public slots:
	void ImageProc(QSharedPointer<QImage> _img_p, const QDateTime _t);
private:
	QVector3D	getCameraPos(const IplImage* _src);
	QVector3D	cvt2CamreaCoord(const IplImage* _src, QVector3D _pt);
	double		cvt2CamreaAngle(const double _a);
	
	QVector<QVector3D> cvtPointCloud2CamreaCoord(const IplImage* _src,std::vector<cv::Point> _pts);

	static	QVector4D	cvtYaw2Quater(const double _y);
public:
	void trafficSign(IplImage* _src);

	static QVector3D toBaseCoord(QVector3D _pt, QVector3D _base, const float _mpp);

	void emit_sig_1_frame_air_view(
		const bool _airView,
		QSharedPointer<QImage> _av,
		QSharedPointer<QImage> _src,
		const QDateTime _time);

		
};