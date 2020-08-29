#include "cjahrdisplaylist.h"

const int  CJahrDisplayList::Role_Jahr  = Qt::UserRole+1;

CJahrDisplayList::CJahrDisplayList(QObject *parent) :
    QAbstractListModel(parent)
{

}

CJahrDisplayList::~CJahrDisplayList()
{

}

int CJahrDisplayList::rowCount ( const QModelIndex & /*parent*/) const
{
	return m_JahrList.count();
}
int CJahrDisplayList::columnCount ( const QModelIndex & /*parent*/) const
{
	return 1;
}

QVariant CJahrDisplayList::data ( const QModelIndex & index, int role) const
{
	QVariant ret = QVariant::Invalid;
	 if(index.row() < m_JahrList.size())
	{
		CJahr temp = m_JahrList[index.row()];
		switch (role)
		{
			case Qt::DisplayRole:
			case Role_Jahr: return temp.Jahr();					//!< Jahrgang der Zeitschrift
		}
	}

	return ret;
}


void CJahrDisplayList::deleteAll()
{
	if (!(m_JahrList.isEmpty()))
	{
		beginRemoveRows(QModelIndex(),0,(rowCount()-1));//This is to keep the list in QML updated
		 m_JahrList.clear();
		 endRemoveRows();
	}
    emit listEmpty();
}


void CJahrDisplayList::AddElement(CJahr &jahr)
{
	for (int i=0; i<m_JahrList.count(); i++)
	{
		if (jahr.Jahr() == m_JahrList.at(i).Jahr())
		{
			//Allready there
			return;
		}
	}
	beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
	m_JahrList << jahr;
	endInsertRows();

}





QHash<int, QByteArray> CJahrDisplayList::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[Role_Jahr] = "jahr";					//!< Jahrgang der Zeitschrift

	return roles;
}
