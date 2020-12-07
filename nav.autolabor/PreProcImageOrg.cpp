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
	this->mSaveImageOnce = false;
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
void PreProcImageOrg::SaveQImage(const QSharedPointer<QImage> _img)
{
	qint64 t = QDateTime::currentDateTime().toMSecsSinceEpoch();
	QString name = QString("%1").arg(t) + ".png";

	if (!(_img)->save(mPaths + name, "png")) {
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
void PreProcImageOrg::ImageProc(QSharedPointer<QImage> _img_ptr, QDateTime _time)
{
	if (mSaveImage) {
		SaveQImage(_img_ptr);
	}

	if (mSaveImageOnce)
	{
		SaveQImage(_img_ptr);
		mSaveImageOnce = false;
	}

	if (mSafeArea) {
		DriveAuto::DrawSafeArea(_img_ptr.get());
	}

	emit sig_1_frame_bgra_ref(_img_ptr, _time);
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
void PreProcImageOrg::SetSaveImageOnce(const bool _s)
{
	this->mSaveImageOnce = _s ;
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