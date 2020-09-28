#ifndef CAUSGABE_H
#define CAUSGABE_H

#include "cartikel.h"
#include <QMap>

#define AUSGABE_TABELLE			"Ausgabe"
#define AUSGABE_INDEX			"UniqueIndex"	//!< INTEGER,
#define AUSGABE_ZEITSCHRIFT		"Zeitschrift"	//!< TEXT,
#define AUSGABE_JAHR			"Jahr"			//!< INTEGER,
#define AUSGABE_AUSGABE			"Ausgabe"		//!< INTEGER,
#define AUSGABE_COVER			"Cover"			//!< BLOB,
#define AUSGABE_PREIS			"Preis"			//!< REAL,
#define AUSGABE_WAEHRUNG		"Waehrung"		//!< TEXT,
#define AUSGABE_SPRACHE         "Sprache"       //!< TEXT
#define AUSGABE_SEITENZAHL		"Seitenzahl"	//!< INTEGER,
#define AUSGABE_CHEFREDAKTEUR	"Chefredakteur"	//!< TEXT,
#define AUSGABE_NOTIZEN			"Notizen"		//!< TEXT,
#define AUSGABE_UNTERTITEL      "Untertitel"    //!< TEXT

class CAusgabe
{
public:
	CAusgabe();

	CAusgabe (const  CAusgabe&) = default;
	CAusgabe& operator=(const CAusgabe&) = default;
	CAusgabe ( CAusgabe&&) = default;
	CAusgabe& operator=( CAusgabe&&) = default;

	virtual ~CAusgabe() = default;

	bool setDBElement(QString columnName, QByteArray columEntry);

	int getAusgabe() const;
	void setAusgabe(int Ausgabe);

	int getJahr() const;
	void setJahr(int Jahr);

	QString getZeitschrift() const;
	void setZeitschrift(const QString &Zeitschrift);

	int getUniqueIndex() const;
	void setUniqueIndex(int uniqueIndex);

	QString getCover() const;
    QString getPureCover() const;
	void setCover(const QString &Cover);

	double getPreis() const;
	void setPreis(double Preis);

	QString getWaehrung() const;
	void setWaehrung(const QString &Waehrung);

	int getSeitenzahl() const;
	void setSeitenzahl(int Seitenzahl);

	QString getChefredakteur() const;
	void setChefredakteur(const QString &Chefredakteur);

	QString getNotizen() const;
	void setNotizen(const QString &Notizen);

    QString getSprache() const;
    void setSprache(const QString &Sprache);

    QString getUntertitel() const;
    void setUntertitel (const QString &untertitel);

    QString getAsSQLString(bool include_whereID) const;


private:
	void setText(QString key, QString text);

	QMap<QString,QByteArray> m_AusgabenMap;



};

#endif // CAUSGABE_H
