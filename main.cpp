#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <sqlite/sqlite3.h>
#include <DatenbankListen/cartikeldisplaylist.h>
#include <DatenbankListen/cjahrdisplaylist.h>
#include <DatenbankListen/causgabedisplaylist.h>
#include <DatenbankListen/clistencontroller.h>
#include <QDebug>

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



    CListenController listenController;
	listenController.openDB("file:///D:/QTTest/Zeitschriften/GEO_Register.db"); //("GEO_Register.db");
  //  listenController.getJahre();

//	sqlite3 *db;
//	  int rc = sqlite3_open_v2("file:///D:/QTTest/Zeitschriften/GEO_Register.db"/*"GEO_Register.db"*/,&db,(SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI),NULL);
	// rc = sqlite3_open_v2("file:///D:/GEO/GEO_Register.db",&db,SQLITE_OPEN_READWRITE,NULL);
/*	if (rc != SQLITE_OK)
	{
		qDebug()<<"Could not open SQLite DB ";//<<DBPath;
		return false;
	}
	*/

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



	return 0;

}
