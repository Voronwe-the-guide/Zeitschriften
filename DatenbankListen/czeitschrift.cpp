#include "czeitschrift.h"

CZeitschrift::CZeitschrift():
    m_isSelected(false)
{

}

bool CZeitschrift::setDBElement(QString columnName, QString columnEntry)
{
    columnName = columnName.toLower();

    if (columnName == "zeitschrift") { setZeitschrift(columnEntry); return true;}

    return false;

}

QString CZeitschrift::Zeitschrift() const
{
    return m_Zeitschrift;
}
void CZeitschrift::setZeitschrift(QString zeitschrift)
{
    m_Zeitschrift = zeitschrift;
}

bool CZeitschrift::isSelected() const
{
    return m_isSelected;
}

void CZeitschrift::setIsSelected(bool isSelected)
{
    m_isSelected = isSelected;
}

