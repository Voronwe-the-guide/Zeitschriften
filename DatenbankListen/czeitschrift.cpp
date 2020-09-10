#include "czeitschrift.h"


CZeitschrift::CZeitschrift():
    m_isSelected(false)
{
	m_ZeitschriftMap[ZEITSCHRIFT_INDEX].setNum(-1);
	m_ZeitschriftMap[ZEITSCHRIFT_ZEITSCHRIFT] = "";
	m_ZeitschriftMap[ZEITSCHRIFT_LOGO] = "";

}

bool CZeitschrift::setDBElement(const QString& columnName, const QByteArray& columnEntry)
{
  //  columnName = columnName.toLower();


/*	if ((columnName == ZEITSCHRIFT_INDEX)
		||  (columnName == ZEITSCHRIFT_ZEITSCHRIFT)
		||  (columnName == ZEITSCHRIFT_LOGO)
		)
		*/
	if (m_ZeitschriftMap.contains(columnName))
	{
		m_ZeitschriftMap[columnName] = columnEntry;
		return true;
	}

    return false;

}

bool CZeitschrift::isSelected() const
{
	return m_isSelected;
}

void CZeitschrift::setIsSelected(bool isSelected)
{
	m_isSelected = isSelected;
}


QString CZeitschrift::getZeitschrift() const
{
	QString zeitschrift;
	if (m_ZeitschriftMap.contains(ZEITSCHRIFT_ZEITSCHRIFT))
	{
		zeitschrift = m_ZeitschriftMap[ZEITSCHRIFT_ZEITSCHRIFT];
	}
	return zeitschrift;
}
void CZeitschrift::setZeitschrift(const QString& zeitschrift)
{
   m_ZeitschriftMap[ZEITSCHRIFT_ZEITSCHRIFT] = zeitschrift.toUtf8();
}


QString CZeitschrift::getLogo() const
{
	QString logo;
	if (m_ZeitschriftMap.contains(ZEITSCHRIFT_LOGO))
	{
		logo = m_ZeitschriftMap[ZEITSCHRIFT_LOGO];
	}
	return logo;
}

void CZeitschrift::setLogo(const QString &logo)
{
   m_ZeitschriftMap[ZEITSCHRIFT_LOGO] = logo.toUtf8();
}

int CZeitschrift::getUniqueIndex() const
{
	int index =  -1;
	if (m_ZeitschriftMap.contains(ZEITSCHRIFT_INDEX))
	{
		index = m_ZeitschriftMap[ZEITSCHRIFT_INDEX].toInt();
	}
	return index;
}

void CZeitschrift::setUniqueIndex(int uniqueIndex)
{
	 m_ZeitschriftMap[ZEITSCHRIFT_INDEX].setNum(uniqueIndex);
}

