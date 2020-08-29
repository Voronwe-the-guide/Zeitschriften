#include "cartikel.h"

CArtikel::CArtikel():
	m_Ausgabe(0),
	m_Jahr(0),
    m_Seite(0)
{

}

bool CArtikel::setDBElement(QString columnName, QString columnEntry)
{
	columnName = columnName.toLower();

	if (columnName == "ausgabe"){ setAusgabe(columnEntry.toInt()); return true;}
	else if (columnName == "jahr") { setJahr(columnEntry.toInt()); return true;}
	else if (columnName == "rubrik") { setRubrik(columnEntry); return true;}
	else if (columnName == "ueberschrift") { setUeberschrift(columnEntry); return true;}
	else if (columnName == "zusammenfassung") { setZusammenfassung(columnEntry); return true;}
	else if (columnName == "kurztext") { setKurztext(columnEntry); return true;}
	else if (columnName == "seite") { setSeite(columnEntry.toInt()); return true;}
	else if (columnName == "autor") { setAutor(columnEntry); return true;}
	else if (columnName == "fotos") { setFotos(columnEntry); return true;}
	else if (columnName == "schlagworte") { setSchlagworte(columnEntry); return true;}
    else if (columnName == "zeitschrift") {setZeitschrift(columnEntry); return true;}
    else if (columnName == "land") {setLand(columnEntry); return true;}
    else if (columnName == "koordinate") {setKoordinate(columnEntry); return true;}
    else if (columnName == "aenderungszeit") {setLastChange(columnEntry); return true;}

	return false;
}


QString CArtikel::Zeitschrift() const
{
	return m_Zeitschrift;
}

void CArtikel::setZeitschrift(const QString &Zeitschrift)
{
	m_Zeitschrift = Zeitschrift;
}

int CArtikel::Jahr() const
{
	return m_Jahr;
}

void CArtikel::setJahr(int Jahr)
{
	m_Jahr = Jahr;
}

int CArtikel::Ausgabe() const
{
	return m_Ausgabe;
}

void CArtikel::setAusgabe(int Ausgabe)
{
	m_Ausgabe = Ausgabe;
}

int CArtikel::Seite() const
{
	return m_Seite;
}

void CArtikel::setSeite(int Seite)
{
	m_Seite = Seite;
}

QString CArtikel::Rubrik() const
{
	return m_Rubrik;
}

void CArtikel::setRubrik(const QString &Rubrik)
{
	m_Rubrik = Rubrik;
}

QString CArtikel::Ueberschrift() const
{
    return m_Ueberschrift;
}

void CArtikel::setUeberschrift(const QString &Ueberschrift)
{
   m_Ueberschrift = Ueberschrift;
}

QString CArtikel::Zusammenfassung() const
{
	return m_Zusammenfassung;
}

void CArtikel::setZusammenfassung(const QString &Zusammenfassung)
{
	m_Zusammenfassung = Zusammenfassung;
}

QString CArtikel::Kurztext() const
{
	return m_Kurztext;
}

void CArtikel::setKurztext(const QString &Kurztext)
{
	m_Kurztext = Kurztext;
}

QString CArtikel::Autor() const
{
	return m_Autor;
}

void CArtikel::setAutor(const QString &Autor)
{
	m_Autor = Autor;
}

QString CArtikel::Fotos() const
{
	return m_Fotos;
}

void CArtikel::setFotos(const QString &Fotos)
{
	m_Fotos = Fotos;
}

QString CArtikel::Schlagworte() const
{
	return m_Schlagworte;
}

void CArtikel::setSchlagworte(const QString &Schlagworte)
{
	m_Schlagworte = Schlagworte;
}

QString CArtikel::Land() const
{
	return m_Land;
}

void CArtikel::setLand(const QString &Land)
{
	m_Land = Land;
}

QGeoCoordinate CArtikel::Koordinate() const
{
	return m_Koordinate;
}
QString CArtikel::KoordinateAsString() const
{
    if (Koordinate().isValid())
    {
        return Koordinate().toString(QGeoCoordinate::Degrees);
    }
    return "";
}

void CArtikel::setKoordinate(const QGeoCoordinate &koordinate)
{
    m_Koordinate = koordinate;
}
void CArtikel::setKoordinate(const QString &koordinate)
{
    QStringList coordinates = koordinate.split(",");
    if (coordinates.size()>=2)
    {
        QString latitude = coordinates.at(0);
        QString longitude = coordinates.at(1);
        latitude.remove("°");
        longitude.remove("°");
        QGeoCoordinate coord;
        bool latOk = true;
        bool longOk = true;
        coord.setLatitude(latitude.toDouble(&latOk));
        coord.setLongitude(longitude.toDouble(&longOk));
        if (coord.isValid())
        {
            setKoordinate(coord);
        }
    }
}

QDateTime CArtikel::lastChange() const
{
    return m_lastChange;
}

QString CArtikel::lastChangeAsString() const
{
    if (lastChange().isValid())
    {
        return lastChange().toString(Qt::ISODate);
    }
    return "";

}

 void CArtikel::setLastChange(const QString &lastChange)
 {
     QDateTime date = QDateTime::fromString(lastChange,Qt::ISODate);
     if (date.isValid())
     {
         setLastChange(date);
     }
 }

void CArtikel::setLastChange(const QDateTime &lastChange)
{
    m_lastChange = lastChange;
}


