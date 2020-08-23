#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <sqlite/sqlite3.h>
#include <DatenbankListen/cartikeldisplaylist.h>
#include <DatenbankListen/cjahrdisplaylist.h>
#include <DatenbankListen/causgabedisplaylist.h>
#include <DatenbankListen/clistencontroller.h>

/*static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++) {
	  printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	 return 0;
 }
*/

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	qRegisterMetaType<CArtikel>("CArtikel");

	sqlite3 *db;
	char *zErrMsg = 0;


	int rc = sqlite3_open_v2("GEO_Register.db",&db,SQLITE_OPEN_READWRITE,NULL);
	CListenController listenController(db);

    listenController.getJahre();



	//rc = sqlite3_exec(db, "SELECT * FROM Inhalte", callback, 0, &zErrMsg);

	QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Desktop/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);

	engine.rootContext()->setContextProperty("cArtikelList", listenController.artikelDisplay());
	engine.rootContext()->setContextProperty("cJahreList",listenController.jahrgaengeDisplay());
	engine.rootContext()->setContextProperty("cAusgabenList",listenController.ausgabenDisplay());
    engine.rootContext()->setContextProperty("cListenController",&listenController);
    engine.load(url);

	app.exec();

	sqlite3_close(db);

	return 0;

}
