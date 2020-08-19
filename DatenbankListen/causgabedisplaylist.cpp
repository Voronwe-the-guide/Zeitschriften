#include "causgabedisplaylist.h"

const int  CAusgabeDisplayList::Role_Jahr  = Qt::UserRole+1;
const int  CAusgabeDisplayList::Role_Ausgabe  = Qt::UserRole+2;
const int  CAusgabeDisplayList::Role_Zeitschrift = Qt::UserRole+3;

CAusgabeDisplayList::CAusgabeDisplayList(sqlite3 *db, QObject *parent) :
	QAbstractListModel(parent),
	m_db(db)
{

}

CAusgabeDisplayList::~CAusgabeDisplayList()
{
	deleteAll();
}

int CAusgabeDisplayList::rowCount ( const QModelIndex & /*parent*/) const
{
	return m_AusgabenList.count();
}
int CAusgabeDisplayList::columnCount ( const QModelIndex & /*parent*/) const
{
	return 3;
}

QVariant CAusgabeDisplayList::data ( const QModelIndex & index, int role) const
{
	QVariant ret = QVariant::Invalid;
	 if(index.row() < m_AusgabenList.size())
	{
		CAusgabe temp = m_AusgabenList[index.row()];
		switch (role)
		{
			case Qt::DisplayRole:
			case Role_Jahr: return temp.Jahr();
			case Role_Ausgabe: return temp.Ausgabe();
			case Role_Zeitschrift: return temp.Zeitschrift();
		}
	}

	return ret;
}

/*!
 * from: https://stackoverflow.com/questions/15836253/c-populate-vector-from-sqlite3-callback-function
 * Answer by: https://stackoverflow.com/users/11654/cl
 */
void CAusgabeDisplayList::getAusgabenForJahr(int jahr)
{
	deleteAll();
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

		AddAusgabe(ausgabe);
	}

	sqlite3_finalize(stmt);

}

void CAusgabeDisplayList::deleteAll()
{
	if (!(m_AusgabenList.isEmpty()))
	{
		beginRemoveRows(QModelIndex(),0,(rowCount()-1));//This is to keep the list in QML updated
		 m_AusgabenList.clear();
		 endRemoveRows();
	}

	emit listEmpty();
}


void CAusgabeDisplayList::AddAusgabe(CAusgabe &ausgabe)
{
	for (int i=0; i<m_AusgabenList.count(); i++)
	{
		if ((ausgabe.Jahr() == m_AusgabenList.at(i).Jahr()) && (ausgabe.Ausgabe() == m_AusgabenList.at(i).Ausgabe()))
		{
			//Allready there
			return;
		}
	}
	beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
	m_AusgabenList << ausgabe;
	endInsertRows();

}

QHash<int, QByteArray> CAusgabeDisplayList::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[Role_Jahr] = "jahr";
	roles[Role_Ausgabe] = "ausgabe";
	roles[Role_Zeitschrift] = "zeitschrift";

	return roles;
}
