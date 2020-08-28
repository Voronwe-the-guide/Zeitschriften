#include "clistencontroller.h"
#include <QDebug>

CListenController::CListenController( QObject *parent) : QObject(parent)
{
    m_db = nullptr;
    m_searchElement = "";
    m_jahrgaengeDisplay = new CJahrDisplayList();
    m_ausgabenDisplay = new CAusgabeDisplayList();
    m_artikelDisplay = new CArtikelDisplayList() ;

    m_zeitschriftenDisplay = new CZeitschriftDisplayList();
    m_zeitschriftenForJahrDisplay = new CZeitschriftDisplayList();



    m_searchTablesSetting["Zeitschrift"].setName("Zeitschrift");
    m_searchTablesSetting["Ausgabe"].setSearchable(false);
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


}

CListenController::~CListenController()
{
    sqlite3_close(m_db);
}

bool CListenController::openDB(QString DBPath)
{
    int rc =  sqlite3_close(m_db);
    if (rc != SQLITE_OK)
    {
        qDebug()<<"Could not close current SQLite DB ";
        return false;
    }
    m_db = nullptr;
    sqlite3 *db;
       rc = sqlite3_open_v2(DBPath.toUtf8(),&db,(SQLITE_OPEN_READONLY | SQLITE_OPEN_URI),nullptr);
    if (rc != SQLITE_OK)
    {
        qDebug()<<"Could not open SQLite DB "<<DBPath;
        return false;
    }
    m_db = db;

    getTableNamesFromDB();
    getOverview();
    return true;

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

CZeitschriftDisplayList *CListenController::zeitschriftenDisplay()
{
    return m_zeitschriftenDisplay;
}
CZeitschriftDisplayList *CListenController::zeitschriftenForJahrDisplay()
{
    return m_zeitschriftenForJahrDisplay;
}

/*!
  Will search for all Jahrgänge and Zeitschriften
  */
void CListenController::getOverview()
{
    m_jahrgaengeDisplay->deleteAll();
    m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
    m_zeitschriftenDisplay->deleteAll();
    m_zeitschriftenForJahrDisplay->deleteAll();

    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
    m_searchElement="";
    sqlite3_stmt *stmt;
    QString select ="Jahr";
    if (m_searchTables.contains("Zeitschrift"))
    {
        select += ",Zeitschrift";
    }
    QString request = QString("SELECT %1 FROM Inhalte ORDER BY Jahr ASC").arg(select);
    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt);
    //sqlite3_prepare_v2(m_db,request.toStdString().c_str() , -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
           return; // or throw
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int number = sqlite3_column_count(stmt);
        CJahr jahr;
        CZeitschrift zeitschrift;
        for (int i=0; i<number; ++i)
        {

            QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            jahr.setDBElement(columnName,columnText);
            zeitschrift.setDBElement(columnName,columnText);

        }

         m_jahrgaengeDisplay->AddElement(jahr);
         m_zeitschriftenDisplay->AddElement(zeitschrift);
    }

    sqlite3_finalize(stmt);

}

/*!
  Will add or remove the Zeitung for the selection list, depending on the current status
 * */
void CListenController::addOrRemoveZeitschrift(int index)
{
    m_zeitschriftenDisplay->ToggleSelection(index);
    getJahreForZeitschrift(m_zeitschriftenDisplay->getSelectedElements());

}
void CListenController::getJahreForZeitschrift(QStringList zeitschriften)
{
    m_jahrgaengeDisplay->deleteAll();
    m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();

    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
    m_searchElement="";
    sqlite3_stmt *stmt;
    QString searchString;
    if (zeitschriften.count()>0)
    {
        for (int i=0;i<zeitschriften.count();i++)
        {
            searchString += QString("Zeitschrift='%1' OR ").arg(zeitschriften.at(i));
        }
        int lastOR = searchString.lastIndexOf("OR");
        searchString = searchString.remove(lastOR, 20);
    }
    QString request = QString("SELECT Jahr,Zeitschrift FROM Inhalte WHERE %1 ORDER BY Jahr ASC").arg(searchString);
    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt);

//    int rc = sqlite3_prepare_v2(m_db,request.toStdString().c_str() , -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
           return; // or throw
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
		int number = sqlite3_column_count(stmt);
        CJahr jahr;
        for (int i=0; i<number; ++i)
        {

            QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            jahr.setDBElement(columnName,columnText);
        }

		 m_jahrgaengeDisplay->AddElement(jahr);
    }

    sqlite3_finalize(stmt);
}

void CListenController::getAusgabenForJahr(int jahr)
{
	//m_jahrgaengeDisplay->deleteAusgaben();
	m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }

	sqlite3_stmt *stmt;
    QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
        searchForString = QString("AND (")+searchForString+QString(") ");
    }
    QString request = QString("SELECT * FROM Inhalte WHERE Jahr='%1' %2 ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(jahr).arg(searchForString);
//    qDebug()<<request;
    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt);
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		   return; // or throw
	}
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
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

		m_ausgabenDisplay->AddElement(ausgabe);
		m_artikelDisplay->AddElement(artikel);
	}

	sqlite3_finalize(stmt);
}

void  CListenController::getArtikelForAusgabe(int jahr, int ausgabe)
{
    m_artikelDisplay->deleteAll();
	sqlite3_stmt *stmt;
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }

    QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
        searchForString = QString("AND (")+searchForString+QString(") ");
    }

    QString request = QString("SELECT * FROM Inhalte WHERE Jahr='%1' AND Ausgabe='%2' %3 ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(jahr).arg(ausgabe).arg(searchForString);
 //   qDebug()<<request;
    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt);

//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
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

		m_artikelDisplay->AddElement(artikel);
    }

    sqlite3_finalize(stmt);

}

void CListenController::getTableNamesFromDB()
{
    char **result;
    int row;int column;
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }

	int rc = sqlite3_get_table(m_db, "SELECT * from Inhalte", &result, &row,    &column,  nullptr);
	if (rc != SQLITE_OK)
	{
		   return; // or throw
	}
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

QString CListenController::getSearchElement() const
{
    return m_searchElement;
}

void CListenController::setSearchElement(const QString &searchElement)
{
    m_searchElement = searchElement;
    m_artikelDisplay->setSearchElement(m_searchElement);
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
   setSearchElement(searchElement);
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
    sqlite3_stmt *stmt;
    QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
        searchForString = QString("WHERE (")+searchForString+QString(") ");
    }

    QString request = QString("SELECT * FROM Inhalte %1 ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(searchForString);
//    qDebug()<<request;

    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt);
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
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

		m_artikelDisplay->AddElement(artikel);
		m_jahrgaengeDisplay->AddElement(jahr);
    }

    sqlite3_finalize(stmt);

}

int CListenController::makeSQLiteSearch(const QString& request, sqlite3_stmt **stmt) const
{
    int rc = sqlite3_prepare_v2(m_db,request.toStdString().c_str() , -1, stmt, nullptr);
    qDebug()<<"SqLite request returned "<<rc<<" for "<<request;
    return rc;
}

