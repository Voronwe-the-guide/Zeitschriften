#include <QGuiApplication>
#include <QApplication>
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
#include <DatenbankInfo/causgabeeditor.h>
#include <Helper/cerrordisplay.h>
#include <QSplashScreen>

#include <Settings/csettings.h>

#include <sqlite/sqlite3.h>

#include <QDebug>

#include <QTextEdit>
#include <Helper/qmlfactory.h>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication app(argc, argv);

	QPixmap pixmap("qrc:/Images/logo_GEO.png");
	QSplashScreen splash(pixmap);
	 splash.show();
	app.setOrganizationName("Blah");
	app.setOrganizationDomain("Blub");

	QMLFactory::registerTypes();
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
	CAusgabeEditor ausgabeEditor(&listenController);

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
	engine.rootContext()->setContextProperty("cAusgabenForJahrList",listenController.ausgabenForJahrDisplay());
    engine.rootContext()->setContextProperty("cZeitschriftenList",listenController.zeitschriftenDisplay());
    engine.rootContext()->setContextProperty("cZeitschriftenForJahr",listenController.zeitschriftenForJahrDisplay());
    engine.rootContext()->setContextProperty("cRubrikList",listenController.rubrikenListDisplay());
    engine.rootContext()->setContextProperty("cZeitschriftNameList",listenController.zeitschriftenListForSelection());
	engine.rootContext()->setContextProperty("cAusgabenList",listenController.ausgabenDisplay());
    engine.rootContext()->setContextProperty("cListenController",&listenController);
    engine.rootContext()->setContextProperty("cArtikelEditor",&artikelEditor);
     engine.rootContext()->setContextProperty("cZeitschriftEditor",&zeitschriftEditor);
	 engine.rootContext()->setContextProperty("cAusgabeEditor",&ausgabeEditor);
	engine.rootContext()->setContextProperty("cErrorDisplay",&errorDisplay);
	engine.rootContext()->setContextProperty("cSloganList",listenController.sloganList());
	engine.rootContext()->setContextProperty("cRedaktionList",listenController.redaktionList());
	engine.rootContext()->setContextProperty("cSprachenList",listenController.sprachenList());
	engine.rootContext()->setContextProperty("cWaehrungList",listenController.waehrungsList());


	engine.load(url);

	splash.close();
	app.exec();



	return 0;

}
