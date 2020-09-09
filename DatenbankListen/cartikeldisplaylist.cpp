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
			case Role_Zeitschrift:	return temp.Zeitschrift();
			case Role_Jahr: return temp.Jahr();					//!< Jahrgang der Zeitschrift
			case Role_Ausgabe: return temp.Ausgabe();				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
			case Role_Seite: return temp.Seite();				//!< Seitennummer
			case Role_Rubrik: return temp.Rubrik();
            case Role_Ueberschrift: return HighlightSearchElement(temp.Ueberschrift());
            case Role_Zusammenfassung: return HighlightSearchElement(temp.Zusammenfassung());
            case Role_Kurztext: return HighlightSearchElement(temp.Kurztext());
            case Role_Autor: return HighlightSearchElement(temp.Autor());
            case Role_Fotos: return HighlightSearchElement(temp.Fotos());
            case Role_Schlagworte: return HighlightSearchElement(temp.Schlagworte());
            case Role_Land: return HighlightSearchElement(temp.Land());
            case Role_Index: return temp.DBIndex();
            case Role_Notizen: return temp.getNotizen();
            case Role_Koordinate: return temp.KoordinateAsString();
            case Role_Latitude: return temp.Koordinate().latitude();
            case Role_Longitude: return temp.Koordinate().longitude();
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
    return getArtikel(index).Zeitschrift();
}
int CArtikelDisplayList::getJahr(int index)
{
    return getArtikel(index).Jahr();

}
int CArtikelDisplayList::getAusgabe(int index)
{
    return getArtikel(index).Ausgabe();

}
int CArtikelDisplayList::getSeite(int index)
{
    return getArtikel(index).Seite();

}
QString CArtikelDisplayList::getRubrik(int index)
{
    return getArtikel(index).Rubrik();

}
QString CArtikelDisplayList::getUeberschrift(int index)
{
    return getArtikel(index).Ueberschrift();

}
QString CArtikelDisplayList::getZusammenfassung(int index)
{
    return getArtikel(index).Zusammenfassung();

}
QString CArtikelDisplayList::getKurztext(int index)
{
    return getArtikel(index).Kurztext();

}
QString CArtikelDisplayList::getAutor(int index)
{
    return getArtikel(index).Autor();

}
QString CArtikelDisplayList::getFotos(int index)
{
    return getArtikel(index).Fotos();

}
QString CArtikelDisplayList::getSchlagworte(int index)
{
    return getArtikel(index).Schlagworte();

}
QString CArtikelDisplayList::getLand(int index)
{
    return getArtikel(index).Land();

}
int CArtikelDisplayList::getDBIndex(int index)
{
    return getArtikel(index).DBIndex();

}
QString CArtikelDisplayList::getNotizen(int index)
{
    return getArtikel(index).getNotizen();

}
double CArtikelDisplayList::getLatitude(int index)
{
    return getArtikel(index).Koordinate().latitude();

}
double CArtikelDisplayList::getLongitude(int index)
{
    return getArtikel(index).Koordinate().longitude();

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
