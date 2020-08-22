#include "clistencontroller.h"
#include <QDebug>

CListenController::CListenController(sqlite3 *db, QObject *parent) : QObject(parent)
{
    m_db = db;
    m_searchElement = "";
    m_jahrgaengeDisplay = new CJahrDisplayList();
    m_ausgabenDisplay = new CAusgabeDisplayList();
    m_artikelDisplay = new CArtikelDisplayList() ;

    m_searchTablesSetting["Ausgabe"].setName("Ausgabe");
    m_searchTablesSetting["Ausgabe"].setSearchable(false);
    m_searchTablesSetting["Jahr"].setName("Jahr");
    m_searchTablesSetting["Jahr"].setSearchable(false);
    m_searchTablesSetting["Rubrik"].setName("Rubrik");
    m_searchTablesSetting["Rubrik"].setSearchable(false);
    m_searchTablesSetting["Ueberschrift"].setName("Ueberschrift");
    m_searchTablesSetting["Zusammenfassung"].setName("Zusammenfassung");
    m_searchTablesSetting["Kurztext"].setName("Kurztext");
    m_searchTablesSetting["Seite"].setName("Seite");
    m_searchTablesSetting["Seite"].setSearchable(false);
    m_searchTablesSetting["Autor"].setName("Autor");
    m_searchTablesSetting["Fotos"].setName("Fotos");
    m_searchTablesSetting["Schlagworte"].setName("Schlagworte");
    m_searchTablesSetting["Land"].setName("Land");

    getTableNamesFromDB();

}

CJahrDisplayList *CListenController::jahrgaengeDisplay()
{
	return m_jahrgaengeDisplay;
}

CAusgabeDisplayList *CListenController::ausgabenDisplay()
{
	return m_ausgabenDisplay;
}


CArtikelDisplayList *CListenController::artikelDisplay()
{
    return m_artikelDisplay;
}

void CListenController::getJahre()
{
    m_jahrgaengeDisplay->deleteAll();
    m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
    m_searchElement="";
    char *zErrMsg = 0;
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(m_db, "SELECT Jahr FROM Inhalte ORDER BY Jahr ASC", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
           return; // or throw
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        int number = sqlite3_column_count(stmt);
        CJahr jahr;
        for (int i=0; i<number; ++i)
        {

            QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            jahr.setDBElement(columnName,columnText);
        }

         m_jahrgaengeDisplay->AddJahr(jahr);
    }

    sqlite3_finalize(stmt);
}

void CListenController::getAusgabenForJahr(int jahr)
{
	//m_jahrgaengeDisplay->deleteAusgaben();
	m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
	char *zErrMsg = 0;
	sqlite3_stmt *stmt;
    QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
        searchForString = QString("AND (")+searchForString+QString(") ");
    }
    QString request = QString("SELECT * FROM Inhalte WHERE Jahr='%1' %2 ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(jahr).arg(searchForString);
    qDebug()<<request;
	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		   return; // or throw
	}
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		int id = sqlite3_column_int(stmt, 0);
		int number = sqlite3_column_count(stmt);
		CAusgabe ausgabe;
        CArtikel artikel;
		for (int i=0; i<number; ++i)
		{

			QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
			ausgabe.setDBElement(columnName,columnText);
            artikel.setDBElement(columnName,columnText);
        }

		m_ausgabenDisplay->AddAusgabe(ausgabe);
        m_artikelDisplay->AddArtikel(artikel);
	}

	sqlite3_finalize(stmt);
}

void  CListenController::getArtikelForAusgabe(int jahr, int ausgabe)
{
    m_artikelDisplay->deleteAll();
    char *zErrMsg = 0;
    sqlite3_stmt *stmt;

    QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
        searchForString = QString("AND (")+searchForString+QString(") ");
    }

    QString request = QString("SELECT * FROM Inhalte WHERE Jahr='%1' AND Ausgabe='%2' %3 ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(jahr).arg(ausgabe).arg(searchForString);
    qDebug()<<request;

    int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
           return; // or throw
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int number = sqlite3_column_count(stmt);
        CArtikel artikel;
        for (int i=0; i<number; ++i)
        {

            QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            artikel.setDBElement(columnName,columnText);
        }

        m_artikelDisplay->AddArtikel(artikel);
    }

    sqlite3_finalize(stmt);

}

void CListenController::getTableNamesFromDB()
{
    char **result;
    int row;int column;

    int rc = sqlite3_get_table(m_db, "SELECT * from Inhalte", &result, &row,    &column,   NULL   );
      for (int i=0; i<column; i++)
    {
        QString name = result[i];
        CColumn columnInfo(name);
        m_searchTables[name]=columnInfo;
        if (m_searchTablesSetting.contains(name))
        {
            m_searchTables[name] = m_searchTablesSetting[name];
        }
    }

    sqlite3_free_table(result);
}

QString CListenController::setSearchStringAsSQL()
{
    QString searchString;
    if (m_searchElement.isEmpty())
    {
        return "";
    }
    QMapIterator<QString, CColumn> i(m_searchTables);
    while (i.hasNext()) {
        i.next();
        if (i.value().searchable())
        {
            searchString += QString(" %1 LIKE '%%2%' OR ").arg(i.key()).arg(m_searchElement);
        }
    }
    int lastOR = searchString.lastIndexOf("OR");
    searchString = searchString.remove(lastOR, 20);

    return searchString;

}
void CListenController::searchArtikel(QString searchElement)
{
    m_jahrgaengeDisplay->deleteAll();
    m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
    m_searchElement = searchElement;
    char *zErrMsg = 0;
    sqlite3_stmt *stmt;
    QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
        searchForString = QString("WHERE (")+searchForString+QString(") ");
    }

    QString request = QString("SELECT * FROM Inhalte %1 ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(searchForString);
    qDebug()<<request;

    int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
           return; // or throw
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int number = sqlite3_column_count(stmt);
        CArtikel artikel;
        CJahr jahr;
        for (int i=0; i<number; ++i)
        {

            QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            artikel.setDBElement(columnName,columnText);
            jahr.setDBElement(columnName,columnText);
        }

        m_artikelDisplay->AddArtikel(artikel);
        m_jahrgaengeDisplay->AddJahr(jahr);
    }

    sqlite3_finalize(stmt);

}


