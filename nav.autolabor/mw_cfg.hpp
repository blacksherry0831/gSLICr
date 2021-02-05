#pragma once
/*----------------------------------------------------------------*/
#include <cpp_stl.h>
#include <cpp_def.h>
#include <cpp_def_debug.h>
/*----------------------------------------------------------------*/
#include <opencv_basic.h>
/*----------------------------------------------------------------*/
#include <qt_basic.h>
/*----------------------------------------------------------------*/
#include <QT_SDK_LIB/QBase.h>
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
class MW_CFG
{
public:
	MW_CFG(void);
	~MW_CFG(void);
public:

	static QDomElement createElement_txt(
		QSharedPointer<QDomDocument> _Xml,
		const QString& _tagName,
		const QString& _data);

	static void createElement_txt_append(
		QSharedPointer<QDomDocument> _Xml,
		QDomElement & _parent,
		const QString & _tagName,
		const QString & _data);

public:
	QString  FILE_XML_CFG;
	QString  NODE_ROOT;
	QString  NODE_CFG;
	QString  NODE_CFG_PROPERTY;
	QString  DATA_CFG_PROPERTY;
public:
	QString getIpXml();
	void initCfgXml();
	virtual void CreateChildCfgNode(
		QSharedPointer<QDomDocument> _Xml,
		QDomElement& _parent);
	void initXmlCfgFile();

	static std::vector<float>	cvtQStr2StdVector(const QString _s);
	static std::vector<QString>	cvtQStr2StdVecQstr(const QString _s);

public:
	void InitLoad();
public:
	QSharedPointer<QDomDocument> mDomDoc;
	void LoadDefaultXmlDomDoc();

	QString getStringFromDomDoc(
		QSharedPointer<QDomDocument> _domDoc,
		const QString _propery,
		const QString _tagCfg);

	std::vector<float> 
		getVectorFromDomDoc_Pro(const QString _tagCfg);

	std::vector<QString> 
		getVectorQStrFromDomDoc_Pro(const QString _tagCfg);

	QString getStringFromDomDoc_Pro(const QString _tagCfg);

	float	getFloatFromDomDoc(
		QSharedPointer<QDomDocument> _domDoc,
		const QString _propery,
		const QString _tagCfg);

	float	getFloatFromDomDoc_Pro(
		const QString _tagCfg);

	int	getIntFromDomDoc(
		QSharedPointer<QDomDocument> _domDoc,
		const QString _propery,
		const QString _tagCfg);

	int	getIntFromDomDoc_Pro(
		const QString _tagCfg);

};

