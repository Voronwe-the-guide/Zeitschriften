#include "csettings.h"
#include <QJsonDocument>
#include <QDebug>

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

QSize CSettingsData::getWindowSize() const
{
    return m_windowSize;
}
void CSettingsData::setWindowSize(const QSize &windowSize)
{
    m_windowSize = windowSize;
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
    GlobalSettings->setWindowSize(windowSize);
}

QJsonObject CSettings::getAsJSONObject()
{
	QJsonObject jsonObject;
    jsonObject["CurrentDB"]=GlobalSettings->getCurrentDB();
    jsonObject["WindowWidth"]=GlobalSettings->getWindowSize().width();
    jsonObject["WindowHeight"]=GlobalSettings->getWindowSize().height();

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
    QSize windowSize(jsonObject["WindowWidth"].toInt(),jsonObject["WindowHeight"].toInt());
    GlobalSettings->setWindowSize(windowSize);

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

QSize CSettings::getWindowSize() const
{
    return GlobalSettings->getWindowSize();
}

void CSettings::setWindowSize(const QSize &windowSize)
{
    GlobalSettings->setWindowSize(windowSize);
}

void CSettings::setWindowHeight(int height)
{
   QSize windowSize = GlobalSettings->getWindowSize();
   windowSize.setHeight(height);
    GlobalSettings->setWindowSize(windowSize);
   m_sizeSettingTimer.start();

}
void CSettings::setWindowWidth(int width)
{
    QSize windowSize = GlobalSettings->getWindowSize();
    windowSize.setHeight(width);
     GlobalSettings->setWindowSize(windowSize);
    m_sizeSettingTimer.start();

}

