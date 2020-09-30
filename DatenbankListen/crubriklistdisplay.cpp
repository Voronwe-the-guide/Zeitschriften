#include "crubriklistdisplay.h"

const int  CSelectionListDisplay::Role_Element   = Qt::UserRole+1;

CSelectionListDisplay::CSelectionListDisplay(QObject *parent) :
	QAbstractListModel(parent)
{

}

CSelectionListDisplay::~CSelectionListDisplay()
{

}

int CSelectionListDisplay::rowCount ( const QModelIndex & /*parent*/) const
{
    return m_DisplayList.count();
}
int CSelectionListDisplay::columnCount ( const QModelIndex & /*parent*/) const
{
	return 1;
}

QVariant CSelectionListDisplay::data ( const QModelIndex & index, int role) const
{
	QVariant ret = QVariant::Invalid;
	 if(index.row() <m_ElementList.size())
	{
        QString temp = m_DisplayList[index.row()];
		switch (role)
		{
			case Qt::DisplayRole:
            case Role_Element: return temp;
		}
	}

	return ret;
}

void CSelectionListDisplay::deleteAll()
{
    if (!(m_DisplayList.isEmpty()))
    {
        beginRemoveRows(QModelIndex(),0,(rowCount()-1));//This is to keep the list in QML updated
         //m_ElementList.clear();
         m_DisplayList.clear();
         endRemoveRows();
    }

    if (!(m_ElementList.isEmpty()))
        m_ElementList.clear();
    emit listEmpty();
}


void CSelectionListDisplay::SetList(QList<QString> list)
{
    deleteAll();
     m_ElementList = list;
     for (int i=0; i<m_ElementList.count(); ++i)
     {
         SetElementToDisplayList(m_ElementList.at(i));
	 }
}

void CSelectionListDisplay::AddElement(QString element)
{
	if (element.isEmpty())
	{
		return;
	}
	for (int i=0; i<m_ElementList.count(); i++)
	{
		if (element  == m_ElementList.at(i))
		{
			//Allready there
			return;
		}
	}
	beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
	m_ElementList << element;
	endInsertRows();

	SetElementToDisplayList(element);

}

void CSelectionListDisplay::UpdateListDisplay(QString filter)
{
    filter = filter.toLower();
    if (!(m_DisplayList.isEmpty()))
    {
        beginRemoveRows(QModelIndex(),0,(rowCount()-1));//This is to keep the list in QML updated
         //m_ElementList.clear();
         m_DisplayList.clear();
         endRemoveRows();
    }
    for (int i=0; i<m_ElementList.count(); ++i)
    {
        if (m_ElementList.at(i).toLower().startsWith(filter))
        {
            SetElementToDisplayList(m_ElementList.at(i));
        }
    }
}

QString CSelectionListDisplay::getElementFromDisplay(int index)
{
    if ((index>=0) && index<m_DisplayList.count())
    {
        return m_DisplayList.at(index);
    }

    return "";
}

void CSelectionListDisplay::SetElementToDisplayList(const QString& element)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
    m_DisplayList << element;
    endInsertRows();

}

QHash<int, QByteArray> CSelectionListDisplay::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Role_Element] = "element";
    return roles;
}
