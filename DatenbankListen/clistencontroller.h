#ifndef CLISTENCONTROLLER_H
#define CLISTENCONTROLLER_H

#include <QObject>
#include <QtSql>
#include <sqlite/sqlite3.h>
#include <DatenbankListen/cartikeldisplaylist.h>
#include <DatenbankListen/cjahrdisplaylist.h>
#include <DatenbankListen/causgabedisplaylist.h>
#include <DatenbankListen/czeitschriftdisplaylist.h>
#include <DatenbankListen/crubriklistdisplay.h>
#include <DatenbankInfo/ccolumn.h>


class CListenController : public QObject
{
	Q_OBJECT
public:
    explicit CListenController(QObject *parent = nullptr);
    ~CListenController();


	CJahrDisplayList *jahrgaengeDisplay();
	CAusgabeDisplayList *ausgabenForJahrDisplay();
	CAusgabeDisplayList *ausgabenDisplay();
	CArtikelDisplayList *artikelDisplay();
    CZeitschriftDisplayList *zeitschriftenDisplay();
    CZeitschriftDisplayList *zeitschriftenForJahrDisplay();
    CSelectionListDisplay *rubrikenListDisplay();
    CSelectionListDisplay *zeitschriftenListForSelection();
	CSelectionListDisplay *sloganList();
	CSelectionListDisplay *redaktionList();
	CSelectionListDisplay *sprachenList();
	CSelectionListDisplay *waehrungsList();



public slots:
    bool openDB(QString DBPath);

    void getListOfZeitschriften();
	void getListOfAusgaben(bool atStartup = false);
    void recallArtikelList();
    void getOverview();

    void getJahreForZeitschrift(QStringList zeitschriften);
    void getLowerInfoForJahr(int jahr);
    int getZeitschriftenForJahr(int Jahr);
    void getAusgabenForJahr(int jahr);
    void getAusgabenForZeitschrift(QString zeitschrift, int jahr);

    void getArtikelForAusgabe(QString zeitschrift,int jahr, int ausgabe);

	void updateInhalteTable(const CArtikel &Artikel);
    int addNewEmptyRowToInhalte();

    void updateZeitschriftenTable( const CZeitschrift &Zeitschrift, bool refresh);
    int addNewEmptyRowToZeitschriftTable();

    void updateAusgabenTable( const CAusgabe &Ausgabe);
    int addNewEmptyRowToAusgabenTable();

    void deleteArtikel(int index);

    void setRubrikDisplay(QString zeitschrift);
    void updateRubrikListDisplay(QString filter);

    void setZeitschriftSelectionDisplay();
    void updateZeitschriftSelectionDisplay(QString filter);

	void setSloganDisplay(QString zeitschrift);
	void setRedaktionDisplay(QString zeitschrift);
	void updateSloganListDisplay(QString filter);
	void updateWaehrungListDisplay(QString filter);
	void updateRedaktionListDisplay(QString filter);


    /*!
     * \brief getArtikelByIndex
     * \param index
     * \param changeOtherLists: Soll nur der Artikel gefunden werden, oder auch Jahr + Ausgabe nur diesen anzeigen?
     */
    CArtikel getArtikelByIndex(int index);
    CZeitschrift getZeitschriftByIndex(int index);
    CAusgabe getAusgabeByIndex(int dbIndex);

	CZeitschrift getZeitschriftByName(const QString& name);
	CAusgabe getAusgabeByData( CAusgabeDisplayList::searchStruct& name);

    void searchArtikel(QString searchElement);

    QString getSearchElement() const;
    void setSearchElement(const QString &searchElement);

    void addOrRemoveZeitschrift(int index);

signals:
	void errorMessage(QString sender, QString Message);
    void newZeitschriftDetected(CZeitschrift zeitschrift);
    void newAusgabeDetected(CAusgabe ausgabe);

private:
    QString setSearchStringAsSQL();
    QString setZeitschriftenAsSQL();
    void getTableNamesFromDB();
	int makeSQLiteSearch(const QString& request, sqlite3_stmt **stmt,QString callingFunction);

	void AddElementToSprachenList(QString element);
	void AddElementToWaehrungsList (QString element);

    QSqlDatabase m_sqldb;

    sqlite3 *m_db;
	CJahrDisplayList *m_jahrgaengeDisplay;
	CAusgabeDisplayList *m_ausgabenForJahrDisplay;
    CArtikelDisplayList *m_artikelDisplay;
    CZeitschriftDisplayList *m_zeitschriftenDisplay;
    CZeitschriftDisplayList *m_zeitschriftenForJahrDisplay;
    CSelectionListDisplay *m_RubrikenList;
    CSelectionListDisplay *m_ZeitschriftenListForSelection;
	CSelectionListDisplay *m_SloganList;
	CSelectionListDisplay *m_redaktionList;
	CSelectionListDisplay *m_SprachenList;
	CSelectionListDisplay *m_waehrungsList;
	CAusgabeDisplayList *m_ausgabenDisplay;

    QString m_searchElement;

    QString m_lastArtikelRequestString;

    QMap<QString, CColumn> m_searchTables;
    QMap<QString, CColumn> m_searchTablesSetting;




};

#endif // LISTENCONTROLLER_H
