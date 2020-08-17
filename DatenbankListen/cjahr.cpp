#include "cjahr.h"

CJahr::CJahr():
	m_Jahr(0)
{

}

int CJahr::Jahr() const
{
	return m_Jahr;
}

void CJahr::setJahr(int jahr)
{
	m_Jahr = jahr;
}

bool CJahr::setDBElement(QString columnName, QString columnEntry)
{
	columnName = columnName.toLower();

	if (columnName == "jahr") { setJahr(columnEntry.toInt()); return true;}

	return false;
}
