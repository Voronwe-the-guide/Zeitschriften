#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <sqlite/sqlite3.h>
#include <DatenbankListen/cartikeldisplaylist.h>
#include <DatenbankListen/cjahrdisplaylist.h>
#include <DatenbankListen/causgabedisplaylist.h>
#include <QDebug>

#include <QCoreApplication>

int main(int argc, char *argv[])
{
 //   QCoreApplication a(argc, argv);
    printf("Hello2");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    printf("Hello2");
    qDebug()<<"start";
    QGuiApplication app(argc, argv);

	qRegisterMetaType<CArtikel>("CArtikel");

	sqlite3 *db;
	char *zErrMsg = 0;


	int rc = sqlite3_open_v2("GEO_Register.db",&db,SQLITE_OPEN_READWRITE,NULL);
	CJahrDisplayList jahrgaengeDisplay(db);
	jahrgaengeDisplay.GetDBRequest();

	CAusgabeDisplayList ausgabenDisplay(db);
	CArtikelDisplayList artikelDisplay(db);
//	artikelDisplay.GetDBRequest();


	//rc = sqlite3_exec(db, "SELECT * FROM Inhalte", callback, 0, &zErrMsg);

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);

	engine.rootContext()->setContextProperty("cArtikelList",&artikelDisplay);
	engine.rootContext()->setContextProperty("cJahreList",&jahrgaengeDisplay);
	engine.rootContext()->setContextProperty("cAusgabenList",&ausgabenDisplay);
	engine.load(url);

	app.exec();

	sqlite3_close(db);

	return 0;

}
