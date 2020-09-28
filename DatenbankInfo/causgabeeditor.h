#ifndef CAUSGABEEDITOR_H
#define CAUSGABEEDITOR_H

#include <DatenbankListen/causgabe.h>
#include <DatenbankListen/clistencontroller.h>

class CAusgabeEditor : public QObject
{
public:


    Q_OBJECT
    Q_PROPERTY(int ausgabe READ getAusgabe NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(int  jahr READ getJahr NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(QString  zeitschrift READ getZeitschrift NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(QString   cover READ getCover NOTIFY coverDisplayUpdated)
    Q_PROPERTY(double   preis READ getPreis NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(QString   waehrung READ getWaehrung NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(QString   seitenzahl READ getSeitenzahl NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(QString  chefredakteur READ getChefredakteur NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(QString  notizen READ getNotizen NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(QString   sprache READ getSprache NOTIFY ausgabeDisplayUpdated)
    Q_PROPERTY(QString   untertitel READ getUntertitel NOTIFY ausgabeDisplayUpdated )


    CAusgabeEditor(CListenController *listen, QObject *parent = nullptr);

    bool getSomethingHasChanged() const;
    void setSomethingHasChanged(bool somethingHasChanged);


signals:
    void ausgabeDisplayUpdated();
    void entryIsNotValid(); //Will be send back before sendig data to SQL



    void ausgabeUpdated(int ausgabe);
    void jahrUpdated(int jahr);
    void zeitschriftUpdated(const QString &Zeitschrift);
    void coverUpdated(const QString &Cover);
    void coverDisplayUpdated();
    void preisUpdated(double Preis);
    void waehrungUpdated(const QString &Waehrung);
    void seitenzahlUpdated(int Seitenzahl);
    void chefredakteurUpdated(const QString &Chefredakteur);
    void notizenUpdated(const QString &Notizen);
    void spracheUpdated(const QString &Sprache);
    void untertitelUpdated (const QString &untertitel);


public slots:

    bool isAusgabeValid() const;
    bool isZeitschriftValid() const;
    bool isJahrValid() const;

    void setNew();

    void setForUpdate(int dbIndex);

    void setForUpdate(CAusgabe ausgabe);

    void getForUpdate(CAusgabe ausgabe);

    bool saveChangesInDB();
    void saveUpdate();
    void storeNew();


    int getAusgabe() const;
    void setAusgabe(int Ausgabe);

    int getJahr() const;
    void setJahr(int  input);

    QString getZeitschrift() const;
    void setZeitschrift(const QString & input);

    QString getCover() const;
    void setCover(const QString & input);

    double getPreis() const;
    void setPreis(double  input);

    QString getWaehrung() const;
    void setWaehrung(const QString & input);

    int getSeitenzahl() const;
    void setSeitenzahl(int  input);

    QString getChefredakteur() const;
    void setChefredakteur(const QString & input);

    QString getNotizen() const;
    void setNotizen(const QString & input);

    QString getSprache() const;
    void setSprache(const QString & input);

    QString getUntertitel() const;
    void setUntertitel (const QString & input);



private:

    CAusgabe m_ausgabe;
    CListenController *m_listen;
    bool m_somethingHasChanged;


};

#endif // CAUSGABEEDITOR_H
