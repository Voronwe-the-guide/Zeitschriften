#include "crubriklistdisplay.h"

const int  CJahrDisplayList::Role_
r  = Qt::UserRole+1;

CSelectionListDisplay::CSelectionListDisplay(QObject *parent) :
	QAbstractListModel(parent)
{

}

CSelectionListDisplay::~CSelectionListDisplay()
{

}

int CSelectionListDisplay::rowCount ( const QModelIndex & /*parent*/) const
{
	return m_ElementList.count();
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
		QString temp = m_ElementList[index.row()];
		switch (role)
		{
			case Qt::DisplayRole:
			case Role_Element: return temp();					//!< Jahrgang der Zeitschrift
		}
	}

	return ret;
}
