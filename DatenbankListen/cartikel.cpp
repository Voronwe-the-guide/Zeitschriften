#include "cartikel.h"

CArtikel::CArtikel():
    m_DBIndex(-1),
    m_Jahr(0),
    m_Ausgabe(0),
    m_Seite(0)
{

}

bool CArtikel::setDBElement(QString columnName, QString columnEntry)
{
    //columnName = columnName.toLower();

    if (columnName == "Ausgabe"){ m_artikelMap[columnName] = columnEntry; setAusgabe(columnEntry.toInt()); return true;}
    else if (columnName == "Jahr") { m_artikelMap[columnName] = columnEntry; setJahr(columnEntry.toInt()); return true;}
    else if (columnName == "Rubrik") { m_artikelMap[columnName] = columnEntry; setRubrik(columnEntry); return true;}
    else if (columnName == "Ueberschrift") { m_artikelMap[columnName] = columnEntry; setUeberschrift(columnEntry); return true;}
    else if (columnName == "Zusammenfassung") {m_artikelMap[columnName] = columnEntry; setZusammenfassung(columnEntry); return true;}
    else if (columnName == "Kurztext") {m_artikelMap[columnName] = columnEntry; setKurztext(columnEntry); return true;}
    else if (columnName == "Seite") {m_artikelMap[columnName] = columnEntry; setSeite(columnEntry.toInt()); return true;}
    else if (columnName == "Autor") {m_artikelMap[columnName] = columnEntry; setAutor(columnEntry); return true;}
    else if (columnName == "Fotos") {m_artikelMap[columnName] = columnEntry; setFotos(columnEntry); return true;}
    else if (columnName == "Schlagworte") {m_artikelMap[columnName] = columnEntry; setSchlagworte(columnEntry); return true;}
    else if (columnName == "Zeitschrift") {m_artikelMap[columnName] = columnEntry;setZeitschrift(columnEntry); return true;}
    else if (columnName == "Land") {m_artikelMap[columnName] = columnEntry;setLand(columnEntry); return true;}
    else if (columnName == "Koordinate") {m_artikelMap[columnName] = columnEntry;setKoordinate(columnEntry); return true;}
    else if (columnName == "Aenderungszeit") {m_artikelMap[columnName] = columnEntry;setLastChange(columnEntry); return true;}
    else if (columnName == "UniqueIndex") {m_artikelMap[columnName] = columnEntry;setDBIndex(columnEntry.toInt()); return true;}

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
     date.setTimeSpec(Qt::OffsetFromUTC);
     if (date.isValid())
     {
         setLastChange(date);
     }
 }

void CArtikel::setLastChange(const QDateTime &lastChange)
{
    QDateTime temp = lastChange;
    temp.setTimeSpec(Qt::OffsetFromUTC);
    m_lastChange = lastChange;
}

int CArtikel::DBIndex() const
{
    return m_DBIndex;
}

void CArtikel::setDBIndex(int index)
{
    m_DBIndex = index;
}

QString CArtikel::getArtikelAsSQLString(bool include_whereID)
{
    QString artikel = "SET ";
    artikel += QString(" Ausgabe = '%1',").arg(Ausgabe());
    artikel +=QString(" Jahr = '%1',").arg(Jahr());
    artikel +=QString(" Rubrik = '%1',").arg(Rubrik());
    artikel +=QString(" Ueberschrift = '%1',").arg(Ueberschrift());
    artikel +=QString(" Zusammenfassung = '%1',").arg(Zusammenfassung());
    artikel +=QString(" Kurztext = '%1',").arg(Kurztext());
    artikel +=QString(" Seite = '%1',").arg(Seite());
    artikel +=QString(" Autor = '%1',").arg(Autor());
    artikel +=QString(" Fotos = '%1',").arg(Fotos());
    artikel +=QString(" Schlagworte = '%1',").arg(Schlagworte());
    artikel +=QString(" Zeitschrift = '%1',").arg(Zeitschrift());
    artikel +=QString(" Land = '%1',").arg(Land());
    artikel +=QString(" Koordinate = '%1',").arg(KoordinateAsString());
    artikel +=QString(" Aenderungszeit = '%1'").arg(lastChangeAsString());

    if (include_whereID)
    {
       artikel += QString(" WHERE UniqueIndex='%1'").arg(DBIndex());
    }

    return artikel;
}


