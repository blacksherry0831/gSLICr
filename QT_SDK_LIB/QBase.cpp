#include "QBase.h"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
QBase::QBase(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
QBase::~QBase(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string QBase::SYS_getCurrentTime(const std::string _format)
{
	QDateTime time = QDateTime::currentDateTime();
	
	QString time_str;

	if (_format==""){
		const std::string format_t="yyyy-MM-dd hh:mm:ss dd";
		const QString format_t_qt = QString::fromStdString(_format);
		time_str = time.toString(format_t_qt);
	}
	else
	{
		const QString format_t_qt = QString::fromStdString(_format);
		time_str=time.toString(format_t_qt);
	}
	
	return time_str.toStdString();
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
QString QBase::SYS_getCurrentTime_Q(const QString _format)
{
	QDateTime time = QDateTime::currentDateTime();
	QString current_time_t;

	if (_format.isEmpty()) {
		const QString format_t=QString("yyyy-MM-dd hh:mm:ss");
		current_time_t = time.toString(format_t);
	}

	current_time_t = time.toString(_format);

	return current_time_t;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
QString QBase::uint2Qstring(uint _num)
{
	return QString::number(_num);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
QString QBase::GetVectorFloat(const std::vector<float> _float)
{
	QString f_v_t;
	for (const auto f_data_t : _float)
	{
		QString f_str = QString("%1").arg(f_data_t);

		if (!f_v_t.isEmpty())
		{
			f_v_t.append(" ");
		}

		f_v_t.append(f_str);

	}
	
	return f_v_t;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::vector<float> QBase::CvtStr2VectorF(QString _float, QString _split)
{

	std::vector<float> v_f;
	
	QStringList v_s_f = _float.split(_split);

		for (int i=0;i<v_s_f.size();i++){
			QString f_str = v_s_f.at(i);
			v_f.push_back(f_str.toFloat());

		}

	return  v_f;

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void QBase::fs_write_xml(const QString _save_full_path,const QSharedPointer<QDomDocument> _Xml)
{

	if (!_Xml.isNull() && !_save_full_path.isEmpty())
	{
		QString  save_full_path = _save_full_path;

		QFile file(save_full_path);

		if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))

			return;

		QTextStream out(&file);

		out.setCodec("UTF-8");

		_Xml->save(out, 4, QDomNode::EncodingFromTextStream);

		file.close();

	}


}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
QSharedPointer<QDomDocument> QBase::fs_read_xml(const QString _full_path)
{

	QSharedPointer<QDomDocument>  domDoc;

	QFile file(_full_path);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Truncate | QIODevice::Text)) {
	
		return domDoc;

	}else{
	
		domDoc = QSharedPointer<QDomDocument>(new QDomDocument());

		domDoc->setContent(&file);

		file.close();	
	}
	
	return domDoc;

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void QBase::UI_Show_QImage_on_QLabel(QLabel * _qlab, QImage * const _p_qimg)
{
	if (_qlab!=Q_NULLPTR && _p_qimg!=Q_NULLPTR){

		QPixmap pixmap2(QPixmap::fromImage(*_p_qimg));

		_qlab->setPixmap(pixmap2.scaled(_qlab->size(), Qt::KeepAspectRatio));
	}

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/