#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include <DatenbankListen/cartikel.h>
#include <DatenbankListen/cjahr.h>
#include <DatenbankListen/causgabe.h>
#include <DatenbankListen/clistencontroller.h>
#include <DatenbankInfo/ccolumn.h>
#include <DatenbankInfo/cartikeleditor.h>
#include <DatenbankInfo/czeitschrifteditor.h>
#include <Helper/cerrordisplay.h>


#include <Settings/csettings.h>

#include <sqlite/sqlite3.h>

#include <QDebug>

#include <QTextEdit>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
	app.setOrganizationName("Blah");
	app.setOrganizationDomain("Blub");

	qRegisterMetaType<CArtikel>("CArtikel");
	qRegisterMetaType<CAusgabe>("CAusgabe");
    qRegisterMetaType<CZeitschrift>("CZeitschrift");
	qRegisterMetaType<CJahr>("CJahr");
	qRegisterMetaType<CColumn>("CColumn");

	CErrorDisplay errorDisplay;
//	 CSettings settings = globalSettings::g_settings;
  //  g_settingsPointer = &settings;

    CSettings settings;
    CListenController listenController;
    listenController.openDB(settings.getCurrentDB());
    QObject::connect(&settings, &CSettings::dbUpdated, &listenController, &CListenController::openDB);
	QObject::connect(&listenController, &CListenController::errorMessage, &errorDisplay, &CErrorDisplay::gotErrorMessage);

    CArtikelEditor artikelEditor(&listenController);
    CZeitschriftEditor zeitschriftEditor(&listenController);

	QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    const QUrl url(QStringLiteral("qrc:/Desktop/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);


    engine.rootContext()->setContextProperty("sqliteversion", QString(sqlite3_libversion()));
    engine.rootContext()->setContextProperty("qtversion", QString(qVersion()));
    engine.rootContext()->setContextProperty("cSettings",&settings);
	engine.rootContext()->setContextProperty("cArtikelList", listenController.artikelDisplay());
	engine.rootContext()->setContextProperty("cJahreList",listenController.jahrgaengeDisplay());
	engine.rootContext()->setContextProperty("cAusgabenList",listenController.ausgabenDisplay());
    engine.rootContext()->setContextProperty("cZeitschriftenList",listenController.zeitschriftenDisplay());
    engine.rootContext()->setContextProperty("cZeitschriftenForJahr",listenController.zeitschriftenForJahrDisplay());
    engine.rootContext()->setContextProperty("cRubrikList",listenController.rubrikenListDisplay());
    engine.rootContext()->setContextProperty("cZeitschriftNameList",listenController.zeitschriftenListForSelection());
    engine.rootContext()->setContextProperty("cListenController",&listenController);
    engine.rootContext()->setContextProperty("cArtikelEditor",&artikelEditor);
     engine.rootContext()->setContextProperty("cZeitschriftEditor",&zeitschriftEditor);
	engine.rootContext()->setContextProperty("cErrorDisplay",&errorDisplay);
    engine.load(url);

	app.exec();



	return 0;

}
