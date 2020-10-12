#ifndef CARTIKELEDITOR_H
#define CARTIKELEDITOR_H

#include <QObject>
#include <DatenbankListen/cartikel.h>
#include <DatenbankListen/clistencontroller.h>

class CArtikelEditor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString zeitschrift READ getZeitschrift NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(int jahr	 READ getJahr NOTIFY artikelDisplayUpdated)
	Q_PROPERTY(int ausgabe	 READ getAusgabe NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(int seite READ getSeite NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString rubrik READ getRubrik NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString ueberschrift READ getUeberschrift NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString zusammenfassung READ getZusammenfassung NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString kurztext READ getKurztext NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString autor READ getAutor NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString fotos READ getFotos NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString schlagworte READ getSchlagworte NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString land READ getLand NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(QString notizen READ getNotizen NOTIFY artikelDisplayUpdated)
    Q_PROPERTY(double currentLat READ getCurrentLat NOTIFY coordinateDisplayUpdated)
    Q_PROPERTY(double currentLong READ getCurrentLong NOTIFY coordinateDisplayUpdated)
    Q_PROPERTY(QString koordinaten READ getKoordinaten NOTIFY coordinateDisplayUpdated)
    Q_PROPERTY(QString sprache READ getSprache NOTIFY artikelDisplayUpdated)

	Q_PROPERTY(bool zeitschriftValid READ isZeitschriftValid NOTIFY zeitschriftUpdated)
	Q_PROPERTY(bool jahrValid READ isJahrValid NOTIFY jahrUpdated)
	Q_PROPERTY(bool ausgabeValid READ isAusgabeValid NOTIFY ausgabeUpdated)
	Q_PROPERTY(bool seiteValid READ isSeiteValid NOTIFY seiteUpdated)


public:
    explicit CArtikelEditor(CListenController *listen, QObject *parent = nullptr);

    bool getSomethingHasChanged() const;
    void setSomethingHasChanged(bool somethingHasChanged);


signals:
    void artikelDisplayUpdated();
    void artikelUpdated(CArtikel artikel);
    void zeitschriftUpdated(QString zeitschrift);
    void jahrUpdated(int jahr);
    void ausgabeUpdated(int ausgabe);
    void seiteUpdated(int seite);
    void rubrikUpdated(QString rubrik);
    void ueberschriftUpdated(QString ueberschrift);
    void zusammenfassungUpdated(QString zusammenfassung);
    void kurztextUpdated(QString kurztext);
    void autorUpdated(QString autor);
    void fotosUpdated(QString fotos);
    void schlagworteUpdated(QString schlagworte);
    void landUpdated(QString land);
    void notizenUpdated(QString notizen);
    void coordinateDisplayUpdated();
    void spracheUpdated(QString sprache);

	void entryIsNotValid(); //Will be send back before sendig data to SQL

    void displayJahrIndex(int index);
    void displayZeitschriftInJahrIndex(int index);
    void displayAusgabeInJahrIndex(int index);
    void displayArtikelIndex(int listIndex);

public slots:

    bool saveChangesInDB(bool fromNew);
    void setNewArtikel();
    bool saveAndNext(bool fromNew);
    void setArtikelForUpdate(int dbIndex);
    void setArtikelForUpdate(CArtikel artikel);

    void saveUpdate();
    void storeNewArtikel();

    CArtikel getArtikel() const;

	bool isZeitschriftValid() const;
	bool isJahrValid() const;
	bool isAusgabeValid() const;
	bool isSeiteValid() const;

    QString getZeitschrift() const;
    void setZeitschrift(const QString &Zeitschrift);

    int getJahr() const;
    void setJahr(int Jahr);

    int getAusgabe() const;
    void setAusgabe(int Ausgabe);

    int getSeite() const;
    void setSeite(int Seite);

    QString getRubrik() const;
    void setRubrik(const QString &Rubrik);

    QString getUeberschrift() const;
    void setUeberschrift(const QString &Ueberschrift);

    QString getZusammenfassung() const;
    void setZusammenfassung(const QString &Zusammenfassung);

    QString getKurztext() const;
    void setKurztext(const QString &Kurztext);

    QString getAutor() const;
    void setAutor(const QString &Autor);

    QString getFotos() const;
    void setFotos(const QString &Fotos);

    QString getSchlagworte() const;
    void setSchlagworte(const QString &Schlagworte);

    QString getLand() const;
    void setLand(const QString &Land);

    QString getNotizen() const;
    void setNotizen(const QString &Notizen);

    QString getSprache() const;
    void setSprache(const QString &Sprache);

    double getCurrentLat() const;
    double getCurrentLong() const;

    QString getKoordinaten() const;

    void setCurrentCoordinate(double lat, double longi);


private:
    CArtikel m_Artikel;
    CListenController *m_listen; //Kann man besser machen, wird nur gebraucht, um sqlite anzusteuern
    bool m_somethingHasChanged;
};

#endif // CARTIKELEDITOR_H
