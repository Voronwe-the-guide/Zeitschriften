#include "causgabeeditor.h"

CAusgabeEditor::CAusgabeEditor(CListenController *listen, QObject *parent):
    QObject(parent),
    m_listen(listen),
    m_somethingHasChanged(false)

{
    QObject::connect(this, &CAusgabeEditor::ausgabeDisplayUpdated, this, &CAusgabeEditor::coverDisplayUpdated);
    QObject::connect(this, &CAusgabeEditor::coverUpdated, this, &CAusgabeEditor::coverDisplayUpdated);

    QObject::connect(m_listen, &CListenController::newAusgabeDetected, this, &CAusgabeEditor::getForUpdate);

	QObject::connect(this, &CAusgabeEditor::zeitschriftUpdated, m_listen, &CListenController::setSloganDisplay); //To show Rubrik only for this Zeitung
	QObject::connect(this, &CAusgabeEditor::zeitschriftUpdated, m_listen, &CListenController::setRedaktionDisplay); //To show Rubrik only for this Zeitung

	QObject::connect(this, &CAusgabeEditor::zeitschriftUpdated, m_listen, &CListenController::updateZeitschriftSelectionDisplay);
	QObject::connect(this, &CAusgabeEditor::waehrungUpdated, m_listen, &CListenController::updateWaehrungListDisplay);
//	QObject::connect(this, &CAusgabeEditor::waehrungUpdated, m_listen, &CListenController::updateSpracheListDisplay);
	QObject::connect(this, &CAusgabeEditor::untertitelUpdated, m_listen, &CListenController::updateSloganListDisplay);
	QObject::connect(this, &CAusgabeEditor::chefredakteurUpdated, m_listen, &CListenController::updateRedaktionListDisplay);



}

bool CAusgabeEditor::getSomethingHasChanged() const
{
    return m_somethingHasChanged;
}
void CAusgabeEditor::setSomethingHasChanged(bool somethingHasChanged)
{
    m_somethingHasChanged = somethingHasChanged;

}

bool CAusgabeEditor::isAusgabeValid() const
{
	if (getAusgabe()>0)
		return true;

	return false;
//	return getAusgabe()>0;
}
bool CAusgabeEditor::isZeitschriftValid() const
{
    return !getZeitschrift().isEmpty();
}
bool CAusgabeEditor::isJahrValid() const
{
	if (getJahr()>0)
		return true;

	return false;
}


void CAusgabeEditor::setNew()
{
    CAusgabe ausgabe;
    setForUpdate(ausgabe);
}


void CAusgabeEditor::setForUpdate(int dbIndex)
{
    CAusgabe ausgabe = m_listen->getAusgabeByIndex(dbIndex);
   setForUpdate(ausgabe);

}

void CAusgabeEditor::setForUpdate(CAusgabe ausgabe)
{
    m_ausgabe = ausgabe;
    setSomethingHasChanged(false);
    emit ausgabeDisplayUpdated();

}

void CAusgabeEditor::getForUpdate(CAusgabe ausgabe)
{
    setForUpdate(ausgabe);

}


int CAusgabeEditor::saveChangesInDB(bool fromNew)
{
    bool dataIsValid =true;
    dataIsValid = dataIsValid && isZeitschriftValid();
    dataIsValid = dataIsValid && isAusgabeValid();
    dataIsValid = dataIsValid && isJahrValid();

    if (!dataIsValid)
    {
        emit entryIsNotValid();
        return -1;
    }

    if (fromNew)
    {
        CAusgabeDisplayList::searchStruct search;
        search.magazin = m_ausgabe.getZeitschrift();
        search.jahr = m_ausgabe.getJahr();
        search.ausgabe = m_ausgabe.getAusgabe();

        CAusgabe ausgabe = m_listen->getAusgabeByData( search);
        int index = ausgabe.getUniqueIndex();
        if (index>=0)
        {
            emit entryAllreadyThere();
            return -2;
        }
    }

    if (m_ausgabe.getUniqueIndex()<0)
    {
        storeNew();
    }
    else
    {
        saveUpdate();
    }
    return 0;
}

void CAusgabeEditor::saveUpdate()
{
    if (getSomethingHasChanged())
    {
       // m Artikel.setLastChange(QDateTime::currentDateTime());
      //  QString sqlRequest = m_Artikel.getArtikelAsSQLString(true);
        m_listen->updateAusgabenTable(m_ausgabe);
    }
}
void CAusgabeEditor::storeNew()
{
    int index = m_listen->addNewEmptyRowToAusgabenTable();

    if (index>=0)
    {
        m_ausgabe.setUniqueIndex(index);
       // QString sqlRequest = m_Artikel.getArtikelAsSQLString(true);
        m_listen->updateAusgabenTable(m_ausgabe);
     }


}


int CAusgabeEditor::getAusgabe() const
{
    return m_ausgabe.getAusgabe();
}
void CAusgabeEditor::setAusgabe(int Ausgabe)
{
    m_ausgabe.setAusgabe(Ausgabe);
    setSomethingHasChanged(true);
    emit ausgabeUpdated(Ausgabe);
}

int CAusgabeEditor:: getJahr() const
{
    return  m_ausgabe.getJahr();
}

void CAusgabeEditor::setJahr(int input)
{
	m_ausgabe.setJahr(input);
    setSomethingHasChanged(true);
	emit jahrUpdated(input);

}

QString CAusgabeEditor::getZeitschrift() const
{
    return  m_ausgabe.getZeitschrift();

}
void CAusgabeEditor::setZeitschrift(const QString & input)
{
    m_ausgabe.setZeitschrift(input);
    setSomethingHasChanged(true);
    emit zeitschriftUpdated(input);

}

QString CAusgabeEditor::getCover() const
{
    return  m_ausgabe.getCover();

}
void CAusgabeEditor::setCover(const QString & input)
{
    m_ausgabe.setCover(input);
    setSomethingHasChanged(true);
    emit coverUpdated(input);

}

QString CAusgabeEditor::getPreis() const
{
    return m_ausgabe.getPreisAsString();

}

void CAusgabeEditor::setPreis(QString input)
{
    m_ausgabe.setPreis(input);
    setSomethingHasChanged(true);
    emit preisUpdated(input);

}

QString CAusgabeEditor::getWaehrung() const
{
    return  m_ausgabe.getWaehrung();

}
void CAusgabeEditor::setWaehrung(const QString & input)
{
    m_ausgabe.setWaehrung(input);
    setSomethingHasChanged(true);
    emit waehrungUpdated(input);

}

int CAusgabeEditor::getSeitenzahl() const
{
    return  m_ausgabe.getSeitenzahl();

}
void CAusgabeEditor::setSeitenzahl(int  input)
{
    m_ausgabe.setSeitenzahl(input);
    setSomethingHasChanged(true);
    emit seitenzahlUpdated(input);

}

QString CAusgabeEditor::getChefredakteur() const
{
    return  m_ausgabe.getChefredakteur();

}
void CAusgabeEditor::setChefredakteur(const QString & input)
{
    m_ausgabe.setChefredakteur(input);
    setSomethingHasChanged(true);
    emit chefredakteurUpdated(input);

}

QString CAusgabeEditor::getNotizen() const
{
    return  m_ausgabe.getNotizen();

}
void CAusgabeEditor::setNotizen(const QString & input)
{
    m_ausgabe.setNotizen(input);
    setSomethingHasChanged(true);
    emit notizenUpdated(input);

}

QString CAusgabeEditor::getSprache() const
{
    return  m_ausgabe.getSprache();

}
void CAusgabeEditor::setSprache(const QString & input)
{
    m_ausgabe.setSprache(input);
    setSomethingHasChanged(true);
    emit spracheUpdated(input);

}

QString CAusgabeEditor::getUntertitel() const
{
    return  m_ausgabe.getUntertitel();

}
void CAusgabeEditor::setUntertitel (const QString & input)
{
    m_ausgabe.setUntertitel(input);
    setSomethingHasChanged(true);
    emit untertitelUpdated(input);

}

