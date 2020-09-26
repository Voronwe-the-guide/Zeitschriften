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

    void entryIsNotValid(); //Will be send back before sendig data to SQL

public slots:
    bool saveChangesInDB();

    void saveUpdate();
    void storeNewArtikel();

    bool isNameValid() const;

    QString getName() const;
    void setName(const QString &Zeitschrift);

    QString getLogoAdress() const;
    void setLogoAdress(const QString &LogoAdress);

    QString getBeschreibung() const;
    void setBeschreibung(const QString &beschreibung);

    QString getNotizen() const;
    void setNotizen(const QString &notizen);


    void setNewZeitschrift();

    void setZeitschriftForUpdate(int dbIndex);

    void setZeitschriftForUpdate(CZeitschrift zeitschriftl);


private:
    CZeitschrift m_zeitschrift;
    CListenController *m_listen;
    bool m_somethingHasChanged;


};

#endif // CZEITSCHRIFTEDITOR_H
