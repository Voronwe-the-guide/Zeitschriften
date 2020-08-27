#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include <DatenbankListen/cartikel.h>
#include <DatenbankListen/cjahr.h>
#include <DatenbankListen/causgabe.h>
#include <DatenbankListen/clistencontroller.h>
#include <DatenbankInfo/ccolumn.h>

#include <Settings/csettings.h>

#include <QDebug>



int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
	app.setOrganizationName("Blah");
	app.setOrganizationDomain("Blub");

	qRegisterMetaType<CArtikel>("CArtikel");
	qRegisterMetaType<CAusgabe>("CAusgabe");
	qRegisterMetaType<CJahr>("CJahr");
	qRegisterMetaType<CColumn>("CColumn");
	CSettings settings;

    CListenController listenController;
	listenController.openDB(settings.currentDB());
	QObject::connect(&settings, &CSettings::dbUpdated, &listenController, &CListenController::openDB);


	QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Desktop/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);

	engine.rootContext()->setContextProperty("cSettings",&settings);
	engine.rootContext()->setContextProperty("cArtikelList", listenController.artikelDisplay());
	engine.rootContext()->setContextProperty("cJahreList",listenController.jahrgaengeDisplay());
	engine.rootContext()->setContextProperty("cAusgabenList",listenController.ausgabenDisplay());
    engine.rootContext()->setContextProperty("cListenController",&listenController);

    engine.load(url);

	app.exec();



	return 0;

}
