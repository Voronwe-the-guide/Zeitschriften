#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QFileInfo>
#include <QJsonObject>
#include <QSize>
#include <QTimer>
class CSettings  : public QObject
{
	Q_OBJECT
    Q_PROPERTY(QString currentDB	 READ getCurrentDB NOTIFY dbUpdated)
public:
	CSettings();
	CSettings (std::string &JsonInfo);
	CSettings (QJsonObject &jsonObject);

	CSettings (const  CSettings&) = default;
	CSettings& operator=(const CSettings&) = default;
	CSettings ( CSettings&&) = default;
	CSettings& operator=( CSettings&&) = default;


	QJsonObject getAsJSONObject();
	std::string getDataInJSONFormat();
	void readDataFromJSONFormat(QJsonObject &jsonObject);
	void readDataFromJSONFormat(std::string &json);


public slots:
    QString getCurrentDB() const;
    void setCurrentDB(const QString &currentDBPath);
    QSize getWindowSize() const;
    void setWindowSize(const QSize &windowSize);
    void setWindowHeight(int height);
    void setWindowWidth(int width);

    void writeSettingsFile();
    void loadSettingsFile();
    void cleanData();



signals:
	void dbUpdated(QString absolutePath);

private:
	QString m_currentDB;
    QSize m_windowSize;
    QTimer m_sizeSettingTimer;
};

#endif // CSETTINGS_H
