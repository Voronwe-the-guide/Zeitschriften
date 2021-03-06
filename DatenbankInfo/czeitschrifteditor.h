#ifndef CZEITSCHRIFTEDITOR_H
#define CZEITSCHRIFTEDITOR_H
#include <DatenbankListen/czeitschrift.h>
#include <DatenbankListen/clistencontroller.h>

class CZeitschriftEditor : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString zeitschriftName READ getName NOTIFY zeitschriftDisplayUpdated)
    Q_PROPERTY (QString logoAdress READ getLogoAdress NOTIFY logoDisplayUpdated)
  //  Q_PROPERTY (QString logoAdress READ getLogoAdress NOTIFY zeitschriftDisplayUpdated)
    Q_PROPERTY (QString beschreibung READ getBeschreibung NOTIFY zeitschriftDisplayUpdated)
    Q_PROPERTY (QString notiz READ getNotizen NOTIFY zeitschriftDisplayUpdated)
    Q_PROPERTY (QString sprache READ getSprache NOTIFY zeitschriftDisplayUpdated)

	Q_PROPERTY(bool zeitschriftValid READ isNameValid NOTIFY zeitschriftNameUpdated)

public:
    CZeitschriftEditor(CListenController *listen, QObject *parent = nullptr);


    bool getSomethingHasChanged() const;
    void setSomethingHasChanged(bool somethingHasChanged);

signals:
    void zeitschriftDisplayUpdated();
    void zeitschriftNameUpdated(QString zeitschrift);
    void logoUpdated(QString logo);
    void logoDisplayUpdated();
    void beschreibungUpdated(QString beschreibung);
    void notizenUpdated(QString Notizen);
    void spracheUpdated(QString Sprache);

    void entryIsNotValid(); //Will be send back before sendig data to SQL
    void entryAllreadyThere();

public slots:
    int saveChangesInDB(bool fromNew);

    void saveUpdate();
    void storeNew();

    bool isNameValid() const;

    QString getName() const;
    void setName(const QString &Zeitschrift);

    QString getLogoAdress() const;
    void setLogoAdress(const QString &LogoAdress);

    QString getBeschreibung() const;
    void setBeschreibung(const QString &beschreibung);

    QString getNotizen() const;
    void setNotizen(const QString &notizen);

    QString getSprache() const;
    void setSprache(const QString &sprache);


    void setNew();

    void setForUpdate(int dbIndex);

    void setForUpdate(CZeitschrift zeitschriftl);

    void getForUpdate(CZeitschrift zeitschrift);


private:
    CZeitschrift m_zeitschrift;
    CListenController *m_listen;
    bool m_somethingHasChanged;


};

#endif // CZEITSCHRIFTEDITOR_H
