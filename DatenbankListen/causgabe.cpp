#include "causgabe.h"

CAusgabe::CAusgabe()


{
	m_AusgabenMap[AUSGABE_INDEX].setNum(-1);
	m_AusgabenMap[AUSGABE_ZEITSCHRIFT] ="";
	m_AusgabenMap[AUSGABE_JAHR].setNum(-1);
	m_AusgabenMap[AUSGABE_AUSGABE].setNum(-1);
	m_AusgabenMap[AUSGABE_COVER] ="";
	m_AusgabenMap[AUSGABE_PREIS].setNum(-1);
	m_AusgabenMap[AUSGABE_WAEHRUNG] ="";
	m_AusgabenMap[AUSGABE_SEITENZAHL].setNum(-1);
	m_AusgabenMap[AUSGABE_CHEFREDAKTEUR]="";
	m_AusgabenMap[AUSGABE_NOTIZEN]="";

}

bool CAusgabe::setDBElement(QString columnName, QByteArray columnEntry)
{

/*	if ((columnName == AUSGABE_INDEX)
		||  (columnName == AUSGABE_ZEITSCHRIFT)
		||  (columnName == AUSGABE_JAHR)
		||  (columnName == AUSGABE_AUSGABE)
		||  (columnName == AUSGABE_COVER)
		||  (columnName == AUSGABE_PREIS)
		||  (columnName == AUSGABE_WAEHRUNG)
		||  (columnName == AUSGABE_SEITENZAHL)
		||  (columnName == AUSGABE_CHEFREDAKTEUR)
		||  (columnName == AUSGABE_NOTIZEN)
		)
		*/
	if (m_AusgabenMap.contains(columnName))
	{
		m_AusgabenMap[columnName] = columnEntry;
		return true;
	}

/*	if (columnName == "ausgabe"){ setAusgabe(columnEntry.toInt()); return true;}
	else if (columnName == "jahr") { setJahr(columnEntry.toInt()); return true;}
    else if (columnName == "zeitschrift"){setZeitschrift(columnEntry); return true;}
*/


	return false;
}
int CAusgabe::getAusgabe() const
{
	int result = -1;
	if (m_AusgabenMap.contains(AUSGABE_AUSGABE))
	{
		result = m_AusgabenMap[AUSGABE_AUSGABE].toInt();
	}
	return result;
}

void CAusgabe::setAusgabe(int Ausgabe)
{
	m_AusgabenMap[AUSGABE_AUSGABE].setNum(Ausgabe);
}

int CAusgabe::getJahr() const
{
	int result = -1;
	if (m_AusgabenMap.contains(AUSGABE_JAHR))
	{
		result = m_AusgabenMap[AUSGABE_JAHR].toInt();
	}
	return result;
}

void CAusgabe::setJahr(int Jahr)
{
	m_AusgabenMap[AUSGABE_JAHR].setNum(Jahr);

}

QString CAusgabe::getZeitschrift() const
{
	QString result;
	if (m_AusgabenMap.contains(AUSGABE_ZEITSCHRIFT))
	{
		result = m_AusgabenMap[AUSGABE_ZEITSCHRIFT];
	}
	return result;
}

void CAusgabe::setZeitschrift(const QString &Zeitschrift)
{
	  m_AusgabenMap[AUSGABE_ZEITSCHRIFT] = Zeitschrift.toUtf8();
}

int CAusgabe::getUniqueIndex() const
{
	int result = -1;
	if (m_AusgabenMap.contains(AUSGABE_INDEX))
	{
		result = m_AusgabenMap[AUSGABE_INDEX].toInt();
	}
	return result;
}

void CAusgabe::setUniqueIndex(int uniqueIndex)
{
	m_AusgabenMap[AUSGABE_INDEX].setNum(uniqueIndex);

}

QString CAusgabe::getCover() const
{
	QString result;
	if (m_AusgabenMap.contains(AUSGABE_COVER))
	{
		result = m_AusgabenMap[AUSGABE_COVER];
	}
	return result;
}

void CAusgabe::setCover(const QString &Cover)
{
	m_AusgabenMap[AUSGABE_COVER] = Cover.toUtf8();
}

double CAusgabe::getPreis() const
{
	double result = -1;
	if (m_AusgabenMap.contains(AUSGABE_PREIS))
	{
		result = m_AusgabenMap[AUSGABE_PREIS].toDouble();
	}
	return result;
}

void CAusgabe::setPreis(double Preis)
{
	m_AusgabenMap[AUSGABE_INDEX].setNum(Preis);
}

QString CAusgabe::getWaehrung() const
{
	QString result;
	if (m_AusgabenMap.contains(AUSGABE_WAEHRUNG))
	{
		result = m_AusgabenMap[AUSGABE_WAEHRUNG];
	}
	return result;
}

void CAusgabe::setWaehrung(const QString &Waehrung)
{
	m_AusgabenMap[AUSGABE_WAEHRUNG] = Waehrung.toUtf8();

}

int CAusgabe::getSeitenzahl() const
{
	int result = -1;
	if (m_AusgabenMap.contains(AUSGABE_SEITENZAHL))
	{
		result = m_AusgabenMap[AUSGABE_SEITENZAHL].toInt();
	}
	return result;
}

void CAusgabe::setSeitenzahl(int Seitenzahl)
{
	m_AusgabenMap[AUSGABE_SEITENZAHL].setNum(Seitenzahl);

}

QString CAusgabe::getChefredakteur() const
{
	QString result;
	if (m_AusgabenMap.contains(AUSGABE_CHEFREDAKTEUR))
	{
		result = m_AusgabenMap[AUSGABE_CHEFREDAKTEUR];
	}
	return result;
}

void CAusgabe::setChefredakteur(const QString &Chefredakteur)
{
	m_AusgabenMap[AUSGABE_CHEFREDAKTEUR] = Chefredakteur.toUtf8();

}

QString CAusgabe::getNotizen() const
{
	QString result;
	if (m_AusgabenMap.contains(AUSGABE_NOTIZEN))
	{
		result = m_AusgabenMap[AUSGABE_NOTIZEN];
	}
	return result;
}

void CAusgabe::setNotizen(const QString &Notizen)
{
	m_AusgabenMap[AUSGABE_NOTIZEN] = Notizen.toUtf8();

}
