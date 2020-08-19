#include "clistencontroller.h"

CListenController::CListenController(sqlite3 *db, QObject *parent) : QObject(parent)
{
	m_jahrgaengeDisplay = new CJahrDisplayList(db);
	m_ausgabenDisplay = new CAusgabeDisplayList(db);
	m_artikelDisplay = new CArtikelDisplayList(db) ;

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

void CListenController::getAusgabenForJahr(int jahr)
{
	//m_jahrgaengeDisplay->deleteAusgaben();
	m_ausgabenDisplay->deleteAll();
	char *zErrMsg = 0;
	sqlite3_stmt *stmt;
	QString request = QString("SELECT Jahr,Ausgabe FROM Inhalte WHERE Jahr='%1' ORDER BY Jahr ASC,Ausgabe ASC").arg(jahr);
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
		for (int i=0; i<number; ++i)
		{

			QString columnName(reinterpret_cast<const char*>(sqlite3_column_name(stmt,i)));
			QString columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
			ausgabe.setDBElement(columnName,columnText);
		}

		m_ausgabenDisplay->AddAusgabe(ausgabe);
	}

	sqlite3_finalize(stmt);


}
