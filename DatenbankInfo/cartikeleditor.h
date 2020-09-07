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

public:
    explicit CArtikelEditor(CListenController *listen, QObject *parent = nullptr);

    bool getSomethingHasChanged() const;
    void setSomethingHasChanged(bool somethingHasChanged);


signals:
    void artikelDisplayUpdated();
    void artikelUpdated(CArtikel artikel);
    void zeitschriftUpdated(QString Zeitschrift);
    void jahrUpdated(int Jahr);
    void ausgabeUpdated(int Ausgabe);
    void seiteUpdated(int Seite);
    void rubrikUpdated(QString Rubrik);
    void ueberschriftUpdated(QString Ueberschrift);
    void zusammenfassungUpdated(QString Zusammenfassung);
    void kurztextUpdated(QString Kurztext);
    void autorUpdated(QString Autor);
    void fotosUpdated(QString Fotos);
    void schlagworteUpdated(QString Schlagworte);
    void landUpdated(QString Land);

public slots:

    void saveChangesInDB();
    void setNewArtikel();
    void saveAndNext();
    void setArtikelForUpdate(int dbIndex);
    void setArtikelForUpdate(CArtikel artikel);

    void saveUpdate();
    void storeNewArtikel();

    CArtikel getArtikel() const;

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

private:
    CArtikel m_Artikel;
    CListenController *m_listen; //Kann man besser machen, wird nur gebraucht, um sqlite anzusteuern
    bool m_somethingHasChanged;
};

#endif // CARTIKELEDITOR_H
