#include "csettings.h"
#include <QJsonDocument>
#include <QDebug>

CSettings::CSettings()
{
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
	m_currentDB="";
    m_windowSize.setWidth(1200);
    m_windowSize.setHeight(600);
}

QJsonObject CSettings::getAsJSONObject()
{
	QJsonObject jsonObject;
	jsonObject["CurrentDB"]=m_currentDB;
    jsonObject["WindowWidth"]=m_windowSize.width();
    jsonObject["WindowHeight"]=m_windowSize.height();

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

    m_currentDB =jsonObject["CurrentDB"].toString();
    m_windowSize.setWidth(jsonObject["WindowWidth"].toInt());
    m_windowSize.setHeight(jsonObject["WindowHeight"].toInt());

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
	return m_currentDB;
}


void CSettings::setCurrentDB(const QString &currentDBPath)
{

	m_currentDB = currentDBPath;
	emit dbUpdated(m_currentDB);


}

QSize CSettings::getWindowSize() const
{
    return m_windowSize;
}

void CSettings::setWindowSize(const QSize &windowSize)
{
    m_windowSize = windowSize;
}

void CSettings::setWindowHeight(int height)
{
   m_windowSize.setHeight(height);
   m_sizeSettingTimer.start();

}
void CSettings::setWindowWidth(int width)
{
    m_windowSize.setWidth(width);
    m_sizeSettingTimer.start();

}

