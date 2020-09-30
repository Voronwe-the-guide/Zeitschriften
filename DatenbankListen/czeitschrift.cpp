#include "czeitschrift.h"
#include <Helper/helper.h>
#include <Settings/csettings.h>

#include <QDir>

CZeitschrift::CZeitschrift():
    m_isSelected(false)
{
	m_ZeitschriftMap[ZEITSCHRIFT_INDEX].setNum(-1);
	m_ZeitschriftMap[ZEITSCHRIFT_ZEITSCHRIFT] = "";
	m_ZeitschriftMap[ZEITSCHRIFT_LOGO] = "";
    m_ZeitschriftMap[ZEITSCHRIFT_BESCHREIBUNG] ="";
    m_ZeitschriftMap[ZEITSCHRIFT_NOTIZEN]="";
    m_ZeitschriftMap[ZEITSCHRIFT_SPRACHE]="";



}
CZeitschrift::~CZeitschrift()
{
	m_ZeitschriftMap.clear();
	m_rubrikList.clear();
}


bool CZeitschrift::setDBElement(const QString& columnName, const QByteArray& columnEntry)
{

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
    QString logo = getPureLogo();
         if (!logo.isEmpty())
        {
            QDir DBPath = (CSettings::getConfiguration()->getCurrentDBPath());
            QFileInfo LogoInfo(DBPath,logo);
            logo = LogoInfo.absoluteFilePath();
            if (logo.contains("file:/"))
            {
              int position = logo.indexOf(("file:/"));
              logo = logo.remove(0,position+6);
            }
         //   qDebug()<<logo;
            logo = "file:///"+logo;
        }

	return logo;
}

QString CZeitschrift::getPureLogo() const
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
   // QFileInfo DBAdress(CSettings::getConfiguration()->getCurrentDB());
    QString logoPath = logo;
    if (!(logoPath.isEmpty()))
    {
        QDir DBPath = (CSettings::getConfiguration()->getCurrentDBPath());

        QFileInfo LogoInfo (logo);
        logoPath = DBPath.relativeFilePath(LogoInfo.absoluteFilePath());
    }
    setText(ZEITSCHRIFT_LOGO,logoPath);
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
   setText(ZEITSCHRIFT_BESCHREIBUNG,beschreibung);
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
    setText(ZEITSCHRIFT_NOTIZEN,notizen);

}

QString CZeitschrift::getSprache() const
{
    QString sprache;
    if (m_ZeitschriftMap.contains(ZEITSCHRIFT_SPRACHE))
    {
        sprache = m_ZeitschriftMap[ZEITSCHRIFT_SPRACHE];
    }
    return sprache;
}
void CZeitschrift::setSprache(const QString &sprache)
{
    setText(ZEITSCHRIFT_SPRACHE,sprache);
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
	m_rubrikList << rubrik;
 }

QList <QString> CZeitschrift::getRubrikList()
{
	return m_rubrikList;
}

void CZeitschrift::AddElementToSloganList(QString element)
{
	if (element.isEmpty())
	{
		return;
	}

	for (int i=0; i<m_sloganList.count(); i++)
	{
		if (m_sloganList.at(i) == element)
		{
			//Allready there
			return;
		}
	}
	m_sloganList << element;
}
QList <QString> CZeitschrift::getSloganList()
{
	return m_sloganList;
}

void CZeitschrift::AddElementToRedaktionList(QString element)
{
	if (element.isEmpty())
	{
		return;
	}

	for (int i=0; i<m_redaktionList.count(); i++)
	{
		if (m_redaktionList.at(i) == element)
		{
			//Allready there
			return;
		}
	}
	m_redaktionList << element;
}

QList <QString> CZeitschrift::getRedaktionList()
{
	return m_redaktionList;
}


QString CZeitschrift::getAsSQLString(bool include_whereID) const
{
    QString artikel = "SET ";

    Helper helper;

    artikel +=QString(" %1 = '%2'").arg(ZEITSCHRIFT_ZEITSCHRIFT).arg(helper.fixSpecialCharacters(getZeitschrift()));
    artikel +=QString(", %1 = '%2'").arg(ZEITSCHRIFT_LOGO).arg(helper.fixSpecialCharacters(getPureLogo()));
    artikel +=QString(", %1 = '%2'").arg(ZEITSCHRIFT_BESCHREIBUNG).arg(helper.fixSpecialCharacters(getBeschreibung()));
    artikel +=QString(", %1 = '%2'").arg(ZEITSCHRIFT_NOTIZEN).arg(helper.fixSpecialCharacters(getNotizen()));
    artikel +=QString(", %1 = '%2'").arg(ZEITSCHRIFT_SPRACHE).arg(helper.fixSpecialCharacters(getSprache()));

    if (include_whereID)
    {
       artikel += QString(" WHERE %1='%2'").arg(ZEITSCHRIFT_INDEX).arg(getUniqueIndex());
    }

    return artikel;
}

/*void CZeitschrift::setText(QString key, QString text)
{
    //text = fixSpecialCharacters(text);
    m_ZeitschriftMap[key]=text.toUtf8();
}
*/
