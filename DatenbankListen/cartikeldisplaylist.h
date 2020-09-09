#ifndef CARTIKELDISPLAYLIST_H
#define CARTIKELDISPLAYLIST_H

#include <QAbstractListModel>
#include <QObject>
#include "cartikel.h"


class CArtikelDisplayList : public QAbstractListModel
{
	Q_OBJECT
public:
    CArtikelDisplayList(QObject *parent = 0);

	virtual ~CArtikelDisplayList();

	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

    QString searchElement() const;
    void setSearchElement(const QString &searchElement);

signals:
	void listEmpty();
    void elementAdded(int index);


public slots:
	void deleteAll();
	void AddElement(CArtikel &artikel);

    CArtikel getArtikel(int index);
    QString getZeitschrift(int index);
    int getJahr(int index);				//!< Jahrgang der Zeitschrift
    int getAusgabe(int index);				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
    int getSeite(int index);				//!< Seitennummer
    QString getRubrik(int index);
    QString getUeberschrift(int index);
    QString getZusammenfassung(int index);
    QString getKurztext(int index);
    QString getAutor(int index);
    QString getFotos(int index);
    QString getSchlagworte(int index);
    QString getLand(int index);
    int getDBIndex(int index);
    QString getNotizen(int index);
    double getLatitude(int index);
    double getLongitude(int index);



protected:

	QHash<int, QByteArray> roleNames() const;

private:

    QString HighlightSearchElement(QString parsedString) const;
	QList<CArtikel> m_ArtikelList;
    QString m_searchElement;

    QString m_fontColor_normal;
    QString m_fontColor_highlight;

	static const int  Role_Zeitschrift;
	static const int  Role_Jahr;					//!< Jahrgang der Zeitschrift
	static const int  Role_Ausgabe;				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
	static const int  Role_Seite;				//!< Seitennummer
	static const int  Role_Rubrik;
	static const int  Role_Ueberschrift;
	static const int  Role_Zusammenfassung;
	static const int  Role_Kurztext;
	static const int  Role_Autor;
	static const int  Role_Fotos;
	static const int  Role_Schlagworte;
	static const int  Role_Land;
	static const int  Role_Koordinate;
    static const int  Role_Index;
    static const int  Role_Notizen;
    static const int  Role_Latitude;
    static const int  Role_Longitude;

};




#endif // CARTIKELDISPLAYLIST_H
