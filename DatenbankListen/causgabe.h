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
#define AUSGABE_SEITENZAHL		"Seitenzahl"	//!< INTEGER,
#define AUSGABE_CHEFREDAKTEUR	"Chefredakteur"	//!< TEXT,
#define AUSGABE_NOTIZEN			"Notizen"		//!< TEXT,

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

private:

	QMap<QString,QByteArray> m_AusgabenMap;

	/*int m_Ausgabe;
	int m_Jahr;
	QString m_Zeitschrift;

	int m_uniqueIndex;
	QString m_Cover; //"			//!< BLOB,
	double m_Preis; //"			//!< INTEGER,
	QString m_Waehrung; //"		//!< TEXT,
	int m_Seitenzahl;//"	//!< INTEGER,
	QString m_Chefredakteur; //"	//!< TEXT,
	QString m_Notizen; //"		//!< TEXT,
*/

};

#endif // CAUSGABE_H
