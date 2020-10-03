#include "clistencontroller.h"
#include <Helper/helper.h>
#include <QDebug>

CListenController::CListenController( QObject *parent) : QObject(parent)
{
    m_db = nullptr;
    m_searchElement = "";
    m_jahrgaengeDisplay = new CJahrDisplayList();
    m_ausgabenForJahrDisplay = new CAusgabeDisplayList();
	m_ausgabenDisplay = new CAusgabeDisplayList();
    m_artikelDisplay = new CArtikelDisplayList() ;

    m_zeitschriftenDisplay = new CZeitschriftDisplayList();
    m_zeitschriftenForJahrDisplay = new CZeitschriftDisplayList();

    m_RubrikenList = new CSelectionListDisplay();

    m_ZeitschriftenListForSelection = new CSelectionListDisplay();
	m_SloganList = new CSelectionListDisplay() ;
	m_redaktionList = new CSelectionListDisplay();
	m_SprachenList = new CSelectionListDisplay();
	m_waehrungsList = new CSelectionListDisplay();

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

    m_jahrgaengeDisplay->deleteAll();
    m_ausgabenForJahrDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
    m_zeitschriftenDisplay->deleteAll();
   m_zeitschriftenForJahrDisplay->deleteAll();
    m_RubrikenList->deleteAll();
    m_ZeitschriftenListForSelection->deleteAll();
    m_SloganList->deleteAll();
    m_redaktionList->deleteAll();
    m_SprachenList->deleteAll();
    m_waehrungsList->deleteAll();
    m_ausgabenDisplay->deleteAll();

   int rc =  sqlite3_close_v2(m_db);
    if (rc != SQLITE_OK)
    {
        qDebug()<<"Could not close current SQLite DB ";
        emit errorMessage("CListenController::OpenDB",tr("Problem with closing DB, please restart Application"));
        return false;
    }
    m_db = nullptr;
    sqlite3 *db;
       rc = sqlite3_open_v2(DBPath.toUtf8(),&db,(SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI),nullptr);
    if (rc != SQLITE_OK)
    {
        qDebug()<<"Could not open SQLite DB "<<DBPath;
        emit errorMessage("CListenController::OpenDB",tr("Could not open DB ")+DBPath);
        return false;
    }
    m_db = db;

    getTableNamesFromDB();
    getListOfZeitschriften();
	getListOfAusgaben(true);
    getOverview();
    return true;


}

CJahrDisplayList *CListenController::jahrgaengeDisplay()
{
	return m_jahrgaengeDisplay;
}

CAusgabeDisplayList *CListenController::ausgabenForJahrDisplay()
{
	return m_ausgabenForJahrDisplay;
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

CSelectionListDisplay *CListenController::rubrikenListDisplay()
{
    return m_RubrikenList;
}

CSelectionListDisplay *CListenController::zeitschriftenListForSelection()
{
    return m_ZeitschriftenListForSelection;
}

CSelectionListDisplay* CListenController::sloganList()
{
	return m_SloganList;
}
CSelectionListDisplay* CListenController::redaktionList()
{
	return m_redaktionList;
}
CSelectionListDisplay* CListenController::sprachenList()
{
	return m_SprachenList;
}
CSelectionListDisplay* CListenController::waehrungsList()
{
	return m_waehrungsList;
}

/*!
 * Liste der Zeitschriften um sie oben anzuzeigen
 */
void CListenController::getListOfZeitschriften()
{
    m_zeitschriftenDisplay->deleteAll();
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
    sqlite3_stmt *stmt;

    //QString request = QString("SELECT Zeitschrift, Rubrik FROM Inhalte  ORDER BY Zeitschrift ASC, Rubrik ASC");
	QString request = QString("SELECT * FROM ")+ZEITSCHRIFT_TABELLE +" ORDER BY "+ZEITSCHRIFT_ZEITSCHRIFT+" ASC";
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getListOfZeitschriften_1");
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
            QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            zeitschrift.setDBElement(columnName,columnText);

        }


		int index=-1;
		m_zeitschriftenDisplay->AddElement(zeitschrift,index);
		 m_SprachenList->AddElement(zeitschrift.getSprache());

    }

    //Get Zeitschriften from Inhalte -> to get the Rubriken and Zeitschriften, which are not in the main list
	request = QString("SELECT ")+ARTIKEL_ZEITSCHRIFT+", "+ARTIKEL_RUBRIK+" FROM "+ARTIKEL_TABELLE+
			" ORDER BY "+ARTIKEL_ZEITSCHRIFT+" ASC, "+ARTIKEL_RUBRIK+" ASC";
	rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getListOfZeitschriften_2");
    if (rc != SQLITE_OK)
    {
           return; // or throw
    }

   bool foundNew = false;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int number = sqlite3_column_count(stmt);
        CZeitschrift zeitschrift;
		QString rubrik;
        for (int i=0; i<number; ++i)
        {

			QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            zeitschrift.setDBElement(columnName,columnText);
			if (columnName == ARTIKEL_RUBRIK)
			{
				rubrik = columnText;
			}

        }

		 int index=-1;
		 bool isNew = m_zeitschriftenDisplay->AddElement(zeitschrift,index);
         if (isNew)
         {
             int index = addNewEmptyRowToZeitschriftTable();
             zeitschrift.setUniqueIndex(index);
             updateZeitschriftenTable(zeitschrift,false);
             foundNew = true;
         }
		 m_zeitschriftenDisplay->AddRubrikToZeitschrift(zeitschrift.getZeitschrift(),rubrik);
    }


    sqlite3_finalize(stmt);

    if (foundNew)
    {
        getListOfZeitschriften();
    }
    else
    {
        setZeitschriftSelectionDisplay();
    }


}

void CListenController::getListOfAusgaben(bool atStartup)
{

	m_ausgabenDisplay->deleteAll();
	if (m_db == nullptr)
	{
		qDebug()<<"No open DB!";
		return;
	}
	sqlite3_stmt *stmt;

	QString request = QString("SELECT * FROM ")+AUSGABE_TABELLE +" ORDER BY "+AUSGABE_ZEITSCHRIFT+" ASC, "+AUSGABE_JAHR+" ASC, "+AUSGABE_AUSGABE+" ASC";
    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getListOfAusgaben_1");
	if (rc != SQLITE_OK)
	{
		   return; // or throw
	}

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		int number = sqlite3_column_count(stmt);
		CAusgabe ausgabe;
		for (int i=0; i<number; ++i)
		{

			QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
			ausgabe.setDBElement(columnName,columnText);
		}
		int index=-1;
		m_ausgabenDisplay->AddElement(ausgabe,index);

		if (atStartup)
		{
			 m_SprachenList->AddElement(ausgabe.getSprache());
			 m_waehrungsList->AddElement(ausgabe.getWaehrung());
			 int listIndex = -1;
			 CZeitschrift zeitschriftForAusgabe = m_zeitschriftenDisplay->getZeitschrift(ausgabe.getZeitschrift(),listIndex);
			 if (listIndex>=0)
			 {
				zeitschriftForAusgabe.AddElementToSloganList(ausgabe.getUntertitel());
				zeitschriftForAusgabe.AddElementToRedaktionList(ausgabe.getChefredakteur());
				m_zeitschriftenDisplay->UpdateZeitschrift(zeitschriftForAusgabe,listIndex);
			 }
		}


	}

/*	if (atStartup)
	{
		//Get Zeitschriften from Inhalte -> to get the Rubriken and Zeitschriften, which are not in the main list
		request = QString("SELECT ")+ARTIKEL_ZEITSCHRIFT+", "+ARTIKEL_JAHR+", "+ARTIKEL_AUSGABE+" FROM "+ARTIKEL_TABELLE
									+" ORDER BY "+ARTIKEL_ZEITSCHRIFT+" ASC, "+ARTIKEL_JAHR+" ASC, "+ARTIKEL_AUSGABE+" ASC";
        rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getListOfAusgaben_2");
		if (rc != SQLITE_OK)
		{
			   return; // or throw
		}

	   bool foundNew = false;
		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
		{
			int number = sqlite3_column_count(stmt);
			CAusgabe newAusgabe;
			for (int i=0; i<number; ++i)
			{
				QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
				QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
				newAusgabe.setDBElement(columnName,columnText);
			}

			 bool isNew = m_ausgabenDisplay->AddElement(newAusgabe);
			 if (isNew)
			 {
				 int index = addNewEmptyRowToAusgabenTable();
				 newAusgabe.setUniqueIndex(index);
				 int listIndex = -1;
				 CZeitschrift zeitschriftForAusgabe = m_zeitschriftenDisplay->getZeitschrift(newAusgabe.getZeitschrift(),listIndex);
				 if (listIndex>=0)
				 {
					 newAusgabe.setSprache(zeitschriftForAusgabe.getSprache());
				 }
				 updateAusgabenTable(newAusgabe);
				 foundNew = true;
			 }
			// m_zeitschriftenDisplay->AddRubrikToZeitschrift(zeitschrift.getZeitschrift(),rubrik);
		}



    if (foundNew)
		{
			getListOfAusgaben();
		}


	}
*/

sqlite3_finalize(stmt);

}
/*!
  Will search for all Jahrgänge and Zeitschriften
  */
void CListenController::getOverview()
{
    m_jahrgaengeDisplay->deleteAll();
    m_ausgabenForJahrDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
     m_zeitschriftenForJahrDisplay->deleteAll();
     m_zeitschriftenDisplay->deselectAll();

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

	QString request = QString("SELECT ")+ARTIKEL_JAHR+" FROM "+ARTIKEL_TABELLE+" "+searchForString+" ORDER BY "+ARTIKEL_JAHR+" ASC";
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
    m_ausgabenForJahrDisplay->deleteAll();
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

	//Liste der Zeitschriften, die in der Suche sind
    if (zeitschriften.count()>0)
    {
        zeitschriftenSearch += QString(" ( ");
		Helper helper;
        for (int i=0;i<zeitschriften.count();i++)
        {
			zeitschriftenSearch += ZEITSCHRIFT_ZEITSCHRIFT+ QString("='")+helper.fixSpecialCharacters(zeitschriften.at(i))+"' OR ";
        }
        int lastOR = zeitschriftenSearch.lastIndexOf("OR");
        zeitschriftenSearch = zeitschriftenSearch.remove(lastOR, 20);
        zeitschriftenSearch += QString(" ) ");
    }
//Suche einschränken mit Info aus Eingabefeld
    QString searchForString = setSearchStringAsSQL();
    if (!(searchForString.isEmpty()))
    {
		searchForString = QString(" (")+searchForString+QString(") ");
		if (!zeitschriftenSearch.isEmpty())
	   {
		   searchForString = QString(" AND ")+searchForString;
	   }
    }

    QString whereRequest;
    if ((!(searchForString.isEmpty())) || (!(zeitschriftenSearch.isEmpty())))
    {
		whereRequest = QString(" WHERE ")+zeitschriftenSearch+" "+searchForString;
    }

//    QString request = QString("SELECT Jahr,Zeitschrift FROM Inhalte %1 ORDER BY Jahr ASC").arg(whereRequest);
	QString request = QString("SELECT ")+ARTIKEL_JAHR+" FROM "+ARTIKEL_TABELLE+" "+whereRequest+" ORDER BY "+ARTIKEL_JAHR+" ASC";

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
    m_ausgabenForJahrDisplay->deleteAll();
    m_artikelDisplay->deleteAll();
    m_zeitschriftenForJahrDisplay->deleteAll();
    getZeitschriftenForJahr(jahr);
}

int CListenController::getZeitschriftenForJahr(int jahr)
{


    m_ausgabenForJahrDisplay->deleteAll();
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
//Get the relevant artikels - with filter Elements
	  QString request = QString("SELECT * FROM ")+ARTIKEL_TABELLE+" WHERE "+ARTIKEL_JAHR+QString("='%1'").arg(jahr)+
			  " "+zeitschriftenSearch+" "+searchForString+
			  " ORDER BY "+ARTIKEL_ZEITSCHRIFT+" ASC, "+ARTIKEL_JAHR+" ASC,"+ARTIKEL_AUSGABE+" ASC,"+ ARTIKEL_SEITE+" ASC";

	  int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getZeitschriftenForJahr_1");
	  if (rc != SQLITE_OK)
      {
             return 0; // or throw
      }
      QTime startTime = QTime::currentTime();
	  QMap<QString,int> zeitschriften_map;  //A list, welche Zeitschriften drinne sind -> für die Details von der Zeitschriften-Liste
	 // QMap<int,int> ausgaben_map;

      while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
      {
          int number = sqlite3_column_count(stmt);
		//  CAusgabe ausgabe;
          CArtikel artikel;
          CZeitschrift zeitschrift;
         QTime localStart = QTime::currentTime();
          for (int i=0; i<number; ++i)
          {

              QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			  QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
		   //   zeitschrift.setDBElement(columnName,columnText);
			//  ausgabe.setDBElement(columnName,columnText);
              artikel.setDBElement(columnName,columnText);
			  if (columnName == ARTIKEL_ZEITSCHRIFT)
			  {
				  zeitschriften_map.insert(columnText,0);
			  }
          }
          QTime loopEnd = QTime::currentTime();
      //    qDebug()<<"Loop Finished in "<<localStart.msecsTo(loopEnd);
		  m_artikelDisplay->AddElement(artikel);
		  int ausgabeIndex = -1;
		  int zeitschriftIndex = -1;
		/*  bool newAusgabe = m_ausgabenForJahrDisplay->AddElement(ausgabe,ausgabeIndex);
		  if (newAusgabe)
		  {
			//  ausgaben_map.insert()
		  }

		  bool newZeitschrift = m_zeitschriftenForJahrDisplay->AddElement(zeitschrift,zeitschriftIndex);
		  if (newZeitschrift)
		  {
			  zeitschriften_map.insert(zeitschrift.getZeitschrift(),zeitschriftIndex);
		  }
		 */ QTime addingEnd = QTime::currentTime();

       //   qDebug()<<"Adding Finished in "<<loopEnd.msecsTo(addingEnd);
      }
      QTime endTime = QTime::currentTime();
      int doneIn = startTime.msecsTo(endTime);
      qDebug()<<"Finished in "<<doneIn;

    sqlite3_finalize(stmt);

	//Update with Info from Zeitschriften Table
	if (zeitschriften_map.count()>0)
	{
		Helper helper;
		QString zeitschriftenSearch_local;
		QMapIterator<QString, int> iter(zeitschriften_map);
		//zeitschriftenSearch_local = QString("WHERE ");
		while (iter.hasNext()) {
			iter.next();
			zeitschriftenSearch_local += ZEITSCHRIFT_ZEITSCHRIFT+QString("='")+helper.fixSpecialCharacters(iter.key())+"' OR ";
		//	cout << i.key() << ": " << i.value() << Qt::endl;
		}

		int lastOR = zeitschriftenSearch_local.lastIndexOf("OR");
		zeitschriftenSearch_local = zeitschriftenSearch_local.remove(lastOR, 20);

		QString request = QString("SELECT * FROM ")+ZEITSCHRIFT_TABELLE+" WHERE "+zeitschriftenSearch_local+
				" ORDER BY "+ZEITSCHRIFT_ZEITSCHRIFT+" ASC ";

		int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getZeitschriftenForJahr_2");
		if (rc != SQLITE_OK)
		{
			   return 0; // or throw
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
		{
			int number = sqlite3_column_count(stmt);
			CZeitschrift zeitschrift;
			for (int i=0; i<number; ++i)
			{

				QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
				QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
				zeitschrift.setDBElement(columnName,columnText);
			}
			int index = -1;

			m_zeitschriftenForJahrDisplay->AddElement(zeitschrift,index);// UpdateZeitschrift(zeitschrift,index);
		}
	}

    return m_zeitschriftenForJahrDisplay->rowCount();
}


void CListenController::getAusgabenForJahr(int jahr)
{
	//m_jahrgaengeDisplay->deleteAusgaben();
	m_ausgabenForJahrDisplay->deleteAll();
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

	QString request = QString ("SELECT * FROM ")+ARTIKEL_TABELLE+" WHERE "+ARTIKEL_JAHR+"='"+jahr+"' "+
			searchForString+" ORDER BY "+ARTIKEL_ZEITSCHRIFT+" ASC, "+ARTIKEL_JAHR+" ASC, "+ARTIKEL_AUSGABE+" ASC, "+ARTIKEL_SEITE+" ASC";
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getAusgabenForJahr");
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		   return; // or throw
	}

	QMap<QString,CAusgabeDisplayList::searchStruct> ausgaben_map;
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		int number = sqlite3_column_count(stmt);
		CArtikel artikel;
		CAusgabeDisplayList::searchStruct ausgabe;
		for (int i=0; i<number; ++i)
		{

			QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
			 artikel.setDBElement(columnName,columnText);
			 ausgabe.setDBElement(columnName,columnText);
		}

		m_artikelDisplay->AddElement(artikel);
		ausgaben_map.insert(ausgabe.getAsString(),ausgabe);
	}

	if (ausgaben_map.count()>0)
	{
		Helper helper;
		QString ausgabenSearch_local;
		QMapIterator<QString,CAusgabeDisplayList::searchStruct> iter(ausgaben_map);
		//zeitschriftenSearch_local = QString("WHERE ");
		while (iter.hasNext()) {
			iter.next();
			ausgabenSearch_local += QString(" ( ")+AUSGABE_ZEITSCHRIFT+QString("='")+helper.fixSpecialCharacters(iter.value().magazin)+"' AND "
								  + AUSGABE_JAHR + QString("='%1'").arg(iter.value().jahr)+ " AND "
								  + AUSGABE_AUSGABE + QString("='%1'").arg(iter.value().ausgabe)+ " ) "
								  +" OR ";
		}
		int lastOR = ausgabenSearch_local.lastIndexOf("OR");
		ausgabenSearch_local = ausgabenSearch_local.remove(lastOR, 20);

		QString request = QString("SELECT * FROM ")+AUSGABE_TABELLE+" WHERE "+ausgabenSearch_local+
				" ORDER BY "+AUSGABE_ZEITSCHRIFT+" ASC, "+AUSGABE_JAHR+" ASC, "+AUSGABE_AUSGABE+" ASC ";

		int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getAusgabenForJahr_2");
		if (rc != SQLITE_OK)
		{
			   return; // or throw
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
		{
			int number = sqlite3_column_count(stmt);
			CAusgabe ausgabe;
			for (int i=0; i<number; ++i)
			{

				QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
				QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
				ausgabe.setDBElement(columnName,columnText);
			}
			int index = -1;

			m_ausgabenForJahrDisplay->AddElement(ausgabe,index);// UpdateZeitschrift(zeitschrift,index);
		}
	}
	sqlite3_finalize(stmt);
}

void CListenController::getAusgabenForZeitschrift(QString zeitschrift, int jahr)
{
    //m_jahrgaengeDisplay->deleteAusgaben();
    m_ausgabenForJahrDisplay->deleteAll();
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
	Helper helper;


	QString request = QString ("SELECT * FROM ")+ARTIKEL_TABELLE+
			" WHERE "+ARTIKEL_JAHR+"='"+QString("%1").arg(jahr)+"' AND "+ARTIKEL_ZEITSCHRIFT+"='"+helper.fixSpecialCharacters(zeitschrift)+"' "+
			searchForString+" ORDER BY "+ARTIKEL_ZEITSCHRIFT+" ASC, "+ARTIKEL_JAHR+" ASC, "+ARTIKEL_AUSGABE+" ASC, "+ARTIKEL_SEITE+" ASC";
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getAusgabenForZeitschrift");
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		   return; // or throw
	}
	QMap<QString,CAusgabeDisplayList::searchStruct> ausgaben_map;
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		int number = sqlite3_column_count(stmt);
		CArtikel artikel;
		CAusgabeDisplayList::searchStruct ausgabe;
		for (int i=0; i<number; ++i)
		{

			QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
			ausgabe.setDBElement(columnName,columnText);
			artikel.setDBElement(columnName,columnText);
		}

		ausgaben_map.insert(ausgabe.getAsString(),ausgabe);
		m_artikelDisplay->AddElement(artikel);
	}

	if (ausgaben_map.count()>0)
	{
		Helper helper;
		QString ausgabenSearch_local;
		QMapIterator<QString,CAusgabeDisplayList::searchStruct> iter(ausgaben_map);
		//zeitschriftenSearch_local = QString("WHERE ");
		while (iter.hasNext()) {
			iter.next();
			ausgabenSearch_local += QString(" ( ")+AUSGABE_ZEITSCHRIFT+QString("='")+helper.fixSpecialCharacters(iter.value().magazin)+"' AND "
								  + AUSGABE_JAHR + QString("='%1'").arg(iter.value().jahr)+ " AND "
								  + AUSGABE_AUSGABE + QString("='%1'").arg(iter.value().ausgabe)+ " ) "
								  +" OR ";
		}
		int lastOR = ausgabenSearch_local.lastIndexOf("OR");
		ausgabenSearch_local = ausgabenSearch_local.remove(lastOR, 20);

		QString request = QString("SELECT * FROM ")+AUSGABE_TABELLE+" WHERE "+ausgabenSearch_local+
				" ORDER BY "+AUSGABE_ZEITSCHRIFT+" ASC, "+AUSGABE_JAHR+" ASC, "+AUSGABE_AUSGABE+" ASC ";

		int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getAusgabenForZeitschrift_2");
		if (rc != SQLITE_OK)
		{
			   return; // or throw
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
		{
			int number = sqlite3_column_count(stmt);
			CAusgabe ausgabe;
			for (int i=0; i<number; ++i)
			{

				QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
				QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
				ausgabe.setDBElement(columnName,columnText);
			}
			int index = -1;

			m_ausgabenForJahrDisplay->AddElement(ausgabe,index);// UpdateZeitschrift(zeitschrift,index);
		}
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

	Helper helper;
	QString request = QString("SELECT * FROM Inhalte WHERE Jahr='%1' AND Ausgabe='%2' AND Zeitschrift='%3' %4 ORDER BY Zeitschrift ASC, Jahr ASC,Ausgabe ASC,Seite ASC").arg(jahr).arg(ausgabe).arg(helper.fixSpecialCharacters(zeitschrift)).arg(searchForString);
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
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
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
//    sqlite3_stmt *stmt;
    char *zErrMsg;

    QString request = QString("INSERT INTO %1 DEFAULT VALUES").arg(ARTIKEL_TABELLE);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
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


int CListenController::addNewEmptyRowToZeitschriftTable()
{
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return -1;
    }
//    sqlite3_stmt *stmt;
    char *zErrMsg;

    QString request = QString("INSERT INTO %1 DEFAULT VALUES").arg(ZEITSCHRIFT_TABELLE);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
    if (rc !=0 )
    {
        qDebug()<<"addNewEmptyRowToZeitschriftTable: SqLite request returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
        return -1;
    }
    else
    {
        qDebug()<<":addNewEmptyRowToZeitschriftTable: SqLite request returned OK for "<<request;

    }
    int index = static_cast<int>(sqlite3_last_insert_rowid(m_db));
 //   sqlite3_finalize(stmt);
    return index;

}


void CListenController::updateAusgabenTable( const CAusgabe &Ausgabe)
{
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
 //   sqlite3_stmt *stmt;
    char *zErrMsg;
    QString sqlElements = Ausgabe.getAsSQLString(true);
    QString request = QString("UPDATE %1 %2").arg(AUSGABE_TABELLE).arg(sqlElements);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
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


int CListenController::addNewEmptyRowToAusgabenTable()
{
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return -1;
    }
//    sqlite3_stmt *stmt;
    char *zErrMsg;

    QString request = QString("INSERT INTO %1 DEFAULT VALUES").arg(AUSGABE_TABELLE);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
    if (rc !=0 )
    {
        qDebug()<<"addNewEmptyRowToAusgabenTable: SqLite request returned "<<sqlite3_errstr(rc)<<" ("<<rc<<") for "<<request;
        return -1;
    }
    else
    {
        qDebug()<<":addNewEmptyRowToZeitschriftTable: SqLite request returned OK for "<<request;

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
//    sqlite3_stmt *stmt;
    char *zErrMsg;

    QString request = QString("DELETE FROM Inhalte WHERE UniqueIndex='%1'").arg(index);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
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

void CListenController::setRubrikDisplay(QString zeitschrift)
{
   int zeitschriftIndex=-1;
    CZeitschrift zeitschriftStruct = m_zeitschriftenDisplay->getZeitschrift(zeitschrift,zeitschriftIndex);
    if ( zeitschriftIndex >= 0)
    {
        m_RubrikenList->SetList(zeitschriftStruct.getRubrikList());
    }
    else
    {
        m_RubrikenList->deleteAll();
    }

}

void CListenController::updateRubrikListDisplay(QString filter)
{
    m_RubrikenList->UpdateListDisplay(filter);
}

void CListenController::setZeitschriftSelectionDisplay()
{

   QList<QString> zeitschriftenList;
   for (int i=0; i<m_zeitschriftenDisplay->rowCount(); ++i)
   {
       zeitschriftenList << m_zeitschriftenDisplay->getZeitschrift(i).getZeitschrift();

   }
    if ( zeitschriftenList.count() >= 0)
    {
        m_ZeitschriftenListForSelection->SetList(zeitschriftenList);
    }
    else
    {
        m_ZeitschriftenListForSelection->deleteAll();
    }

}

void CListenController::updateZeitschriftSelectionDisplay(QString filter)
{
      m_ZeitschriftenListForSelection->UpdateListDisplay(filter);

}


void CListenController::setSloganDisplay(QString zeitschrift)
{
	int zeitschriftIndex=-1;
	 CZeitschrift zeitschriftStruct = m_zeitschriftenDisplay->getZeitschrift(zeitschrift,zeitschriftIndex);
	 if ( zeitschriftIndex >= 0)
	 {
		 m_SloganList->SetList(zeitschriftStruct.getSloganList());
	 }
	 else
	 {
		 m_SloganList->deleteAll();
	 }
}
void CListenController::setRedaktionDisplay(QString zeitschrift)
{
	int zeitschriftIndex=-1;
	 CZeitschrift zeitschriftStruct = m_zeitschriftenDisplay->getZeitschrift(zeitschrift,zeitschriftIndex);
	 if ( zeitschriftIndex >= 0)
	 {
		 m_redaktionList->SetList(zeitschriftStruct.getRedaktionList());
	 }
	 else
	 {
		 m_redaktionList->deleteAll();
	 }
}
void CListenController::updateSloganListDisplay(QString filter)
{
	m_SloganList->UpdateListDisplay(filter);
}
void CListenController::updateWaehrungListDisplay(QString filter)
{
	m_waehrungsList->UpdateListDisplay(filter);
}
void CListenController::updateRedaktionListDisplay(QString filter)
{
	m_redaktionList->UpdateListDisplay(filter);
}


void CListenController::updateInhalteTable(const CArtikel &Artikel)// QString sqlElements)
{
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
 //   sqlite3_stmt *stmt;
    char *zErrMsg;
	QString sqlElements = Artikel.getArtikelAsSQLString(true);
    QString request = QString("UPDATE Inhalte %1").arg(sqlElements);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
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

	//Check ob Zeitschrift neu gemacht werden muß
	CZeitschrift zeitschrift = getZeitschriftByName(Artikel.getZeitschrift());  //  m_zeitschriftenDisplay->getZeitschrift(Artikel.getZeitschrift(),zeitschriftIndex);
	if (zeitschrift.getUniqueIndex()<0)
    {
       int unique_index = addNewEmptyRowToZeitschriftTable();
       zeitschrift.setUniqueIndex(unique_index);
        zeitschrift.setZeitschrift(Artikel.getZeitschrift());
        zeitschrift.setSprache(Artikel.getSprache());
        updateZeitschriftenTable(zeitschrift,true);
        emit newZeitschriftDetected(zeitschrift);
    }

	//Check, ob Ausgabe neu gemacht werden muß
	CAusgabeDisplayList::searchStruct ausgabeData;
	ausgabeData.magazin = Artikel.getZeitschrift();
	ausgabeData.jahr = Artikel.getJahr();
	ausgabeData.ausgabe = Artikel.getAusgabe();
	CAusgabe ausgabe = getAusgabeByData(ausgabeData);
	if (ausgabe.getUniqueIndex() <0)
	{
	   int unique_index = addNewEmptyRowToAusgabenTable();
	   ausgabe.setUniqueIndex(unique_index);
		ausgabe.setZeitschrift(Artikel.getZeitschrift());
		ausgabe.setJahr(Artikel.getJahr());
		ausgabe.setAusgabe(Artikel.getAusgabe());
		zeitschrift.setSprache(Artikel.getSprache());
		updateAusgabenTable(ausgabe);
		emit newAusgabeDetected(ausgabe);
	}

//	getListOfZeitschriften();
    return;
}

void CListenController::updateZeitschriftenTable( const CZeitschrift &Zeitschrift, bool refresh)
{
    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return;
    }
 //   sqlite3_stmt *stmt;
    char *zErrMsg;
    QString sqlElements = Zeitschrift.getAsSQLString(true);
    QString request = QString("UPDATE Zeitschriften %1").arg(sqlElements);
    int rc = sqlite3_exec(m_db,request.toStdString().c_str(),nullptr,nullptr,&zErrMsg);
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

    if (refresh)
    {
        getListOfZeitschriften();
    }
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

    QString request = QString("SELECT * FROM Inhalte WHERE UniqueIndex='%1'").arg(index);
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
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            artikel.setDBElement(columnName,columnText);

        }
        counter ++;

      }

    sqlite3_finalize(stmt);
    return artikel;
}

CZeitschrift CListenController::getZeitschriftByIndex(int index)
{
    CZeitschrift zeitschrift;


    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return zeitschrift;
    }
    sqlite3_stmt *stmt;

    QString request = QString("SELECT * FROM Zeitschriften WHERE UniqueIndex='%1'").arg(index);
//    qDebug()<<request;

    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getZeitschriftByIndex");
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
           return zeitschrift; // or throw
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
             return zeitschrift;
          }
        int number = sqlite3_column_count(stmt);

        for (int i=0; i<number; ++i)
        {

           QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            zeitschrift.setDBElement(columnName,columnText);

        }
        counter ++;

      }

    sqlite3_finalize(stmt);
    return zeitschrift;
}

CAusgabe CListenController::getAusgabeByIndex(int dbIndex)
{
    CAusgabe ausgabe;


    if (m_db == nullptr)
    {
        qDebug()<<"No open DB!";
        return ausgabe;
    }
    sqlite3_stmt *stmt;

    QString request = QString("SELECT * FROM %1 WHERE UniqueIndex='%2'").arg(AUSGABE_TABELLE).arg(dbIndex);
//    qDebug()<<request;

    int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getZeitschriftByIndex");
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
           return ausgabe; // or throw
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
             qDebug()<<"Index "<<dbIndex<<" nicht eindeutig";
             return ausgabe;
          }
        int number = sqlite3_column_count(stmt);

        for (int i=0; i<number; ++i)
        {

           QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
            QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
           ausgabe.setDBElement(columnName,columnText);

        }
        counter ++;

      }

    sqlite3_finalize(stmt);
    return ausgabe;
}


void CListenController::getTableNamesFromDB()
{
    char **result;
    int row;int column;

 /*   if (!m_sqldb.isOpen())
    {
        qDebug()<<"No open DB!";
        return;

    }

    QSqlQuery query;
    query.exec("SELECT * from Inhalte");
   */
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


CZeitschrift CListenController::getZeitschriftByName(const QString& name)
{
	CZeitschrift zeitschrift;
	if (m_db == nullptr)
	{
		qDebug()<<"No open DB!";
		return zeitschrift;
	}
	sqlite3_stmt *stmt;
		Helper helper;
	QString request = QString ("SELECT * FROM ")+ZEITSCHRIFT_TABELLE+" WHERE "+ZEITSCHRIFT_ZEITSCHRIFT"='"+helper.fixSpecialCharacters(name)+"'";
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getZeitschriftByName");
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		   return zeitschrift; // or throw
	}
	int counter =0;
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		  if (counter > 0)
		  {
			 qDebug()<<"getZeitschriftByName: Name "<<name<<" nicht eindeutig";
			 return zeitschrift;
		  }
		int number = sqlite3_column_count(stmt);

		for (int i=0; i<number; ++i)
		{

		   QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
			zeitschrift.setDBElement(columnName,columnText);

		}
		counter ++;

	  }
	sqlite3_finalize(stmt);
	return zeitschrift;
}



CAusgabe CListenController::getAusgabeByData(CAusgabeDisplayList::searchStruct& name)
{
	CAusgabe ausgabe;
	if (m_db == nullptr)
	{
		qDebug()<<"No open DB!";
		return ausgabe;
	}
	sqlite3_stmt *stmt;
		Helper helper;
	QString request = QString ("SELECT * FROM ")+AUSGABE_TABELLE+" WHERE "
			+AUSGABE_ZEITSCHRIFT"='"+helper.fixSpecialCharacters(name.magazin)+"' "
			+" AND "+AUSGABE_JAHR+QString("='%1' ").arg(name.jahr)
			+" AND "+AUSGABE_AUSGABE+QString("='%1' ").arg(name.ausgabe);
	int rc = makeSQLiteSearch(request.toStdString().c_str(),&stmt,"getZeitschriftByName");
//	int rc = sqlite3_prepare_v2(m_db, request.toStdString().c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		   return ausgabe; // or throw
	}
	int counter =0;
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		  if (counter > 0)
		  {
			 qDebug()<<"getAusgabeByData:"<<name.getAsString()<< " nicht eindeutig";
			 return ausgabe;
		  }
		int number = sqlite3_column_count(stmt);

		for (int i=0; i<number; ++i)
		{

		   QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
			ausgabe.setDBElement(columnName,columnText);

		}
		counter ++;

	  }
	sqlite3_finalize(stmt);
	return ausgabe;
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
	Helper helper;
	QString searchElement = helper.fixSpecialCharacters(m_searchElement);
    QMapIterator<QString, CColumn> i(m_searchTables);
    while (i.hasNext()) {
        i.next();
        if (i.value().searchable())
        {
			searchString += QString(" %1 LIKE '%%2%' OR ").arg(i.key()).arg(searchElement);
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
		Helper helper;
        for (int i=0;i<zeitschriften.count();i++)
        {
			zeitschriftenSearch += QString("Zeitschrift='%1' OR ").arg(helper.fixSpecialCharacters(zeitschriften.at(i)));
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
    m_ausgabenForJahrDisplay->deleteAll();
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
			QByteArray columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
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
    QTime startTime = QTime::currentTime();
    int rc = sqlite3_prepare_v2(m_db,request.toStdString().c_str() , -1, stmt, nullptr);
    QTime endTime = QTime::currentTime();
    int doneIn = startTime.msecsTo(endTime);
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
    qDebug()<<"Finished in "<<doneIn;
    return rc;
}

void AddElementToSprachenList(QString element);
void AddElementToWaehrungsList (QString element);
