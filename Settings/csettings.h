#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QFileInfo>
#include <QJsonObject>
class CSettings  : public QObject
{
	Q_OBJECT
public:
	CSettings();
	CSettings (std::string &JsonInfo);
	CSettings (QJsonObject &jsonObject);

	CSettings (const  CSettings&) = default;
	CSettings& operator=(const CSettings&) = default;
	CSettings ( CSettings&&) = default;
	CSettings& operator=( CSettings&&) = default;

	void writeSettingsFile();
	void loadSettingsFile();
	void cleanData();

	QJsonObject getAsJSONObject();
	std::string getDataInJSONFormat();
	void readDataFromJSONFormat(QJsonObject &jsonObject);
	void readDataFromJSONFormat(std::string &json);

public slots:
	QString currentDB() const;
//	void setCurrentDB(const QFileInfo &currentDB);
	void setCurrentDB(const QString &currentDBPath);

signals:
	void dbUpdated(QString absolutePath);

private:
	QString m_currentDB;
};

#endif // CSETTINGS_H
