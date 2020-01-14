#include "DriveAuto.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
DriveAuto::DriveAuto(QObject *parent) :QObject(parent)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
DriveAuto::~DriveAuto()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DriveAuto::DrawSafeArea(QImage& _img)
{

	const int W = _img.width();
	const int H = _img.height();

	if (1920 == W &&
		1080 == H) {
		DrawSafeArea_1920_1080(_img);
	}else if (960 == W &&
			  540 == H) {
		DrawSafeArea_960_540(_img);
	}else{
	
	}
	
}
/*-----------------------------------------*/
/**
*安全区显示
*/
/*-----------------------------------------*/
void DriveAuto::DrawSafeArea_1920_1080(QImage& _img)
{
		Q_ASSERT(1920 == _img.width() && 1080 == _img.height());

		QPainter painter(&_img);
		painter.setPen(QPen(QColor(0, 255, 0), 3));
		painter.drawEllipse(0, 0, 100, 100);
		painter.drawLine(240, 1075, 1680, 1075);
		painter.drawLine(280, 1045, 1640, 1045);
		painter.drawLine(540, 850, 1380, 850);
		painter.drawLine(847, 620, 1073, 620);
		painter.drawLine(847, 620, 240, 1075);
		painter.drawLine(1073, 620, 1680, 1075);
		painter.drawLine(960, 1075, 960, 620);

		QFont font("宋体", 25, QFont::Bold, false);
		painter.setFont(font);
		painter.drawText(900, 620, "252cm");
		painter.drawText(900, 850, "61cm");
		painter.drawText(900, 1050, "23cm");
								
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DriveAuto::DrawSafeArea_960_540(QImage& _img)
{
		Q_ASSERT(960 == _img.width() &&	540 == _img.height());
		const int SCALE = 2;
		QPainter painter(&_img);
		painter.setPen(QPen(QColor(0, 255, 0), 4 / SCALE));
#if 0
		painter.drawEllipse(0, 0, 100 / SCALE, 100 / SCALE);
#endif // 0
		painter.drawLine(240 / SCALE, 1075 / SCALE, 1680 / SCALE, 1075 / SCALE);
		painter.drawLine(280 / SCALE, 1045 / SCALE, 1640 / SCALE, 1045 / SCALE);
		painter.drawLine(540 / SCALE, 850 / SCALE, 1380 / SCALE, 850 / SCALE);
		painter.drawLine(847 / SCALE, 620 / SCALE, 1073 / SCALE, 620 / SCALE);
		painter.drawLine(847 / SCALE, 620 / SCALE, 240 / SCALE, 1075 / SCALE);
		painter.drawLine(1073 / SCALE, 620 / SCALE, 1680 / SCALE, 1075 / SCALE);
		painter.drawLine(960 / SCALE, 1075 / SCALE, 960 / SCALE, 620 / SCALE);

		QFont font("宋体", 26 / SCALE, QFont::Bold, false);
		painter.setFont(font);
		painter.drawText(900/ SCALE, 620/ SCALE, "252cm");
		painter.drawText(900/ SCALE, 850/ SCALE, "61cm");
		painter.drawText(900/ SCALE, 1050/ SCALE, "23cm");
			
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DriveAuto::DrawRunDirection(QImage & _img, DrivePolicy::RunCmd _run_dir)
{
	const int LSZ = 4;
	QPainter painter(&_img);
	painter.setPen(QPen(QColor(255, 255, 0), LSZ));

	const int W = _img.width();
	const int H = _img.height();
	const int R = ((W > H) ? H : W)/4;
	const QPoint c(W/2,H/2);
	
	const QPoint c_u(c.x(), c.y()-R);
	const QPoint c_u_l(c.x()-R / 2,c.y()-R);
	const QPoint c_u_r(c.x()+R ,c.y()-R);
	
	const QPoint c_l(c.x()-R , c.y());
	const QPoint c_r(c.x()+R , c.y());
	
	const QPoint c_d(c.x(), c.y()+R);
	const QPoint c_d_l(c.x()-R, c.y() + R);
	const QPoint c_d_r(c.x() + R, c.y() + R);
	
	QPoint   c_x=c;

	painter.drawEllipse(c, R , R );
	
	switch (_run_dir)
	{
	case DrivePolicy::RunCmd::GO_DOWN:
		c_x = c_d;
		break;
	case DrivePolicy::RunCmd::GO_DOWN_LEFT:
		c_x = c_d_l;
		break;
	case DrivePolicy::RunCmd::GO_DOWN_RIGHT:
		c_x = c_d_r;
		break;
	case DrivePolicy::RunCmd::GO_RIGHT:
		c_x = c_r;
		break;
	case DrivePolicy::RunCmd::GO_LEFT:
		c_x = c_l;
		break;
	case DrivePolicy::RunCmd::GO_UP_RIGHT:
		c_x = c_u_r;
		break;
	case DrivePolicy::RunCmd::GO_UP_LEFT:
		c_x = c_u_l;
		break;
	case DrivePolicy::RunCmd::GO_UP:
		c_x = c_u;
		break;
	default:
		
		break;
	}

	painter.drawLine(c,c_x);

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DriveAuto::CalSafeArea(QImage & _img)
{
	const int W = _img.width();
	const int H = _img.height();

	if (1920 == W &&
		1080 == H) {
		CalSafeArea_1920_1080(_img);
	}
	else if (960 == W &&
			 540 == H) {
		CalSafeArea_960_540(_img);
	}
	else {

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DriveAuto::CalSafeArea_1920_1080(QImage & _img)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DriveAuto::CalSafeArea_960_540(QImage & _img)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int DriveAuto::Qimage2cvMat(QImage& _img)
{
	cv::Mat mat;

	mat.create(_img.height(), _img.width(), CV_8UC4);
	
	Q_ASSERT(_img.byteCount()== mat.total() * mat.elemSize());

	memcpy(mat.ptr<uchar>(0), _img.bits(),_img.byteCount());
		
	return 0;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/