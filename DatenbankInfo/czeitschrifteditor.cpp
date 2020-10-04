#include "czeitschrifteditor.h"

CZeitschriftEditor::CZeitschriftEditor(CListenController *listen, QObject *parent):
    QObject(parent),
    m_listen(listen),
    m_somethingHasChanged(false)

{
    QObject::connect(this, &CZeitschriftEditor::zeitschriftDisplayUpdated, this, &CZeitschriftEditor::logoDisplayUpdated);
    QObject::connect(this, &CZeitschriftEditor::logoUpdated, this, &CZeitschriftEditor::logoDisplayUpdated);

    QObject::connect(m_listen, &CListenController::newZeitschriftDetected, this, &CZeitschriftEditor::getForUpdate);
}

void CZeitschriftEditor::setNew()
{
    CZeitschrift zeitschrift;
    setForUpdate(zeitschrift);

}
/*
bool CZeitschriftEditor::saveAndNext()
{
    bool retVal = true;
    retVal = saveChangesInDB();
    if(!retVal)
    {
        return false;
    }
    CArtikel newOne;
    newOne.setJahr(m_Artikel.getJahr());
    newOne.setAusgabe(m_Artikel.getAusgabe());
    newOne.setRubrik(m_Artikel.getRubrik());
    newOne.setZeitschrift(m_Artikel.getZeitschrift());
    setArtikelForUpdate(newOne);
    return true;

}

*/
void CZeitschriftEditor::setForUpdate(int dbIndex)
{
    CZeitschrift zeitschrift = m_listen->getZeitschriftByIndex(dbIndex);
   setForUpdate(zeitschrift);

}

void CZeitschriftEditor::setForUpdate(CZeitschrift zeitschrift)
{
    m_zeitschrift = zeitschrift;
    setSomethingHasChanged(false);
    emit zeitschriftDisplayUpdated();

}

void CZeitschriftEditor::getForUpdate(CZeitschrift zeitschrift)
{
    setForUpdate(zeitschrift);
}

bool CZeitschriftEditor::getSomethingHasChanged() const
{
    return m_somethingHasChanged;
}
void CZeitschriftEditor::setSomethingHasChanged(bool somethingHasChanged)
{
    m_somethingHasChanged = somethingHasChanged;
}

int CZeitschriftEditor::saveChangesInDB(bool fromNew)
{
    bool dataIsValid =true;
    dataIsValid = dataIsValid && isNameValid();
    if (!dataIsValid)
    {
        emit entryIsNotValid();
        return -1;
    }
    if (fromNew)
    {
       CZeitschrift zeitschrift = m_listen->getZeitschriftByName(m_zeitschrift.getZeitschrift());
        int index = zeitschrift.getUniqueIndex();
        if (index>=0)
        {
            emit entryAllreadyThere();
            return -2;
        }
    }

    if (m_zeitschrift.getUniqueIndex()<0)
    {
        storeNew();
    }
    else
    {
        saveUpdate();
    }
    return 0;
}


bool CZeitschriftEditor::isNameValid() const
{
    return !getName().isEmpty();
}

QString CZeitschriftEditor::getName() const
{
    return m_zeitschrift.getZeitschrift();
}
void  CZeitschriftEditor::setName(const QString &Zeitschrift)
{
    m_zeitschrift.setZeitschrift(Zeitschrift);
    setSomethingHasChanged(true);
    emit zeitschriftNameUpdated(Zeitschrift);
}

QString CZeitschriftEditor::getLogoAdress() const
{
    return m_zeitschrift.getLogo();
}

void CZeitschriftEditor::setLogoAdress(const QString &LogoAdress)
{
    m_zeitschrift.setLogo(LogoAdress);
    setSomethingHasChanged(true);
    emit logoUpdated(LogoAdress);

}

QString  CZeitschriftEditor::getBeschreibung() const
{
    return m_zeitschrift.getBeschreibung();
}

void  CZeitschriftEditor::setBeschreibung(const QString &beschreibung)
{
    m_zeitschrift.setBeschreibung(beschreibung);
    setSomethingHasChanged(true);
    emit beschreibungUpdated(beschreibung);
}

QString  CZeitschriftEditor::getNotizen() const
{
    return m_zeitschrift.getNotizen();
}
void  CZeitschriftEditor::setNotizen(const QString &notizen)
{
    m_zeitschrift.setNotizen(notizen);
    setSomethingHasChanged(true);
    emit notizenUpdated(notizen);
}


QString CZeitschriftEditor::getSprache() const
{
    return m_zeitschrift.getSprache();
}
void CZeitschriftEditor::setSprache(const QString &sprache)
{
    m_zeitschrift.setSprache(sprache);
    setSomethingHasChanged(true);
    emit spracheUpdated(sprache);
}


void CZeitschriftEditor::saveUpdate()
{
    if (getSomethingHasChanged())
    {
       // m Artikel.setLastChange(QDateTime::currentDateTime());
      //  QString sqlRequest = m_Artikel.getArtikelAsSQLString(true);
        m_listen->updateZeitschriftenTable(m_zeitschrift,true);
    }

}

void CZeitschriftEditor::storeNew()
{
   // m_zeitschrift.setLastChange(QDateTime::currentDateTime());
    int index = m_listen->addNewEmptyRowToZeitschriftTable();

    if (index>=0)
    {
        m_zeitschrift.setUniqueIndex(index);
       // QString sqlRequest = m_Artikel.getArtikelAsSQLString(true);
        m_listen->updateZeitschriftenTable(m_zeitschrift,true);
     }

}
