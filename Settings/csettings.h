#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QFileInfo>
#include <QJsonObject>
#include <QJsonArray>
#include <QSize>
#include <QTimer>
#include <QDir>
#include <QQuickItem>

#include <Settings/cwindowinfo.h>



class CSettingsData
{

public:
	CSettingsData();

	QString getCurrentDB() const;
    void setCurrentDB(const QString &currentDBPath);
    QDir getCurrentDBPath() const;

	QSize getWindowSize(WindowNames::eWindow windowName) const;
	void setWindowSize(WindowNames::eWindow windowName, const QSize &windowSize);
	QStringList getWindowNames();

	QJsonArray getSizeAsJSON();
	void setSizeFromJSON(QJsonArray array);


private:
    QString m_currentDB;

	QMap<QString, CWindowInfo> m_WindowMap;
	CWindowInfo m_defaultInfo;

};



class CSettings  : public QObject
{
	Q_OBJECT
    Q_PROPERTY(QString currentDB	 READ getCurrentDB NOTIFY dbUpdated)

public:

    CSettings();
	CSettings (std::string &JsonInfo);
	CSettings (QJsonObject &jsonObject);


    static CSettingsData* getConfiguration();
	QJsonObject getAsJSONObject();
	std::string getDataInJSONFormat();
	void readDataFromJSONFormat(QJsonObject &jsonObject);
	void readDataFromJSONFormat(std::string &json);


public slots:
    QString getCurrentDB() const;
    void setCurrentDB(const QString &currentDBPath);
	void setWindowHeight(WindowNames::eWindow windowName,int height);
	void setWindowWidth(WindowNames::eWindow windowName,int width);

	QSize getWindowSize(WindowNames::eWindow windowName) const;
	void setWindowSize(WindowNames::eWindow windowName, const QSize &windowSize);




    void writeSettingsFile();
    void loadSettingsFile();
    void cleanData();



signals:
	void dbUpdated(QString absolutePath);

private:

	 QTimer m_sizeSettingTimer;
};



#endif // CSETTINGS_H
