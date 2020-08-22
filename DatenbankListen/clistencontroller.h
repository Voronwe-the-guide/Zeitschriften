#ifndef CLISTENCONTROLLER_H
#define CLISTENCONTROLLER_H

#include <QObject>
#include <sqlite/sqlite3.h>
#include <DatenbankListen/cartikeldisplaylist.h>
#include <DatenbankListen/cjahrdisplaylist.h>
#include <DatenbankListen/causgabedisplaylist.h>

class CListenController : public QObject
{
	Q_OBJECT
public:
	explicit CListenController(sqlite3 *db,QObject *parent = nullptr);

	CJahrDisplayList *jahrgaengeDisplay();
	CAusgabeDisplayList *ausgabenDisplay();
	CArtikelDisplayList *artikelDisplay();

public slots:
	void getAusgabenForJahr(int jahr);

signals:


private:
	sqlite3 *m_db;
	CJahrDisplayList *m_jahrgaengeDisplay;
		CAusgabeDisplayList *m_ausgabenDisplay;
		CArtikelDisplayList *m_artikelDisplay;



};

#endif // LISTENCONTROLLER_H
