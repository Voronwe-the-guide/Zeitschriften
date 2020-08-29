#ifndef CARTIKEL_H
#define CARTIKEL_H

#include <QString>
#include <QGeoCoordinate>
#include <QDateTime>

class CArtikel
{
public:
	CArtikel();
	CArtikel (const  CArtikel&) = default;
	CArtikel& operator=(const CArtikel&) = default;
	CArtikel ( CArtikel&&) = default;
	CArtikel& operator=( CArtikel&&) = default;

	virtual ~CArtikel() = default;

	bool setDBElement(QString columnName, QString columEntry);
	QString Zeitschrift() const;
	void setZeitschrift(const QString &Zeitschrift);

	int Jahr() const;
	void setJahr(int Jahr);

	int Ausgabe() const;
	void setAusgabe(int Ausgabe);

	int Seite() const;
	void setSeite(int Seite);

	QString Rubrik() const;
	void setRubrik(const QString &Rubrik);

	QString Ueberschrift() const;
	void setUeberschrift(const QString &Ueberschrift);

	QString Zusammenfassung() const;
	void setZusammenfassung(const QString &Zusammenfassung);

	QString Kurztext() const;
	void setKurztext(const QString &Kurztext);

	QString Autor() const;
	void setAutor(const QString &Autor);

	QString Fotos() const;
	void setFotos(const QString &Fotos);

	QString Schlagworte() const;
	void setSchlagworte(const QString &Schlagworte);

	QString Land() const;
	void setLand(const QString &Land);

	QGeoCoordinate Koordinate() const;
    QString KoordinateAsString() const;
	void setKoordinate(const QGeoCoordinate &Koordinate);
    void setKoordinate(const QString &Koordinate);

    QDateTime lastChange() const;
    QString lastChangeAsString() const;
     void setLastChange(const QString &Koordinate);
    void setLastChange(const QDateTime &lastChange);

private:

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
	QGeoCoordinate m_Koordinate;
    QDateTime m_lastChange;


};

#endif // CARTIKEL_H
