#include "PreProcImageOrg.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
PreProcImageOrg::PreProcImageOrg(QObject *parent) :QObject(parent)
{
	mSafeArea = false;
	this->mSaveImage = false;
	this->InitImageSavePath();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
PreProcImageOrg::~PreProcImageOrg()
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageOrg::InitImageSavePath()
{
	const QString qexeFullPath = QCoreApplication::applicationDirPath();

	const QString PathImageSave = qexeFullPath + "/" + "Image" + "/";

	if (CreateDir(PathImageSave)) {
		this->mPaths = PathImageSave;
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageOrg::SaveQImage(const QImage& _img )
{

	qint64 t = QDateTime::currentDateTime().toMSecsSinceEpoch();
	QString name = QString("%1").arg(t) + ".png";

	if (!(_img).save(mPaths + name, "png")){
		qDebug() << "picture save failed" << endl;
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageOrg::SetResize(const int _w, const int _h)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageOrg::DrawSafeArea(const bool _r)
{
	this->mSafeArea=_r;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageOrg::SetSaveImage(const bool _s)
{
	this->mSaveImage = _s;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageOrg::ImageProc(QImage _img, const QDateTime _time)
{

	if (mSaveImage){
		SaveQImage(_img);
	}

	if (mSafeArea){
		DriveAuto::DrawSafeArea(_img);
	}

	emit sig_1_frame_bgra(_img, _time);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool PreProcImageOrg::CreateDir(const QString &path)
{
	QDir dir(path); // 注意
	if (dir.exists())
	{
		return true;
	}
	else {
		dir.setPath("");
		bool ok = dir.mkpath(path);
		return ok;
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/