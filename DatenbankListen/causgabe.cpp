#include "causgabe.h"

CAusgabe::CAusgabe():
	m_Ausgabe(0),
	m_Jahr(0)

{

}

bool CAusgabe::setDBElement(QString columnName, QString columnEntry)
{
	columnName = columnName.toLower();

	if (columnName == "ausgabe"){ setAusgabe(columnEntry.toInt()); return true;}
	else if (columnName == "jahr") { setJahr(columnEntry.toInt()); return true;}
    else if (columnName == "zeitschrift"){setZeitschrift(columnEntry); return true;}

	return false;
}
int CAusgabe::Ausgabe() const
{
	return m_Ausgabe;
}

void CAusgabe::setAusgabe(int Ausgabe)
{
	m_Ausgabe = Ausgabe;
}

int CAusgabe::Jahr() const
{
	return m_Jahr;
}

void CAusgabe::setJahr(int Jahr)
{
	m_Jahr = Jahr;
}

QString CAusgabe::Zeitschrift() const
{
	return m_Zeitschrift;
}

void CAusgabe::setZeitschrift(const QString &Zeitschrift)
{
	m_Zeitschrift = Zeitschrift;
}
