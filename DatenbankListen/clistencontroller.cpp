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
       rc = sqlite3_open_v2(DBPath.toUtf8(),&db,(SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI),nullptr);
    if (rc != SQLITE_OK)
    {
        qDebug()<<"Could not open SQLite DB "<<DBPath;
        return false;
    }
    m_db = db;

    getTableNamesFromDB();
    getListOfZeitschriften();
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

void CListenController::getListOfZeitschriften()
{
    m_zeitschriftenDisplay->deleteAll();
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
    sqlite3_stmt *stmt;

    QString request = QString("SELECT Zeitschrift FROM Inhalte  ORDER BY Zeitschrift ASC");
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getListOfZeitschriften");
    if (rc != SQLITE_OK)
    {
           return; // or throw
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int number = sqlite3_column_count(stmt);
        CZeitschrift zeitschrift;
        for (int i=0; i<number; ++i)
        {

            QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            zeitschrift.setDBElement(columnName,columnText);

        }

         m_zeitschriftenDisplay->AddElement(zeitschrift);
    }

    sqlite3_finalize(stmt);
}
/*!
  Will search for all Jahrgänge and Zeitschriften
  */
void CListenController::getOverview()
{
    m_jahrgaengeDisplay->deleteAll();
    m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
     m_zeitschriftenForJahrDisplay->deleteAll();
     m_zeitschriftenDisplay->deselectAll();

    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
    sqlite3_stmt *stmt;
    QString select ="Jahr";

    m_searchElement = "";
   QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
        searchForString = QString("WHERE (")+searchForString+QString(") ");
    }

    QString request = QString("SELECT %1 FROM Inhalte %2 ORDER BY Jahr ASC").arg(select).arg(searchForString);
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getOverview");
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
    m_zeitschriftenForJahrDisplay->deleteAll();

    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
//    m_searchElement="";
    sqlite3_stmt *stmt;
    QString zeitschriftenSearch;
    if (zeitschriften.count()>0)
    {
        zeitschriftenSearch += QString(" ( ");
        for (int i=0;i<zeitschriften.count();i++)
        {
            zeitschriftenSearch += QString("Zeitschrift='%1' OR ").arg(zeitschriften.at(i));
        }
        int lastOR = zeitschriftenSearch.lastIndexOf("OR");
        zeitschriftenSearch = zeitschriftenSearch.remove(lastOR, 20);
        zeitschriftenSearch += QString(" ) ");
    }

    QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
        searchForString = QString("AND (")+searchForString+QString(") ");
    }

    QString whereRequest;
    if ((!(searchForString.isEmpty())) || (!(zeitschriftenSearch.isEmpty())))
    {
        whereRequest = QString(" WHERE %1 %2").arg(zeitschriftenSearch).arg(searchForString);
    }

    QString request = QString("SELECT Jahr,Zeitschrift FROM Inhalte %1 ORDER BY Jahr ASC").arg(whereRequest);

	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getJahreForZeitschrift");

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

void CListenController::getLowerInfoForJahr(int jahr)
{
    m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
    m_zeitschriftenForJahrDisplay->deleteAll();
    getZeitschriftenForJahr(jahr);
}

int CListenController::getZeitschriftenForJahr(int jahr)
{
	  m_ausgabenDisplay->deleteAll();
      m_artikelDisplay->deleteAll();
      m_zeitschriftenForJahrDisplay->deleteAll();
      if (m_db == nullptr)
      {
          qDebug()<<"No open DB!";
          return 0;
      }
      sqlite3_stmt *stmt;
      QString searchForString = setSearchStringAsSQL();
      if (!(searchForString.isEmpty()))
      {
          searchForString = QString("AND (")+searchForString+QString(") ");
      }
       QString zeitschriftenSearch = setZeitschriftenAsSQL();
       if (!(zeitschriftenSearch.isEmpty()))
       {
           zeitschriftenSearch = QString(" AND ( ")+zeitschriftenSearch+QString(") ");
       }

      QString request = QString("SELECT * FROM Inhalte WHERE Jahr='%1' %2 %3 ORDER BY Zeitschrift ASC, Jahr ASC,Ausgabe ASC,Seite ASC").arg(jahr).arg(zeitschriftenSearch).arg(searchForString);
	  int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getLowerInfoForJahr");
  //	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
      if (rc != SQLITE_OK)
      {
             return 0; // or throw
      }
      while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
      {
          int number = sqlite3_column_count(stmt);
          CAusgabe ausgabe;
          CArtikel artikel;
          CZeitschrift zeitschrift;
          for (int i=0; i<number; ++i)
          {

              QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
              QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
              zeitschrift.setDBElement(columnName,columnText);
              ausgabe.setDBElement(columnName,columnText);
              artikel.setDBElement(columnName,columnText);
          }

          m_ausgabenDisplay->AddElement(ausgabe);
          m_artikelDisplay->AddElement(artikel);
          m_zeitschriftenForJahrDisplay->AddElement(zeitschrift);
      }

    sqlite3_finalize(stmt);
    return m_zeitschriftenForJahrDisplay->rowCount();
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
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getAusgabenForJahr");
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

void CListenController::getAusgabenForZeitschrift(QString zeitschrift, int jahr)
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

    QString request = QString("SELECT * FROM Inhalte WHERE Jahr='%1' AND Zeitschrift='%2' %3 ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(jahr).arg(zeitschrift).arg(searchForString);
//    qDebug()<<request;
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getAusgabenForZeitschrift");
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

void  CListenController::getArtikelForAusgabe(QString zeitschrift, int jahr, int ausgabe)
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

    QString request = QString("SELECT * FROM Inhalte WHERE Jahr='%1' AND Ausgabe='%2' AND Zeitschrift='%3' %4 ORDER BY Zeitschrift ASC, Jahr ASC,Ausgabe ASC,Seite ASC").arg(jahr).arg(ausgabe).arg(zeitschrift).arg(searchForString);
 //   qDebug()<<request;
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getArtikelForAusgabe");

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

int CListenController::addNewEmptyRowToInhalte()
{
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return -1;
    }
    sqlite3_stmt *stmt;
    char *zErrMsg;

    QString request = QString("INSERT INTO Inhalte DEFAULT VALUES");
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,0,&zErrMsg);
    if (rc !=0 )
    {
        qDebug()<<"addNewRowToInhalte: SqLite request returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
        return -1;
    }
    else
    {
        qDebug()<<":addNewRowToInhalte: SqLite request returned OK for "<<request;

    }
    int index = static_cast<int>(sqlite3_last_insert_rowid(m_db));
 //   sqlite3_finalize(stmt);
    return index;
}

void CListenController::deleteArtikel(int index)
{
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return ;
    }
    sqlite3_stmt *stmt;
    char *zErrMsg;

    QString request = QString("DELETE FROM Inhalte WHERE UniqueIndex='%1'").arg(index);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,0,&zErrMsg);
    if (rc !=0 )
    {
        qDebug()<<"deleteArtikel: SqLite request returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
        return ;
    }
    else
    {
        qDebug()<<"deleteArtikel: SqLite request returned OK for "<<request;

    }
 //   int index = static_cast<int>(sqlite3_last_insert_rowid(m_db));
 //   sqlite3_finalize(stmt);
    return ;
}
void CListenController::updateInhalteTable(QString sqlElements)
{
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
    sqlite3_stmt *stmt;
    char *zErrMsg;

    QString request = QString("UPDATE Inhalte %1").arg(sqlElements);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,0,&zErrMsg);
//    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt);
    if (rc !=0 )
    {
        qDebug()<<"SqLite request returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
    }
    else
    {
        qDebug()<<"SqLite request returned OK for "<<request;

    }
 //   sqlite3_finalize(stmt);
    return;
}

CArtikel CListenController::getArtikelByIndex(int index)
{
    CArtikel artikel;


    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return artikel;
    }
    sqlite3_stmt *stmt;

    QString request = QString("SELECT * FROM Inhalte WHERE UniqueIndex='%1' ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(index);
//    qDebug()<<request;

	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getArtikelByIndex");
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
           return artikel; // or throw
    }

  /*  if (number != 1)
    {
       qDebug()<<"Index "<<index<<" nicht eindeutig";
       return artikel;
    }*/

    int counter =0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
          if (counter > 0)
          {
             qDebug()<<"Index "<<index<<" nicht eindeutig";
             return artikel;
          }
        int number = sqlite3_column_count(stmt);

        for (int i=0; i<number; ++i)
        {

           QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            artikel.setDBElement(columnName,columnText);

        }
        counter ++;

      }

    sqlite3_finalize(stmt);
    return artikel;
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


QString CListenController::setZeitschriftenAsSQL()
{
    QStringList zeitschriften = m_zeitschriftenDisplay->getSelectedElements();
    QString zeitschriftenSearch;
    if (zeitschriften.count()>0)
    {
  //      zeitschriftenSearch+= " ( ";
        for (int i=0;i<zeitschriften.count();i++)
        {
            zeitschriftenSearch += QString("Zeitschrift='%1' OR ").arg(zeitschriften.at(i));
        }
        int lastOR = zeitschriftenSearch.lastIndexOf("OR");
        zeitschriftenSearch = zeitschriftenSearch.remove(lastOR, 20);
//        zeitschriftenSearch +" ) ";
    }
    return zeitschriftenSearch;

}
void CListenController::searchArtikel(QString searchElement)
{
    m_jahrgaengeDisplay->deleteAll();
    m_ausgabenDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
    m_zeitschriftenForJahrDisplay->deleteAll();

    setSearchElement(searchElement);
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
    sqlite3_stmt *stmt;
    QString searchForString = setSearchStringAsSQL();
  /*  if (!(searchForString.isEmpty()))
    {
        searchForString = QString("WHERE (")+searchForString+QString(") ");
    }
*/

    QString zeitschriftenSearch = setZeitschriftenAsSQL();


    QString filterRequest;
    if ((!(searchForString.isEmpty())) || (!(zeitschriftenSearch.isEmpty())))
    {
        filterRequest = QString("WHERE ");
        if (!(zeitschriftenSearch.isEmpty()))
        {
            filterRequest += QString(" ( ")+zeitschriftenSearch +  QString(" ) ");
            if (!(searchForString.isEmpty()))
            {
                filterRequest += " AND ";
            }
        }

        if (!(searchForString.isEmpty()))
        {
            filterRequest += QString(" (")+searchForString+QString(") ");
        }
    }

    QString request = QString("SELECT * FROM Inhalte %1 ORDER BY Jahr ASC,Ausgabe ASC,Seite ASC").arg(filterRequest);
//    qDebug()<<request;

	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"searchArtikel");
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


int CListenController::makeSQLiteSearch(const QString& request, sqlite3_stmt **stmt,QString callingFunction)
{
 //   int rc = sqlite3_get_table
    int rc = sqlite3_prepare_v2(m_db,request.toStdString().c_str() , -1, stmt, nullptr);
    if (rc !=0 )
    {
		QString error = QString("sqlite3_prepare_v2 request from ")+callingFunction+QString(" returned %1 (%2) for %3").arg(sqlite3_errstr(rc)).arg(rc).arg(request);
		qDebug()<< error; //"SqLite request from "<<callingFunction"<< returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
		emit errorMessage("CListenController",error);
	}
    else
    {
		qDebug()<<"sqlite3_prepare_v2 request from "<<callingFunction<<" returned OK for "<<request;

    }
    return rc;
}

