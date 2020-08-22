#ifndef CLISTENCONTROLLER_H
#define CLISTENCONTROLLER_H

#include <QObject>
#include <sqlite/sqlite3.h>
#include <DatenbankListen/cartikeldisplaylist.h>
#include <DatenbankListen/cjahrdisplaylist.h>
#include <DatenbankListen/causgabedisplaylist.h>
#include <DatenbankInfo/ccolumn.h>

class CListenController : public QObject
{
	Q_OBJECT
public:
	explicit CListenController(sqlite3 *db,QObject *parent = nullptr);

	CJahrDisplayList *jahrgaengeDisplay();
	CAusgabeDisplayList *ausgabenDisplay();
	CArtikelDisplayList *artikelDisplay();

public slots:
    void getJahre();
	void getAusgabenForJahr(int jahr);
    void getArtikelForAusgabe(int jahr, int ausgabe);
    void searchArtikel(QString searchElement);

signals:


private:
    QString setSearchStringAsSQL();
    void getTableNamesFromDB();

    sqlite3 *m_db;
	CJahrDisplayList *m_jahrgaengeDisplay;
    CAusgabeDisplayList *m_ausgabenDisplay;
    CArtikelDisplayList *m_artikelDisplay;
    QString m_searchElement;

    QMap<QString, CColumn> m_searchTables;
    QMap<QString, CColumn> m_searchTablesSetting;



};

#endif // LISTENCONTROLLER_H
