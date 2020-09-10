#include "causgabedisplaylist.h"

const int  CAusgabeDisplayList::Role_Jahr  = Qt::UserRole+1;
const int  CAusgabeDisplayList::Role_Ausgabe  = Qt::UserRole+2;
const int  CAusgabeDisplayList::Role_Zeitschrift = Qt::UserRole+3;

CAusgabeDisplayList::CAusgabeDisplayList(QObject *parent) :
    QAbstractListModel(parent)
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
			case Role_Jahr: return temp.getJahr();
			case Role_Ausgabe: return temp.getAusgabe();
			case Role_Zeitschrift: return temp.getZeitschrift();
		}
	}

	return ret;
}

/*!
 * from: https://stackoverflow.com/questions/15836253/c-populate-vector-from-sqlite3-callback-function
 * Answer by: https://stackoverflow.com/users/11654/cl
 */

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


void CAusgabeDisplayList::AddElement(CAusgabe &ausgabe)
{
	for (int i=0; i<m_AusgabenList.count(); i++)
	{
		if ((ausgabe.getJahr() == m_AusgabenList.at(i).getJahr()) && (ausgabe.getAusgabe() == m_AusgabenList.at(i).getAusgabe()))
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
