#include "cartikel.h"
#include <QMapIterator>
#include <QDebug>
#include <Helper/helper.h>

CArtikel::CArtikel()//:
 //   m_DBIndex(-1),
 //   m_Jahr(0),
 //   m_Ausgabe(0),
 //   m_Seite(0)
{
    m_artikelMap[ARTIKEL_INDEX].setNum(-1);
	m_artikelMap[ARTIKEL_ZEITSCHRIFT] ="";
    m_artikelMap[ARTIKEL_AUSGABE]="";
    m_artikelMap[ARTIKEL_JAHR]="";
	m_artikelMap[ARTIKEL_RUBRIK] ="";
	m_artikelMap[ARTIKEL_UEBERSCHRIFT] ="";
	m_artikelMap[ARTIKEL_ZUSAMMENFASSUNG] ="";
	m_artikelMap[ARTIKEL_KURZTEXT] ="";
    m_artikelMap[ARTIKEL_SEITE]="";
	m_artikelMap[ARTIKEL_AUTOR] ="";
	m_artikelMap[ARTIKEL_FOTOS] ="";
	m_artikelMap[ARTIKEL_SCHLAGWORTE] ="";
	m_artikelMap[ARTIKEL_LAND] ="";
	m_artikelMap[ARTIKEL_NOTIZEN] ="";
    m_artikelMap[ARTIKEL_LONGITUDE].setNum(0);
	m_artikelMap[ARTIKEL_LATITUDE].setNum(0);
	m_artikelMap[ARTIKEL_AENDERUNGSZEIT] ="";
    m_artikelMap[ARTIKEL_SPRACHE]="";
}

bool CArtikel::setDBElement(const QString& columnName, const QByteArray& columnEntry)
{

	if (m_artikelMap.contains(columnName))
	{
		m_artikelMap[columnName] = columnEntry;
		return true;
	}

	return false;

}


QString CArtikel::getZeitschrift() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_ZEITSCHRIFT))
	{
		result = m_artikelMap[ARTIKEL_ZEITSCHRIFT];
	}
	return result;
}

void CArtikel::setZeitschrift(const QString &Zeitschrift)
{
   setText(ARTIKEL_ZEITSCHRIFT,Zeitschrift);// m_artikelMap[ARTIKEL_ZEITSCHRIFT] = Zeitschrift.toUtf8();
}

int CArtikel::getJahr() const
{
	int result = -1;
	if (m_artikelMap.contains(ARTIKEL_JAHR))
	{
		result = m_artikelMap[ARTIKEL_JAHR].toInt();
	}
	return result;
}

void CArtikel::setJahr(int Jahr)
{
	m_artikelMap[ARTIKEL_JAHR].setNum(Jahr);

 //   qDebug()<<"Neues Jahr: "<<m_artikelMap[ARTIKEL_JAHR];
}

int CArtikel::getAusgabe() const
{
	int result = -1;
	if (m_artikelMap.contains(ARTIKEL_AUSGABE))
	{
		result = m_artikelMap[ARTIKEL_AUSGABE].toInt();
	}
	return result;
}

void CArtikel::setAusgabe(int Ausgabe)
{
	m_artikelMap[ARTIKEL_AUSGABE].setNum(Ausgabe);
}

int CArtikel::getSeite() const
{
	int result = -1;
	if (m_artikelMap.contains(ARTIKEL_SEITE))
	{
		result = m_artikelMap[ARTIKEL_SEITE].toInt();
	}
	return result;
}

void CArtikel::setSeite(int Seite)
{
    m_artikelMap[ARTIKEL_SEITE].setNum(Seite);
}

QString CArtikel::getRubrik() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_RUBRIK))
	{
		result = m_artikelMap[ARTIKEL_RUBRIK];
	}
	return result;
}

void CArtikel::setRubrik(const QString &Rubrik)
{
	setText(ARTIKEL_RUBRIK,Rubrik);// m_artikelMap[ARTIKEL_RUBRIK] = Rubrik.toUtf8();

}

QString CArtikel::getUeberschrift() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_UEBERSCHRIFT))
	{
		result = m_artikelMap[ARTIKEL_UEBERSCHRIFT];
	}
	return result;
}

void CArtikel::setUeberschrift(const QString &Ueberschrift)
{
	setText(ARTIKEL_UEBERSCHRIFT,Ueberschrift); // m_artikelMap[ARTIKEL_UEBERSCHRIFT] = Ueberschrift.toUtf8();

}

QString CArtikel::getZusammenfassung() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_ZUSAMMENFASSUNG))
	{
		result = m_artikelMap[ARTIKEL_ZUSAMMENFASSUNG];
	}
	return result;
}

void CArtikel::setZusammenfassung(const QString &Zusammenfassung)
{
	setText(ARTIKEL_ZUSAMMENFASSUNG,Zusammenfassung); m_artikelMap[ARTIKEL_ZUSAMMENFASSUNG] = Zusammenfassung.toUtf8();

}

QString CArtikel::getKurztext() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_KURZTEXT))
	{
		result = m_artikelMap[ARTIKEL_KURZTEXT];
	}
	return result;
}

void CArtikel::setKurztext(const QString &Kurztext)
{
	setText(ARTIKEL_KURZTEXT,Kurztext);// m_artikelMap[ARTIKEL_KURZTEXT] = Kurztext.toUtf8();

}

QString CArtikel::getAutor() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_AUTOR))
	{
		result = m_artikelMap[ARTIKEL_AUTOR];
	}
	return result;
}

void CArtikel::setAutor(const QString &Autor)
{
	setText(ARTIKEL_AUTOR,Autor);// m_artikelMap[ARTIKEL_AUTOR] = Autor.toUtf8();

}

QString CArtikel::getFotos() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_FOTOS))
	{
		result = m_artikelMap[ARTIKEL_FOTOS];
	}
	return result;
}

void CArtikel::setFotos(const QString &Fotos)
{
	setText(ARTIKEL_FOTOS,Fotos);// m_artikelMap[ARTIKEL_FOTOS] = Fotos.toUtf8();

}

QString CArtikel::getSchlagworte() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_SCHLAGWORTE))
	{
		result = m_artikelMap[ARTIKEL_SCHLAGWORTE];
	}
	return result;
}

void CArtikel::setSchlagworte(const QString &Schlagworte)
{
	setText(ARTIKEL_SCHLAGWORTE,Schlagworte);//  m_artikelMap[ARTIKEL_SCHLAGWORTE] = Schlagworte.toUtf8();

}

QString CArtikel::getLand() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_LAND))
	{
		result = m_artikelMap[ARTIKEL_LAND];
	}
	return result;
}

void CArtikel::setLand(const QString &Land)
{
	setText(ARTIKEL_LAND,Land);   //m_artikelMap[ARTIKEL_LAND] = Land.toUtf8();

}

QString CArtikel::getSprache() const
{
    QString result;
    if (m_artikelMap.contains(ARTIKEL_SPRACHE))
    {
        result = m_artikelMap[ARTIKEL_SPRACHE];
    }
    return result;
}


void CArtikel::setSprache(const QString &Sprache)
{
   setText(ARTIKEL_SPRACHE,Sprache);
}


QGeoCoordinate CArtikel::getKoordinate() const
{
	QGeoCoordinate koordinate;

	if ((m_artikelMap.contains(ARTIKEL_LATITUDE)) && (m_artikelMap.contains(ARTIKEL_LONGITUDE)))
	{
		double latitude = m_artikelMap[ARTIKEL_LATITUDE].toDouble();
		double longitude = m_artikelMap[ARTIKEL_LONGITUDE].toDouble();
		if (((latitude>0.1) || (latitude<-0.1)) && ((longitude>0.1) || (longitude<-0.1))) //Thank goodness 0/0 is in the Ocean
		{
			koordinate.setLatitude(latitude);
			koordinate.setLongitude(longitude);
		}
	}
	return koordinate;
}
QString CArtikel::getKoordinateAsString() const
{
	if (getKoordinate().isValid())
    {
		return getKoordinate().toString(QGeoCoordinate::Degrees);
    }
    return "";
}

void CArtikel::setKoordinate(const QGeoCoordinate &koordinate)
{
	 m_artikelMap[ARTIKEL_LONGITUDE].setNum(koordinate.longitude());
	 m_artikelMap[ARTIKEL_LATITUDE].setNum(koordinate.latitude());
}
void CArtikel::setKoordinate(const QString& whichOne, const QString &partOfkoordinate)
{
   if (partOfkoordinate != "")
   {
	  if (whichOne == ARTIKEL_LONGITUDE)
      {
		  m_artikelMap[ARTIKEL_LONGITUDE] = partOfkoordinate.toUtf8();
      }
	  else if (whichOne == ARTIKEL_LONGITUDE)
      {
		  m_artikelMap[ARTIKEL_LATITUDE] = partOfkoordinate.toUtf8();
	  }
   }
}

QDateTime CArtikel::getLastChange() const
{
	QString lastChange = getLastChangeAsString();
	QDateTime date;
	if (lastChange != "")
	{
	 date = QDateTime::fromString(lastChange,Qt::ISODate);
	 date.setTimeSpec(Qt::OffsetFromUTC);
	}
	return date;
}

QString CArtikel::getLastChangeAsString() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_AENDERUNGSZEIT))
	{
		result = m_artikelMap[ARTIKEL_AENDERUNGSZEIT];
	}
	return result;

/*	if (getLastChange().isValid())
    {
		return getLastChange().toString(Qt::ISODate);
    }
    return "";
*/
}

 void CArtikel::setLastChange(const QString &lastChange)
 {

	 m_artikelMap[ARTIKEL_AENDERUNGSZEIT] = lastChange.toUtf8();

	/* QDateTime date = QDateTime::fromString(lastChange,Qt::ISODate);
     date.setTimeSpec(Qt::OffsetFromUTC);
     if (date.isValid())
     {
         setLastChange(date);
     }
	 */
 }

void CArtikel::setLastChange(const QDateTime &lastChange)
{
	QString strChange;
    if (lastChange.isValid())
	{
         strChange = lastChange.toString(Qt::ISODate);
	}
	 setLastChange(strChange);

	/*QDateTime temp = lastChange;
    temp.setTimeSpec(Qt::OffsetFromUTC);
    m_lastChange = lastChange;
	*/
}

int CArtikel::getDBIndex() const
{
	int result = -1;
	if (m_artikelMap.contains(ARTIKEL_INDEX))
	{
		result = m_artikelMap[ARTIKEL_INDEX].toInt();
	}
	return result;
}

void CArtikel::setDBIndex(int index)
{
	m_artikelMap[ARTIKEL_INDEX].setNum(index);
}

QString CArtikel::getNotizen() const
{
	QString result;
	if (m_artikelMap.contains(ARTIKEL_NOTIZEN))
	{
		result = m_artikelMap[ARTIKEL_NOTIZEN];
	}
	return result;
}

void CArtikel::setNotizen(const QString &Notizen)
{
	setText(ARTIKEL_NOTIZEN,Notizen);// m_artikelMap[ARTIKEL_NOTIZEN] = Notizen.toUtf8();

}
QString CArtikel::getArtikelAsSQLString(bool include_whereID) const
{
    QString artikel = "SET ";

 /*   QMapIterator<QString, QByteArray> i(m_artikelMap);
    while (i.hasNext()) {
        i.next();
        if (i.key()!=ARTIKEL_INDEX)
        {
            artikel += QString(" %1 = '%2',").arg(i.key()).arg(i.value().toStdString()) ;
        }
//        cout << i.key() << ": " << i.value() << Qt::endl;
    }
*/
	Helper helper;
    artikel +=QString(" %1 = '%2'").arg(ARTIKEL_AUSGABE).arg(helper.fixSpecialCharacters(getAusgabe()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_JAHR).arg(helper.fixSpecialCharacters(getJahr()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_RUBRIK).arg(helper.fixSpecialCharacters(getRubrik()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_UEBERSCHRIFT).arg(helper.fixSpecialCharacters(getUeberschrift()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_ZUSAMMENFASSUNG).arg(helper.fixSpecialCharacters(getZusammenfassung()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_KURZTEXT).arg(helper.fixSpecialCharacters(getKurztext()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_SEITE).arg(helper.fixSpecialCharacters(getSeite()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_AUTOR).arg(helper.fixSpecialCharacters(getAutor()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_FOTOS).arg(helper.fixSpecialCharacters(getFotos()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_SCHLAGWORTE).arg(helper.fixSpecialCharacters(getSchlagworte()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_ZEITSCHRIFT).arg(helper.fixSpecialCharacters(getZeitschrift()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_LAND).arg(helper.fixSpecialCharacters(getLand()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_SPRACHE).arg(helper.fixSpecialCharacters(getSprache()));

	if (getKoordinate().isValid())
    {
        artikel +=QString(", %1 = '%2'").arg(ARTIKEL_LONGITUDE).arg(getKoordinate().longitude());
        artikel +=QString(", %1 = '%2'").arg(ARTIKEL_LATITUDE).arg(getKoordinate().latitude());
    }
    else
    {
        artikel +=QString(", %1 = ''").arg(ARTIKEL_LONGITUDE);
        artikel +=QString(", %1 = ''").arg(ARTIKEL_LATITUDE);

    }
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_AENDERUNGSZEIT).arg(helper.fixSpecialCharacters(getLastChangeAsString()));
    artikel +=QString(", %1 = '%2'").arg(ARTIKEL_NOTIZEN).arg(helper.fixSpecialCharacters(getNotizen()));

    if (include_whereID)
    {
       artikel += QString(" WHERE %1='%2'").arg(ARTIKEL_INDEX).arg(getDBIndex());
    }

	return artikel;
}

void CArtikel::setText(QString key, QString text)
{
	//text = fixSpecialCharacters(text);
	m_artikelMap[key]=text.toUtf8();
}




