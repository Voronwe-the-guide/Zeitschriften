#ifndef CAUSGABE_H
#define CAUSGABE_H

#include "cartikel.h"
#include <QList>
class CAusgabe
{
public:
	CAusgabe();

	CAusgabe (const  CAusgabe&) = default;
	CAusgabe& operator=(const CAusgabe&) = default;
	CAusgabe ( CAusgabe&&) = default;
	CAusgabe& operator=( CAusgabe&&) = default;

	virtual ~CAusgabe() = default;

	bool setDBElement(QString columnName, QString columEntry);

	int Ausgabe() const;
	void setAusgabe(int Ausgabe);

	int Jahr() const;
	void setJahr(int Jahr);

	QString Zeitschrift() const;
	void setZeitschrift(const QString &Zeitschrift);

private:
	int m_Ausgabe;
	int m_Jahr;
	QString m_Zeitschrift;


};

#endif // CAUSGABE_H
