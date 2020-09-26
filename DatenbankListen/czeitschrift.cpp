#include "czeitschrift.h"
#include <Helper/helper.h>

CZeitschrift::CZeitschrift():
    m_isSelected(false)
{
	m_ZeitschriftMap[ZEITSCHRIFT_INDEX].setNum(-1);
	m_ZeitschriftMap[ZEITSCHRIFT_ZEITSCHRIFT] = "";
	m_ZeitschriftMap[ZEITSCHRIFT_LOGO] = "";
    m_ZeitschriftMap[ZEITSCHRIFT_BESCHREIBUNG] ="";
    m_ZeitschriftMap[ZEITSCHRIFT_NOTIZEN]="";



}
CZeitschrift::~CZeitschrift()
{
	m_ZeitschriftMap.clear();
	m_rubrikList.clear();
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
   setText(ZEITSCHRIFT_ZEITSCHRIFT,zeitschrift);
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


QString CZeitschrift::getBeschreibung() const
{
    QString beschreibung;
    if (m_ZeitschriftMap.contains(ZEITSCHRIFT_BESCHREIBUNG))
    {
        beschreibung = m_ZeitschriftMap[ZEITSCHRIFT_BESCHREIBUNG];
    }
    return beschreibung;
}
void CZeitschrift::setBeschreibung(const QString &beschreibung)
{
    m_ZeitschriftMap[ZEITSCHRIFT_BESCHREIBUNG] = beschreibung.toUtf8();
}

QString CZeitschrift::getNotizen() const
{
    QString notizen;
    if (m_ZeitschriftMap.contains(ZEITSCHRIFT_NOTIZEN))
    {
        notizen = m_ZeitschriftMap[ZEITSCHRIFT_NOTIZEN];
    }
    return notizen;
}
void CZeitschrift::setNotizen(const QString &notizen)
{
    m_ZeitschriftMap[ZEITSCHRIFT_NOTIZEN] = notizen.toUtf8();

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

void CZeitschrift::setText(QString key, QString text)
{
	//text = fixSpecialCharacters(text);
	m_ZeitschriftMap[key]=text.toUtf8();
}

void CZeitschrift::AddElementToRubrikList(QString rubrik)
{
	if (rubrik.isEmpty())
	{
		return;
	}

	for (int i=0; i<m_rubrikList.count(); i++)
	{
		if (m_rubrikList.at(i) == rubrik)
		{
			//Allready there
			return;
		}
	}
 //   beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
	m_rubrikList << rubrik;
 //   endInsertRows();
}
QList <QString> CZeitschrift::getRubrikList()
{
	return m_rubrikList;
}


QString CZeitschrift::getAsSQLString(bool include_whereID) const
{
    QString artikel = "SET ";

    Helper helper;

    artikel +=QString(" %1 = '%2'").arg(ZEITSCHRIFT_ZEITSCHRIFT).arg(helper.fixSpecialCharacters(getZeitschrift()));
    artikel +=QString(", %1 = '%2'").arg(ZEITSCHRIFT_LOGO).arg(helper.fixSpecialCharacters(getLogo()));
    artikel +=QString(", %1 = '%2'").arg(ZEITSCHRIFT_BESCHREIBUNG).arg(helper.fixSpecialCharacters(getBeschreibung()));
    artikel +=QString(", %1 = '%2'").arg(ZEITSCHRIFT_NOTIZEN).arg(helper.fixSpecialCharacters(getNotizen()));

    if (include_whereID)
    {
       artikel += QString(" WHERE %1='%2'").arg(ZEITSCHRIFT_INDEX).arg(getUniqueIndex());
    }

    return artikel;
}
