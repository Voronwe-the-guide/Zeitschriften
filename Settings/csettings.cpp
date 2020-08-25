#include "csettings.h"
#include <QJsonDocument>
#include <QDebug>

CSettings::CSettings()
{
	cleanData();
	loadSettingsFile();

	connect(this, &CSettings::dbUpdated, this, &CSettings::writeSettingsFile);

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
}

QJsonObject CSettings::getAsJSONObject()
{
	QJsonObject jsonObject;
	jsonObject["CurrentDB"]=m_currentDB;
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
}
void CSettings::readDataFromJSONFormat(std::string &json)
{
	QByteArray stationBA = QByteArray::fromStdString(json);
	QJsonDocument loadDoc(QJsonDocument::fromJson(stationBA));
	QJsonObject stationInfoObject = loadDoc.object();
	readDataFromJSONFormat(stationInfoObject);
}

QString CSettings::currentDB() const
{
	return m_currentDB;
}

/*void CSettings::setCurrentDB(const QFileInfo &currentDB)
{
	m_currentDB = currentDB;
	QString a = m_currentDB.absolutePath();
	emit dbUpdated(m_currentDB.absolutePath());
}
*/
void CSettings::setCurrentDB(const QString &currentDBPath)
{
	//QFileInfo currentDB(currentDBPath);
	//setCurrentDB(currentDB);
	m_currentDB = currentDBPath;
	emit dbUpdated(m_currentDB);


}
