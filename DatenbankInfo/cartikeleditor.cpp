#include "cartikeleditor.h"

CArtikelEditor::CArtikelEditor(CListenController *listen,QObject *parent) :
    QObject(parent),
    m_listen(listen),
    m_somethingHasChanged(false)
{

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
}

CArtikel CArtikelEditor::getArtikel() const
{
    return m_Artikel;
}

QString CArtikelEditor::getZeitschrift() const
{
    return m_Artikel.Zeitschrift();
}
void CArtikelEditor::setZeitschrift(const QString &Zeitschrift)
{
    m_Artikel.setZeitschrift(Zeitschrift);
    setSomethingHasChanged(true);
    emit zeitschriftUpdated(Zeitschrift);
}

int CArtikelEditor::getJahr() const
{
    return m_Artikel.Jahr();
}
void CArtikelEditor::setJahr(int Jahr)
{
    m_Artikel.setJahr(Jahr);
    setSomethingHasChanged(true);
    emit jahrUpdated(Jahr);
}

int CArtikelEditor::getAusgabe() const
{
    return m_Artikel.Ausgabe();
}

void CArtikelEditor::setAusgabe(int Ausgabe)
{
    m_Artikel.setAusgabe(Ausgabe);
    setSomethingHasChanged(true);
    emit ausgabeUpdated(Ausgabe);
}

int CArtikelEditor::getSeite() const
{
    return m_Artikel.Seite();
}

void CArtikelEditor::setSeite(int Seite)
{
    m_Artikel.setSeite(Seite);
    setSomethingHasChanged(true);
    emit seiteUpdated(Seite);
}

QString CArtikelEditor::getRubrik() const
{
    return m_Artikel.Rubrik();
}

void CArtikelEditor::setRubrik(const QString &Rubrik)
{
    m_Artikel.setRubrik(Rubrik);
    setSomethingHasChanged(true);
    emit rubrikUpdated(Rubrik);
}

QString CArtikelEditor::getUeberschrift() const
{
    return m_Artikel.Ueberschrift();
}

void CArtikelEditor::setUeberschrift(const QString &Ueberschrift)
{
    m_Artikel.setUeberschrift(Ueberschrift);
    setSomethingHasChanged(true);
    emit ueberschriftUpdated(Ueberschrift);
}

QString CArtikelEditor::getZusammenfassung() const
{
    return m_Artikel.Zusammenfassung();
}

void CArtikelEditor::setZusammenfassung(const QString &Zusammenfassung)
{
    m_Artikel.setZusammenfassung(Zusammenfassung);
    setSomethingHasChanged(true);
    emit zusammenfassungUpdated(Zusammenfassung);
}

QString CArtikelEditor::getKurztext() const
{
    return m_Artikel.Kurztext();
}

void CArtikelEditor::setKurztext(const QString &Kurztext)
{
    m_Artikel.setKurztext(Kurztext);
    setSomethingHasChanged(true);
    emit kurztextUpdated(Kurztext);
}

QString CArtikelEditor::getAutor() const
{
    return m_Artikel.Autor();
}

void CArtikelEditor::setAutor(const QString &Autor)
{
    m_Artikel.setAutor(Autor);
    setSomethingHasChanged(true);
    emit autorUpdated(Autor);
}

QString CArtikelEditor::getFotos() const
{
    return m_Artikel.Fotos();
}

void CArtikelEditor::setFotos(const QString &Fotos)
{
    m_Artikel.setFotos(Fotos);
    setSomethingHasChanged(true);
   emit fotosUpdated(Fotos);
}

QString CArtikelEditor::getSchlagworte() const
{
    return m_Artikel.Schlagworte();
}

void CArtikelEditor::setSchlagworte(const QString &Schlagworte)
{
    setSomethingHasChanged(true);
    m_Artikel.setSchlagworte(Schlagworte);
    emit schlagworteUpdated(Schlagworte);
}

QString CArtikelEditor::getLand() const
{
    return m_Artikel.Land();
}

void CArtikelEditor::setLand(const QString &Land)
{
    m_Artikel.setLand(Land);
    setSomethingHasChanged(true);
    emit landUpdated(Land);
}

bool CArtikelEditor::getSomethingHasChanged() const
{
    return m_somethingHasChanged;
}

void CArtikelEditor::setSomethingHasChanged(bool somethingHasChanged)
{
    m_somethingHasChanged = somethingHasChanged;
}

void CArtikelEditor::saveChangesInDB()
{
    if (getSomethingHasChanged())
    {
        m_Artikel.setLastChange(QDateTime::currentDateTime());
        QString sqlRequest = m_Artikel.getArtikelAsSQLString(true);
        m_listen->updateInhalteTable(sqlRequest);
    }

}
