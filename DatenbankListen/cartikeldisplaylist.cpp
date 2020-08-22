#include "cartikeldisplaylist.h"



const int  CArtikelDisplayList::Role_Zeitschrift = Qt::UserRole+1;
const int  CArtikelDisplayList::Role_Jahr  = Qt::UserRole+2;					//!< Jahrgang der Zeitschrift
const int  CArtikelDisplayList::Role_Ausgabe = Qt::UserRole+3;				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
const int  CArtikelDisplayList::Role_Seite = Qt::UserRole+4;				//!< Seitennummer
const int  CArtikelDisplayList::Role_Rubrik = Qt::UserRole+5;
const int  CArtikelDisplayList::Role_Ueberschrift = Qt::UserRole+6;
const int  CArtikelDisplayList::Role_Zusammenfassung = Qt::UserRole+7;
const int  CArtikelDisplayList::Role_Kurztext = Qt::UserRole+8;
const int  CArtikelDisplayList::Role_Autor = Qt::UserRole+9;
const int  CArtikelDisplayList::Role_Fotos = Qt::UserRole+10;
const int  CArtikelDisplayList::Role_Schlagworte = Qt::UserRole+11;
const int  CArtikelDisplayList::Role_Land = Qt::UserRole+12;
const int  CArtikelDisplayList::Role_Koordinate = Qt::UserRole+13;




CArtikelDisplayList::CArtikelDisplayList(QObject *parent) :
    QAbstractListModel(parent)

{

}

CArtikelDisplayList::~CArtikelDisplayList()
{

}

int CArtikelDisplayList::rowCount ( const QModelIndex & /*parent*/) const
{
	return m_ArtikelList.count();
}
int CArtikelDisplayList::columnCount ( const QModelIndex & /*parent*/) const
{
	return 13;
}

QVariant CArtikelDisplayList::data ( const QModelIndex & index, int role) const
{
	QVariant ret = QVariant::Invalid;
	 if(index.row() < m_ArtikelList.size())
	{
		CArtikel temp = m_ArtikelList[index.row()];
		switch (role)
		{
			case Qt::DisplayRole:
			case Role_Zeitschrift:	return temp.Zeitschrift();
			case Role_Jahr: return temp.Jahr();					//!< Jahrgang der Zeitschrift
			case Role_Ausgabe: return temp.Ausgabe();				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
			case Role_Seite: return temp.Seite();				//!< Seitennummer
			case Role_Rubrik: return temp.Rubrik();
			case Role_Ueberschrift: return temp.Ueberschrift();
			case Role_Zusammenfassung: return temp.Zusammenfassung();
			case Role_Kurztext: return temp.Kurztext();
			case Role_Autor: return temp.Autor();
			case Role_Fotos: return temp.Fotos();
			case Role_Schlagworte: return temp.Schlagworte();
			case Role_Land: return temp.Land();
	//		case Role_Koordinate: return temp.Koordinate();
		}
	}

	return ret;
}

/*!
 * from: https://stackoverflow.com/questions/15836253/c-populate-vector-from-sqlite3-callback-function
 * Answer by: https://stackoverflow.com/users/11654/cl
 */

void CArtikelDisplayList::deleteAll()
{
	if (!(m_ArtikelList.isEmpty()))
	{
		beginRemoveRows(QModelIndex(),0,(rowCount()-1));//This is to keep the list in QML updated
		 m_ArtikelList.clear();
		 endRemoveRows();
	}
	emit listEmpty();
}


void CArtikelDisplayList::AddArtikel(CArtikel &artikel)
{
	beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
	m_ArtikelList << artikel;
	endInsertRows();

}

QHash<int, QByteArray> CArtikelDisplayList::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[Role_Zeitschrift] = "zeitschrift";
	roles[Role_Jahr] = "jahr";					//!< Jahrgang der Zeitschrift
	roles[Role_Ausgabe] = "ausgabe";				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
	roles[Role_Seite] = "seite";				//!< Seitennummer
	roles[Role_Rubrik] = "rubrik";
	roles[Role_Ueberschrift] = "ueberschrift";
	roles[Role_Zusammenfassung] = "zusammenfassung";
	roles[Role_Kurztext] = "kurztext";
	roles[Role_Autor] = "autor";
	roles[Role_Fotos] = "fotos";
	roles[Role_Schlagworte] = "schlagworte";
	roles[Role_Land] = "land";
	roles[Role_Koordinate] = "koordinate";

	return roles;
}
