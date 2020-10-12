#include "cartikeleditor.h"

CArtikelEditor::CArtikelEditor(CListenController *listen,QObject *parent) :
    QObject(parent),
    m_listen(listen),
    m_somethingHasChanged(false)
{

    QObject::connect(this, &CArtikelEditor::zeitschriftUpdated, m_listen, &CListenController::setRubrikDisplay); //To show Rubrik only for this Zeitung

    QObject::connect(this, &CArtikelEditor::rubrikUpdated, m_listen, &CListenController::updateRubrikListDisplay);
    QObject::connect(this, &CArtikelEditor::zeitschriftUpdated, m_listen, &CListenController::updateZeitschriftSelectionDisplay);
}

void CArtikelEditor::setNewArtikel()
{
    CArtikel artikel;
    setArtikelForUpdate(artikel);

}

bool CArtikelEditor::saveAndNext(bool fromNew)
{
	bool retVal = true;
    retVal = saveChangesInDB(fromNew);
	if(!retVal)
	{
		return false;
	}
    CArtikel newOne;
	newOne.setJahr(m_Artikel.getJahr());
	newOne.setAusgabe(m_Artikel.getAusgabe());
	newOne.setRubrik(m_Artikel.getRubrik());
	newOne.setZeitschrift(m_Artikel.getZeitschrift());
    newOne.setSprache(m_Artikel.getSprache());
    setArtikelForUpdate(newOne);
	return true;

}
void CArtikelEditor::setArtikelForUpdate(int dbIndex)
{
    CArtikel artikel = m_listen->getArtikelByIndex(dbIndex);
    setArtikelForUpdate(artikel);

}

void CArtikelEditor::setArtikelForUpdate(CArtikel artikel)
{
    m_Artikel = artikel;
    setSomethingHasChanged(false);
    emit artikelDisplayUpdated();
    emit zeitschriftUpdated(m_Artikel.getZeitschrift());

}

CArtikel CArtikelEditor::getArtikel() const
{
    return m_Artikel;
}

bool CArtikelEditor::isZeitschriftValid() const
{
	return !getZeitschrift().isEmpty();
}
bool CArtikelEditor::isJahrValid() const
{
	return (getJahr()>0);
}
bool CArtikelEditor::isAusgabeValid() const
{
	return (getAusgabe()>0);

}
bool CArtikelEditor::isSeiteValid() const
{
	return (getSeite()>0);



}

QString CArtikelEditor::getZeitschrift() const
{
	return m_Artikel.getZeitschrift();
}
void CArtikelEditor::setZeitschrift(const QString &Zeitschrift)
{
    m_Artikel.setZeitschrift(Zeitschrift);
    setSomethingHasChanged(true);
    emit zeitschriftUpdated(Zeitschrift);
}

int CArtikelEditor::getJahr() const
{
	return m_Artikel.getJahr();
}
void CArtikelEditor::setJahr(int Jahr)
{

    m_Artikel.setJahr(Jahr);
    setSomethingHasChanged(true);
    emit jahrUpdated(Jahr);
}

int CArtikelEditor::getAusgabe() const
{
	return m_Artikel.getAusgabe();
}

void CArtikelEditor::setAusgabe(int Ausgabe)
{
   m_Artikel.setAusgabe(Ausgabe);
    setSomethingHasChanged(true);
    emit ausgabeUpdated(Ausgabe);
}

int CArtikelEditor::getSeite() const
{
	return m_Artikel.getSeite();
}

void CArtikelEditor::setSeite(int Seite)
{
    m_Artikel.setSeite(Seite);
    setSomethingHasChanged(true);
    emit seiteUpdated(Seite);
}

QString CArtikelEditor::getRubrik() const
{
	return m_Artikel.getRubrik();
}

void CArtikelEditor::setRubrik(const QString &Rubrik)
{
    m_Artikel.setRubrik(Rubrik);
    setSomethingHasChanged(true);
    emit rubrikUpdated(Rubrik);
}

QString CArtikelEditor::getUeberschrift() const
{
	return m_Artikel.getUeberschrift();
}

void CArtikelEditor::setUeberschrift(const QString &Ueberschrift)
{
    m_Artikel.setUeberschrift(Ueberschrift);
    setSomethingHasChanged(true);
    emit ueberschriftUpdated(Ueberschrift);
}

QString CArtikelEditor::getZusammenfassung() const
{
	return m_Artikel.getZusammenfassung();
}

void CArtikelEditor::setZusammenfassung(const QString &Zusammenfassung)
{
    m_Artikel.setZusammenfassung(Zusammenfassung);
    setSomethingHasChanged(true);
    emit zusammenfassungUpdated(Zusammenfassung);
}

QString CArtikelEditor::getKurztext() const
{
	return m_Artikel.getKurztext();
}

void CArtikelEditor::setKurztext(const QString &Kurztext)
{
    m_Artikel.setKurztext(Kurztext);
    setSomethingHasChanged(true);
    emit kurztextUpdated(Kurztext);
}

QString CArtikelEditor::getAutor() const
{
	return m_Artikel.getAutor();
}

void CArtikelEditor::setAutor(const QString &Autor)
{
    m_Artikel.setAutor(Autor);
    setSomethingHasChanged(true);
    emit autorUpdated(Autor);
}

QString CArtikelEditor::getFotos() const
{
	return m_Artikel.getFotos();
}

void CArtikelEditor::setFotos(const QString &Fotos)
{
    m_Artikel.setFotos(Fotos);
    setSomethingHasChanged(true);
   emit fotosUpdated(Fotos);
}

QString CArtikelEditor::getSchlagworte() const
{
	return m_Artikel.getSchlagworte();
}

void CArtikelEditor::setSchlagworte(const QString &Schlagworte)
{
    setSomethingHasChanged(true);
    m_Artikel.setSchlagworte(Schlagworte);
    emit schlagworteUpdated(Schlagworte);
}

QString CArtikelEditor::getLand() const
{
	return m_Artikel.getLand();
}

void CArtikelEditor::setLand(const QString &Land)
{
   m_Artikel.setLand(Land);
    setSomethingHasChanged(true);
    emit landUpdated(Land);
}

QString  CArtikelEditor::getNotizen() const
{
    return m_Artikel.getNotizen();
}
void  CArtikelEditor::setNotizen(const QString &Notizen)
{
    m_Artikel.setNotizen(Notizen);
    setSomethingHasChanged(true);
    emit notizenUpdated(Notizen);
}

QString CArtikelEditor::getSprache() const
{
    return m_Artikel.getSprache();
}
void CArtikelEditor::setSprache(const QString &Sprache)
{
    m_Artikel.setSprache(Sprache);
    setSomethingHasChanged(true);
    emit spracheUpdated(Sprache);

}



double CArtikelEditor::getCurrentLat() const
{
	if (m_Artikel.getKoordinate().isValid())
    {
		return m_Artikel.getKoordinate().latitude();
    }
    return 0;
}
double CArtikelEditor::getCurrentLong() const
{
	if (m_Artikel.getKoordinate().isValid())
    {
		return m_Artikel.getKoordinate().longitude();
    }
    return 0;
}

QString CArtikelEditor::getKoordinaten() const
{
	return m_Artikel.getKoordinateAsString();
}

void CArtikelEditor::setCurrentCoordinate(double lat, double longi)
{
   QGeoCoordinate kord;
   kord.setLatitude(lat);
   kord.setLongitude(longi);
    m_Artikel.setKoordinate(kord);
    setSomethingHasChanged(true);
    emit coordinateDisplayUpdated();
}

bool CArtikelEditor::getSomethingHasChanged() const
{
    return m_somethingHasChanged;
}

void CArtikelEditor::setSomethingHasChanged(bool somethingHasChanged)
{
    m_somethingHasChanged = somethingHasChanged;
  //  emit artikelDisplayUpdated();
}


bool CArtikelEditor::saveChangesInDB(bool fromNew)
{

	bool dataIsValid =true;

	dataIsValid = dataIsValid && isZeitschriftValid();
	dataIsValid = dataIsValid && isJahrValid();
	dataIsValid = dataIsValid && isAusgabeValid();
	dataIsValid = dataIsValid && isSeiteValid();
	if (!dataIsValid)
	{
		emit entryIsNotValid();
		return false;
    }

   if (m_Artikel.getUniqueIndex()<0)
   {
       storeNewArtikel();
   }
   else
   {
       saveUpdate();
   }

   if (fromNew)
   {

     int jahrIndex = m_listen->jahrgaengeDisplay()->getIndexInList(m_Artikel.getJahr());
     m_listen->getZeitschriftenForJahr(m_Artikel.getJahr());
     m_listen->getAusgabenForZeitschrift(m_Artikel.getZeitschrift(),m_Artikel.getJahr());

     int listIndex= m_listen->setListAfterNewArtikel(m_Artikel);
     int zeitschriftIndex=-1;
     CZeitschrift zeit = m_listen->zeitschriftenForJahrDisplay()->getZeitschrift(m_Artikel.getZeitschrift(),zeitschriftIndex);
     CAusgabe ausgabe;
     ausgabe.setZeitschrift(m_Artikel.getZeitschrift());
     ausgabe.setJahr(m_Artikel.getJahr());
     ausgabe.setAusgabe(m_Artikel.getAusgabe());
     int ausgabeIndex = m_listen->ausgabenForJahrDisplay()->getIndexInList(ausgabe);

     emit displayJahrIndex(jahrIndex);
     emit displayZeitschriftInJahrIndex(zeitschriftIndex);
     emit displayAusgabeInJahrIndex(ausgabeIndex);
     emit displayArtikelIndex(listIndex);
   }
   return true;

}

void CArtikelEditor::saveUpdate()
{
    if (getSomethingHasChanged())
    {
        m_Artikel.setLastChange(QDateTime::currentDateTime());
	  //  QString sqlRequest = m_Artikel.getArtikelAsSQLString(true);
		m_listen->updateInhalteTable(m_Artikel);
    }

}

void CArtikelEditor::storeNewArtikel()
{
    m_Artikel.setLastChange(QDateTime::currentDateTime());
    int index = m_listen->addNewEmptyRowToInhalte();

    if (index>=0)
    {
        m_Artikel.setUniqueIndex(index);
        QString sqlRequest = m_Artikel.getAsSQLString(true);
		m_listen->updateInhalteTable(m_Artikel);
     }

}

