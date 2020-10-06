#ifndef CWINDOWINFO_H
#define CWINDOWINFO_H

#include <QSize>
#include <QObject>
#include <QQuickItem>
#include <QJsonObject>
class WindowNames : public QObject
{
	Q_OBJECT
public:
	enum eWindow
	{
		WINDOW_MAIN = 0,
		WINDOW_EDIT_ARTIKEL,
		WINDOW_EDIT_AUSGABE,
		WINDOW_EDIT_ZEITSCHRIFT,
		WINDOW_LIST_AUSGABE,
		WINDOW_LIST_ZEITSCHRIFT,
	};
	Q_ENUM(eWindow)
	explicit WindowNames(QObject *parent = nullptr);


};

//To give it to QML
class WindowInfoQML: public QObject
{
	Q_OBJECT
public:
	enum eWindow
	{
		WINDOW_MAIN = WindowNames::WINDOW_MAIN,
		WINDOW_EDIT_ARTIKEL = WindowNames::WINDOW_EDIT_ARTIKEL,
		WINDOW_EDIT_AUSGABE = WindowNames::WINDOW_EDIT_AUSGABE,
		WINDOW_EDIT_ZEITSCHRIFT = WindowNames::WINDOW_EDIT_ZEITSCHRIFT,
		WINDOW_LIST_AUSGABE = WindowNames::WINDOW_LIST_AUSGABE,
		WINDOW_LIST_ZEITSCHRIFT = WindowNames::WINDOW_LIST_ZEITSCHRIFT
	};
	Q_ENUM(eWindow)
	//explicit WindowNames(QObject *parent = nullptr);

	// Do not forget to declare your class to the QML system.
	 static inline void qmlRegister(const char * libraryName, int versionMajor, int versionMinor)
	  {
		 qmlRegisterType<WindowInfoQML>(libraryName, versionMajor, versionMinor, "WindowNames");
	 }

};

class CWindowInfo
{
public:
	CWindowInfo();
	CWindowInfo(QSize size);
	CWindowInfo (const  CWindowInfo&) = default;
	CWindowInfo& operator=(const CWindowInfo&) = default;
	CWindowInfo ( CWindowInfo&&) = default;
	CWindowInfo& operator=( CWindowInfo&&) = default;

	virtual ~CWindowInfo() = default;

	QSize getWindowSize() const;
	void setWindowSize(const QSize &windowSize);

	QJsonObject getAsJSON();
	void setFromJSON(QJsonObject array);

private:
	QSize m_windowSize;

};

#endif // CWINDOWINFO_H
