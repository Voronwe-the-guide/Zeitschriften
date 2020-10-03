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
const int  CArtikelDisplayList::Role_Index = Qt::UserRole+14;
const int  CArtikelDisplayList::Role_Notizen = Qt::UserRole+15;
const int  CArtikelDisplayList::Role_Latitude = Qt::UserRole+16;
const int  CArtikelDisplayList::Role_Longitude = Qt::UserRole+17;
const int  CArtikelDisplayList::Role_Sprache = Qt::UserRole+18;





CArtikelDisplayList::CArtikelDisplayList(QObject *parent) :
    QAbstractListModel(parent),
    m_fontColor_normal("\"black\""),
    m_fontColor_highlight("\"red\"")

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
			case Role_Zeitschrift:	return temp.getZeitschrift();
			case Role_Jahr: return temp.getJahr();					//!< Jahrgang der Zeitschrift
			case Role_Ausgabe: return temp.getAusgabe();				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
			case Role_Seite: return temp.getSeite();				//!< Seitennummer
			case Role_Rubrik: return temp.getRubrik();
			case Role_Ueberschrift: return HighlightSearchElement(temp.getUeberschrift());
			case Role_Zusammenfassung: return HighlightSearchElement(temp.getZusammenfassung());
			case Role_Kurztext: return HighlightSearchElement(temp.getKurztext());
			case Role_Autor: return HighlightSearchElement(temp.getAutor());
			case Role_Fotos: return HighlightSearchElement(temp.getFotos());
			case Role_Schlagworte: return HighlightSearchElement(temp.getSchlagworte());
			case Role_Land: return HighlightSearchElement(temp.getLand());
            case Role_Index: return temp.getUniqueIndex();
            case Role_Notizen: return temp.getNotizen();
			case Role_Koordinate: return temp.getKoordinateAsString();
			case Role_Latitude: return temp.getKoordinate().latitude();
			case Role_Longitude: return temp.getKoordinate().longitude();
            case Role_Sprache: return temp.getSprache();
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


void CArtikelDisplayList::AddElement(CArtikel &artikel)
{
	beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
	m_ArtikelList << artikel;
	endInsertRows();
    emit elementAdded(m_ArtikelList.count()-1);


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
    roles[Role_Index] = "dbindex";
    roles[Role_Notizen] = "notizen";
    roles[Role_Latitude] = "latitude";
    roles[Role_Longitude] = "longitude";
    roles[Role_Sprache] = "sprache";


    return roles;
}


CArtikel CArtikelDisplayList::getArtikel(int index)
{
    CArtikel artikel;
    if ((index >= 0) && (index<m_ArtikelList.count()))
    {
       artikel = m_ArtikelList.at(index);
    }

    return artikel;
}
QString CArtikelDisplayList::getZeitschrift(int index)
{
	return getArtikel(index).getZeitschrift();
}
int CArtikelDisplayList::getJahr(int index)
{
	return getArtikel(index).getJahr();

}
int CArtikelDisplayList::getAusgabe(int index)
{
	return getArtikel(index).getAusgabe();

}
int CArtikelDisplayList::getSeite(int index)
{
	return getArtikel(index).getSeite();

}
QString CArtikelDisplayList::getRubrik(int index)
{
	return getArtikel(index).getRubrik();

}
QString CArtikelDisplayList::getUeberschrift(int index)
{
	return getArtikel(index).getUeberschrift();

}
QString CArtikelDisplayList::getZusammenfassung(int index)
{
	return getArtikel(index).getZusammenfassung();

}
QString CArtikelDisplayList::getKurztext(int index)
{
	return getArtikel(index).getKurztext();

}
QString CArtikelDisplayList::getAutor(int index)
{
	return getArtikel(index).getAutor();

}
QString CArtikelDisplayList::getFotos(int index)
{
	return getArtikel(index).getFotos();

}
QString CArtikelDisplayList::getSchlagworte(int index)
{
	return getArtikel(index).getSchlagworte();

}
QString CArtikelDisplayList::getLand(int index)
{
	return getArtikel(index).getLand();

}

QString CArtikelDisplayList::getSprache(int index)
{
    return getArtikel(index).getSprache();
}
int CArtikelDisplayList::getDBIndex(int index)
{
    return getArtikel(index).getUniqueIndex();

}
QString CArtikelDisplayList::getNotizen(int index)
{
    return getArtikel(index).getNotizen();

}


double CArtikelDisplayList::getLatitude(int index)
{
	return getArtikel(index).getKoordinate().latitude();

}
double CArtikelDisplayList::getLongitude(int index)
{
	return getArtikel(index).getKoordinate().longitude();

}

QString CArtikelDisplayList::HighlightSearchElement(QString inputString) const
{
   QString parsedString = inputString;
    if ((m_searchElement=="" ) || (parsedString == ""))
   {
       return parsedString;
   }
   int indexOfElement = 0;
   QString startNormal = "<font color="+m_fontColor_normal+">";
   QString end = "</font>";
   QString startHighlight =  "<font color="+m_fontColor_highlight+">";
//find the first one
   indexOfElement = parsedString.indexOf(m_searchElement,indexOfElement,Qt::CaseInsensitive);
   if (indexOfElement<0)
   {
       //not in there
       return parsedString;
   }
   else if (indexOfElement == 0)
   {
       //starts with
       parsedString.insert(indexOfElement,startHighlight);
       indexOfElement = parsedString.indexOf(m_searchElement,indexOfElement,Qt::CaseInsensitive);
       parsedString.insert(indexOfElement+m_searchElement.size(),end+startNormal);
       indexOfElement += m_searchElement.size();

   }
   else if (indexOfElement >0)
   {
       parsedString.insert(0,startNormal);
       indexOfElement = 0;
   }

   do
   {
       indexOfElement = parsedString.indexOf(m_searchElement,indexOfElement,Qt::CaseInsensitive);
       if (indexOfElement < 0)
       {
           break;
       }
       parsedString.insert(indexOfElement,end+startHighlight);
       indexOfElement = parsedString.indexOf(m_searchElement,indexOfElement,Qt::CaseInsensitive);
       parsedString.insert(indexOfElement+m_searchElement.size(),end+startNormal);
       indexOfElement += m_searchElement.size();


   }while(indexOfElement>=0);

   if (!(parsedString.endsWith(end)))
   {
       parsedString += end;
    }

   return parsedString;

}


QString CArtikelDisplayList::searchElement() const
{
    return m_searchElement;
}

void CArtikelDisplayList::setSearchElement(const QString &searchElement)
{
    m_searchElement = searchElement;
}
