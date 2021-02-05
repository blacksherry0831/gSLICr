#include "mw_cfg.hpp"
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
MW_CFG::MW_CFG(void)
{
	FILE_XML_CFG = "cfg.mainwindow.xml";
	NODE_ROOT = "config";
	NODE_CFG = "cfg.data";
	NODE_CFG_PROPERTY = "property";
	DATA_CFG_PROPERTY = "property.name";
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
MW_CFG::~MW_CFG(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
QString MW_CFG::getIpXml()
{
	QString fullPath;

	const QString  fullDir = QApplication::applicationDirPath();

	fullPath.append(fullDir).append(QDir::separator()).
		append(FILE_XML_CFG);

	return fullPath;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
QDomElement MW_CFG::createElement_txt(
	QSharedPointer<QDomDocument> _Xml,
	const QString & _tagName,
	const QString & _data)
{

	QDomElement element_t = _Xml->createElement(_tagName);
	QDomText data_v = _Xml->createTextNode(_data);
	element_t.appendChild(data_v);

	return element_t;

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MW_CFG::createElement_txt_append(
	QSharedPointer<QDomDocument> _Xml,
	QDomElement& _parent,
	const QString & _tagName,
	const QString & _data)
{
	const QDomElement dom_ele_t= createElement_txt(_Xml, _tagName, _data);
	_parent.appendChild(dom_ele_t);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MW_CFG::LoadDefaultXmlDomDoc()
{
	mDomDoc = QBase::fs_read_xml(getIpXml());
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
QString MW_CFG::getStringFromDomDoc(
	QSharedPointer<QDomDocument> _domDoc,
	const QString _propery,
	const QString _tagCfg)
{
	QString     data_t;
	QDomElement docElem = _domDoc->documentElement();

	QDomNodeList rootlist = docElem.childNodes();

	for (int i = 0; i < rootlist.count(); i++) {

		QDomNode node_feature_classify = rootlist.at(i);
		QDomNodeList node_feature_sub = node_feature_classify.childNodes();

		QDomElement property_t = node_feature_classify.firstChildElement(NODE_CFG_PROPERTY);
		QString   property_data_t = property_t.text();

		if (property_data_t == _propery) {
			QDomElement tag_t = node_feature_classify.firstChildElement(_tagCfg);
			data_t = tag_t.text();
		}

	}

	return     data_t;

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::vector<float> MW_CFG::getVectorFromDomDoc_Pro(const QString _tagCfg)
{
	const	QString data = getStringFromDomDoc(
												mDomDoc,
												DATA_CFG_PROPERTY,
												_tagCfg);
	const	std::vector<float> vdata = cvtQStr2StdVector(data);
	return vdata;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::vector<QString> MW_CFG::getVectorQStrFromDomDoc_Pro(const QString _tagCfg)
{
	const	QString data = getStringFromDomDoc(
		mDomDoc,
		DATA_CFG_PROPERTY,
		_tagCfg);
	return		cvtQStr2StdVecQstr(data);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
QString MW_CFG::getStringFromDomDoc_Pro(const QString _tagCfg)
{
	return getStringFromDomDoc(
		mDomDoc,
		DATA_CFG_PROPERTY,
		_tagCfg);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float MW_CFG::getFloatFromDomDoc(
	QSharedPointer<QDomDocument> _domDoc,
	const QString _propery,
	const QString _tagCfg)
{
	QString     data_t = getStringFromDomDoc(_domDoc, _propery, _tagCfg);
	Q_ASSERT(!data_t.isEmpty());
	return  data_t.toFloat();
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float MW_CFG::getFloatFromDomDoc_Pro(const QString _tagCfg)
{
	return getFloatFromDomDoc(
		mDomDoc,
		DATA_CFG_PROPERTY,
		_tagCfg);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int MW_CFG::getIntFromDomDoc(
	QSharedPointer<QDomDocument> _domDoc,
	const QString _propery,
	const QString _tagCfg)
{
	QString     data_t = getStringFromDomDoc(_domDoc, _propery, _tagCfg);
	Q_ASSERT(!data_t.isEmpty());
	return  data_t.toInt();
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int MW_CFG::getIntFromDomDoc_Pro(const QString _tagCfg)
{
	return getIntFromDomDoc(
		mDomDoc,
		DATA_CFG_PROPERTY,
		_tagCfg);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MW_CFG::initCfgXml()
{
#if defined(QT_VERSION)
	QSharedPointer<QDomDocument> Xml = QSharedPointer<QDomDocument>(new QDomDocument());
	QDomProcessingInstruction Qdp_t = Xml->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	Xml->appendChild(Qdp_t);
	QDomElement root = Xml->createElement(NODE_ROOT);
	Xml->appendChild(root);
#endif // defined(QT_VERSION)

	if (!Xml.isNull())
	{
		QDomElement root = Xml->documentElement();


		{
			QDomElement cfg_node = Xml->createElement(NODE_CFG);
			{
				CreateChildCfgNode(Xml, cfg_node);
			}
			root.appendChild(cfg_node);
		}

	}

	QBase::fs_write_xml(getIpXml(), Xml);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MW_CFG::CreateChildCfgNode(QSharedPointer<QDomDocument> _Xml, QDomElement & _parent)
{
	Q_ASSERT(!_Xml->isNull());
	Q_ASSERT(!_parent.isNull());
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MW_CFG::initXmlCfgFile()
{

	const QString xml_path = getIpXml();
	QFile  xml_file(xml_path);

	if (xml_file.exists()) {

	}
	else {
		initCfgXml();
	}

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::vector<float> MW_CFG::cvtQStr2StdVector(const QString _s)
{
	QStringList sl= _s.split(",");
	std::vector<float> data;
	for each (auto var in sl){
		data.push_back(	var.toFloat());
	}
	return data;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::vector<QString> MW_CFG::cvtQStr2StdVecQstr(const QString _s)
{
	QStringList sl = _s.split(",");
	std::vector<QString> data;
	for each (auto var in sl) {
		data.push_back(var);
	}
	return data;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MW_CFG::InitLoad()
{
	this->initXmlCfgFile();
	this->LoadDefaultXmlDomDoc();
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/