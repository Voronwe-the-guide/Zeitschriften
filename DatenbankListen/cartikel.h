#ifndef CARTIKEL_H
#define CARTIKEL_H

#include <QObject>
#include <QString>
#include <QGeoCoordinate>
#include <QDateTime>
#include <QMap>


#define ARTIKEL_TABELLE			"Inhalte"
#define ARTIKEL_INDEX			"UniqueIndex"		//!< INTEGER,
#define ARTIKEL_ZEITSCHRIFT		"Zeitschrift"		//!< TEXT DEFAULT 'GEO',
#define ARTIKEL_AUSGABE			"Ausgabe"			//!< INTEGER,
#define ARTIKEL_JAHR			"Jahr"				//!< INTEGER,
#define ARTIKEL_RUBRIK			"Rubrik"			//!< TEXT,
#define ARTIKEL_UEBERSCHRIFT	"Ueberschrift"		//!< TEXT DEFAULT (null),
#define ARTIKEL_ZUSAMMENFASSUNG	"Zusammenfassung"	//!< TEXT,
#define ARTIKEL_KURZTEXT		"Kurztext"			//!< TEXT,
#define ARTIKEL_SEITE			"Seite"				//!< INTEGER,
#define ARTIKEL_AUTOR			"Autor"				//!< TEXT,
#define ARTIKEL_FOTOS			"Fotos"				//!< TEXT,
#define ARTIKEL_SCHLAGWORTE		"Schlagworte"		//!< TEXT,
#define ARTIKEL_LAND			"Land"				//!< TEXT,
#define ARTIKEL_NOTIZEN			"Notizen"			//!< TEXT,
#define ARTIKEL_SPRACHE         "Sprache"           //!< TEXT
#define ARTIKEL_LONGITUDE		"Koord_Laenge"		//!< REAL,
#define ARTIKEL_LATITUDE		"Koord_Breite"		//!< REAL,
#define ARTIKEL_AENDERUNGSZEIT	"Aenderungszeit"	//!< TEXT,

class CArtikel
{

public:
	CArtikel();
    CArtikel (const  CArtikel&) = default;
    CArtikel& operator=(const CArtikel&) = default;
    CArtikel ( CArtikel&&) = default;
    CArtikel& operator=( CArtikel&&) = default;

	virtual ~CArtikel() = default;


	bool setDBElement(const QString& columnName, const QByteArray& columnEntry);
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

	QGeoCoordinate getKoordinate() const;
	QString getKoordinateAsString() const;
	void setKoordinate(const QGeoCoordinate &Koordinate);
    void setKoordinate(const QString& whichOne, const QString &partOfkoordinate);

	QDateTime getLastChange() const;
	QString getLastChangeAsString() const;
     void setLastChange(const QString &Koordinate);
    void setLastChange(const QDateTime &lastChange);

	int getDBIndex() const;
    void setDBIndex(int index);

	QString getArtikelAsSQLString(bool include_whereID) const;



private:

	void setText(QString key, QString text);


 /*   int m_DBIndex;
    QString m_Zeitschrift;		//!< Name der Zeitschrift
    int m_Jahr;					//!< Jahrgang der Zeitschrift
	int m_Ausgabe;				//!< Ausgabe der Zeitschrift, bezogen auf Jahrgang
	int m_Seite;				//!< Seitennummer
	QString m_Rubrik;
	QString m_Ueberschrift;
	QString m_Zusammenfassung;
	QString m_Kurztext;
	QString m_Autor;
	QString m_Fotos;
	QString m_Schlagworte;
	QString m_Land;
    QString m_Notizen;
	QGeoCoordinate m_Koordinate;
    QDateTime m_lastChange;
*/
	QMap<QString,QByteArray> m_artikelMap;

};

#endif // CARTIKEL_H
