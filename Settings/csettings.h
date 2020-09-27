#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QFileInfo>
#include <QJsonObject>
#include <QSize>
#include <QTimer>
#include <QDir>

class CSettingsData
{

public:
    QString getCurrentDB() const;
    void setCurrentDB(const QString &currentDBPath);
    QDir getCurrentDBPath() const;

    QSize getWindowSize() const;
    void setWindowSize(const QSize &windowSize);

private:
    QString m_currentDB;
    QSize m_windowSize;

};

class CSettings  : public QObject
{
	Q_OBJECT
    Q_PROPERTY(QString currentDB	 READ getCurrentDB NOTIFY dbUpdated)
public:
/*    static CSettings* getInstance()
    {
        if (nullptr == sm_Instance) {sm_Instance = new CSettings(); }
        return sm_Instance;
    }
*/
    CSettings();
	CSettings (std::string &JsonInfo);
	CSettings (QJsonObject &jsonObject);

	CSettings (const  CSettings&) = default;
	CSettings& operator=(const CSettings&) = default;
	CSettings ( CSettings&&) = default;
	CSettings& operator=( CSettings&&) = default;

    static CSettingsData* getConfiguration();
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

 //   static CSettings* sm_Instance;
//	QString m_currentDB;
//    QSize m_windowSize;
    QTimer m_sizeSettingTimer;
};


//CSettings* CSettings::sm_Instance = nullptr;

#endif // CSETTINGS_H
