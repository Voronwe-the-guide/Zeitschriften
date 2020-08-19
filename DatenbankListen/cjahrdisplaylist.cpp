#include "Cjahrdisplaylist.h"

const int  CJahrDisplayList::Role_Jahr  = Qt::UserRole+1;

CJahrDisplayList::CJahrDisplayList(sqlite3 *db, QObject *parent) :
	QAbstractListModel(parent),
	m_db(db)
{

}

CJahrDisplayList::~CJahrDisplayList()
{

}

int CJahrDisplayList::rowCount ( const QModelIndex & /*parent*/) const
{
	return m_JahrList.count();
}
int CJahrDisplayList::columnCount ( const QModelIndex & /*parent*/) const
{
	return 1;
}

QVariant CJahrDisplayList::data ( const QModelIndex & index, int role) const
{
	QVariant ret = QVariant::Invalid;
	 if(index.row() < m_JahrList.size())
	{
		CJahr temp = m_JahrList[index.row()];
		switch (role)
		{
			case Qt::DisplayRole:
			case Role_Jahr: return temp.Jahr();					//!< Jahrgang der Zeitschrift
		}
	}

	return ret;
}

/*!
 * from: https://stackoverflow.com/questions/15836253/c-populate-vector-from-sqlite3-callback-function
 * Answer by: https://stackoverflow.com/users/11654/cl
 */
void CJahrDisplayList::GetDBRequest()
{
	deleteAll();
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

		AddJahr(jahr);
	}

	sqlite3_finalize(stmt);

}

void CJahrDisplayList::deleteAll()
{
	if (!(m_JahrList.isEmpty()))
	{
		beginRemoveRows(QModelIndex(),0,(rowCount()-1));//This is to keep the list in QML updated
		 m_JahrList.clear();
		 endRemoveRows();
	}
		emit listEmpty();
}


void CJahrDisplayList::AddJahr(CJahr &jahr)
{
	for (int i=0; i<m_JahrList.count(); i++)
	{
		if (jahr.Jahr() == m_JahrList.at(i).Jahr())
		{
			//Allready there
			return;
		}
	}
	beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
	m_JahrList << jahr;
	endInsertRows();

}

void CJahrDisplayList::deleteAusgaben()
{
	//m_AusgabenListe.clear();
}

void CJahrDisplayList::AddAusgabe(CAusgabe ausgabe)
{
/*	CAusgabeDisplayList list(m_db);
	if (m_AusgabenListe.contains(ausgabe.Jahr()))
	{
		list = m_AusgabenListe.value(ausgabe.Jahr());
	}
	list.AddAusgabe(ausgabe);
	m_AusgabenListe.insert(ausgabe.Jahr(),list);
*/
}

QHash<int, QByteArray> CJahrDisplayList::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[Role_Jahr] = "jahr";					//!< Jahrgang der Zeitschrift

	return roles;
}
