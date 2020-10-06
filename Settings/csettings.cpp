#include "csettings.h"
#include <QJsonDocument>
#include <QDebug>

CSettingsData::CSettingsData():
	m_defaultInfo(QSize(400,400))
{
	m_WindowMap[QVariant::fromValue(WindowNames::WINDOW_MAIN).toString()] =CWindowInfo(QSize(1000,800));
	m_WindowMap[QVariant::fromValue(WindowNames::WINDOW_EDIT_ARTIKEL).toString()] =CWindowInfo(QSize(1000,600));
	m_WindowMap[QVariant::fromValue(WindowNames::WINDOW_EDIT_AUSGABE).toString()] =CWindowInfo(QSize(600,400));
	m_WindowMap[QVariant::fromValue(WindowNames::WINDOW_EDIT_ZEITSCHRIFT).toString()] =CWindowInfo(QSize(600,400));
	m_WindowMap[QVariant::fromValue(WindowNames::WINDOW_LIST_AUSGABE).toString()] =CWindowInfo(QSize(900,900));
	m_WindowMap[QVariant::fromValue(WindowNames::WINDOW_LIST_ZEITSCHRIFT).toString()] =CWindowInfo(QSize(600,400));


}

QString CSettingsData::getCurrentDB() const
{
    return m_currentDB;
}
void CSettingsData::setCurrentDB(const QString &currentDBPath)
{
    m_currentDB = currentDBPath;
}

QDir CSettingsData::getCurrentDBPath() const
{
    QFileInfo DBAdress(CSettings::getConfiguration()->getCurrentDB());
    QDir DBPath(DBAdress.absolutePath());

    return DBPath;
}

QSize CSettingsData::getWindowSize(WindowNames::eWindow windowName) const
{
	if (m_WindowMap.contains(QVariant::fromValue(windowName).toString()))
	{
		return m_WindowMap.value(QVariant::fromValue(windowName).toString()).getWindowSize();
	}

	return m_defaultInfo.getWindowSize();
}
void CSettingsData::setWindowSize(WindowNames::eWindow windowName, const QSize &windowSize)
{
	CWindowInfo info(windowSize);
	if (m_WindowMap.contains(QVariant::fromValue(windowName).toString()))
	{
		info = m_WindowMap[QVariant::fromValue(windowName).toString()];
		info.setWindowSize(windowSize);
	}

	m_WindowMap[QVariant::fromValue(windowName).toString()] = windowSize;
}

QStringList CSettingsData::getWindowNames()
{
	return m_WindowMap.keys();
}

void CSettingsData::setSizeFromJSON(QJsonArray DataArray)
{
	for (int i=0; i<DataArray.count(); i++)
	{
	   QJsonObject DataObject = DataArray[i].toObject();
	   QJsonObject WindowInfo = DataObject["Details"].toObject();
	   CWindowInfo info;
	   info.setFromJSON(WindowInfo);
	   m_WindowMap[DataObject["Window"].toString()]=info;
   }
}

QJsonArray CSettingsData::getSizeAsJSON()
{
	QJsonArray jsonArray;

	QMapIterator<QString, CWindowInfo> i(m_WindowMap);
	while (i.hasNext())
	{
		i.next();

		CWindowInfo info = i.value();
		QJsonObject windowInfo;
		windowInfo["Window"] = i.key();
		windowInfo["Details"] = info.getAsJSON();
		jsonArray.append(windowInfo);
	}

	return jsonArray;


}



QSharedPointer<CSettingsData> GlobalSettings;

CSettingsData* CSettings::getConfiguration()
{
    return GlobalSettings.data();
}

CSettings::CSettings()
{
    CSettingsData *setting = new CSettingsData;
    GlobalSettings.reset(setting);

    cleanData();
	loadSettingsFile();

	connect(this, &CSettings::dbUpdated, this, &CSettings::writeSettingsFile);
    m_sizeSettingTimer.setInterval(1000);
    connect(&m_sizeSettingTimer,&QTimer::timeout,this,&CSettings::writeSettingsFile);

}

CSettings::CSettings (std::string &JsonInfo):
	CSettings()
{
	readDataFromJSONFormat(JsonInfo);
}


CSettings::CSettings (QJsonObject &jsonObject):
	CSettings()
{
	readDataFromJSONFormat(jsonObject);
}


void CSettings::loadSettingsFile()
{
	QFile file ("settings.json");
	if (!(file.open(QIODevice::ReadOnly | QIODevice::Text)))
	{
		writeSettingsFile();
	}
	QString fileName = file.fileName();
	QString settings = file.readAll();
	file.close();
	QJsonDocument document = QJsonDocument::fromJson(settings.toUtf8());
	QJsonObject object = document.object();
	readDataFromJSONFormat(object);
	int i=5;
}

void CSettings::writeSettingsFile()
{
    m_sizeSettingTimer.stop();
    QFile file ("settings.json");
	if (!(file.open(QIODevice::WriteOnly | QIODevice::Text)))
	{
		//No setting-file available
	}

	QJsonDocument jsonDoc = QJsonDocument(getAsJSONObject());
	file.write(jsonDoc.toJson());
	file.close();
}

void CSettings::cleanData()
{
    GlobalSettings->setCurrentDB("");
    QSize windowSize(1200,600);
	GlobalSettings->setWindowSize(WindowNames::WINDOW_MAIN,windowSize);
}

QJsonObject CSettings::getAsJSONObject()
{
	QJsonObject jsonObject;
    jsonObject["CurrentDB"]=GlobalSettings->getCurrentDB();
	jsonObject["WindowList"]=GlobalSettings->getSizeAsJSON();

	return jsonObject;


}
std::string CSettings::getDataInJSONFormat()
{
	QJsonObject stationObject = getAsJSONObject();
	QJsonDocument jsonDoc = QJsonDocument(stationObject);
	std::string jsonText = jsonDoc.toJson().toStdString();
	return jsonText;

}
void CSettings::readDataFromJSONFormat(QJsonObject &jsonObject)
{
	if (jsonObject.count()<0)
	{
		qDebug()<<"Wrong Setting array";
		return;
	}

	cleanData();

    GlobalSettings->setCurrentDB(jsonObject["CurrentDB"].toString());
	GlobalSettings->setSizeFromJSON(jsonObject["WindowList"].toArray());

}
void CSettings::readDataFromJSONFormat(std::string &json)
{
	QByteArray stationBA = QByteArray::fromStdString(json);
	QJsonDocument loadDoc(QJsonDocument::fromJson(stationBA));
	QJsonObject stationInfoObject = loadDoc.object();
	readDataFromJSONFormat(stationInfoObject);
}

QString CSettings::getCurrentDB() const
{
    return GlobalSettings->getCurrentDB();
}


void CSettings::setCurrentDB(const QString &currentDBPath)
{

    GlobalSettings->setCurrentDB(currentDBPath);
    emit dbUpdated(GlobalSettings->getCurrentDB());


}

QSize  CSettings::getWindowSize(WindowNames::eWindow windowName) const
{
	return GlobalSettings->getWindowSize(windowName);

}
void  CSettings::setWindowSize(WindowNames::eWindow windowName, const QSize &windowSize)
{
	GlobalSettings->setWindowSize(windowName,windowSize);

}

void CSettings::setWindowHeight(WindowNames::eWindow windowName,int height)
{
   QSize windowSize = GlobalSettings->getWindowSize(windowName);
   windowSize.setHeight(height);
	GlobalSettings->setWindowSize(windowName,windowSize);
   m_sizeSettingTimer.start();

}
void CSettings::setWindowWidth(WindowNames::eWindow windowName,int width)
{
	QSize windowSize = GlobalSettings->getWindowSize(windowName);
	windowSize.setWidth(width);
	 GlobalSettings->setWindowSize(windowName,windowSize);
    m_sizeSettingTimer.start();

}

