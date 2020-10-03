#include <DatenbankListen/czeitschriftdisplaylist.h>

const int  CZeitschriftDisplayList::Role_Zeitschrift  = Qt::UserRole+1;
const int CZeitschriftDisplayList::Role_Selection = Qt::UserRole+2;
const int CZeitschriftDisplayList::Role_Logo = Qt::UserRole+3;
const int CZeitschriftDisplayList::Role_DBIndex = Qt::UserRole+4;
const int  CZeitschriftDisplayList::Role_Beschreibung= Qt::UserRole+5;
const int  CZeitschriftDisplayList::Role_Notizen= Qt::UserRole+6;
 const int CZeitschriftDisplayList:: Role_Sprache= Qt::UserRole+7;


CZeitschriftDisplayList::CZeitschriftDisplayList(QObject *parent) :
    QAbstractListModel(parent)
{

}


CZeitschriftDisplayList::~CZeitschriftDisplayList()
{

}

int CZeitschriftDisplayList::rowCount ( const QModelIndex & /*parent*/) const
{
    return m_ZeitschriftenList.count();
}
int CZeitschriftDisplayList::columnCount ( const QModelIndex & /*parent*/) const
{
    return 1;
}

QVariant CZeitschriftDisplayList::data ( const QModelIndex & index, int role) const
{
    QVariant ret = QVariant::Invalid;
     if(index.row() <  m_ZeitschriftenList.size())
    {
        CZeitschrift temp =  m_ZeitschriftenList[index.row()];
        switch (role)
        {
            case Qt::DisplayRole:
			case Role_Zeitschrift: return temp.getZeitschrift();					//!< Jahrgang der Zeitschrift
            case Role_Selection: return temp.isSelected();
            case Role_Logo: return temp.getLogo();
            case Role_DBIndex: return temp.getUniqueIndex();
            case Role_Beschreibung: return temp.getBeschreibung();
            case Role_Notizen: return temp.getNotizen();
            case Role_Sprache: return temp.getSprache();

        }
    }

    return ret;
}


void CZeitschriftDisplayList::deleteAll()
{
    if (!(m_ZeitschriftenList.isEmpty()))
    {
        beginRemoveRows(QModelIndex(),0,(rowCount()-1));//This is to keep the list in QML updated
         m_ZeitschriftenList.clear();
         endRemoveRows();
    }
        emit listEmpty();
}


bool CZeitschriftDisplayList::AddElement(CZeitschrift &zeitschrift, int&listIndex)
{
    for (int i=0; i<m_ZeitschriftenList.count(); i++)
    {
		if (zeitschrift.getZeitschrift() == m_ZeitschriftenList.at(i).getZeitschrift())
        {
			listIndex = i;
            return false;
        }
    }
    beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
    m_ZeitschriftenList << zeitschrift;
    endInsertRows();
	listIndex = m_ZeitschriftenList.count()-1;

    return true;

}

CZeitschrift CZeitschriftDisplayList::getZeitschrift (const QString& Zeitschrift, int &listIndex)
{
	CZeitschrift zeitschrift;
	listIndex = -1;
	for (int i=0; i<m_ZeitschriftenList.count(); ++i)
	{
		if (m_ZeitschriftenList.at(i).getZeitschrift() == Zeitschrift)
		{
			zeitschrift = m_ZeitschriftenList.at(i);
			listIndex = i;
			break;
		}
	}
	return zeitschrift;
}


CZeitschrift CZeitschriftDisplayList::getZeitschrift (int listIndex)
{
	CZeitschrift zeitschrift;
	if ((listIndex>=0 ) && (listIndex<m_ZeitschriftenList.count()))
	{
		zeitschrift = m_ZeitschriftenList.at(listIndex);
	}
    return zeitschrift;
}


void CZeitschriftDisplayList::AddRubrikToZeitschrift(const QString& zeitschrift, const QString& rubrik)
{
	int theIndex=-1;
	CZeitschrift Zeitung = getZeitschrift(zeitschrift,theIndex);
	if (theIndex>=0)
	{
		Zeitung.AddElementToRubrikList(rubrik);
		m_ZeitschriftenList.replace(theIndex,Zeitung);
		const QModelIndex idx = index(theIndex);
		emit dataChanged(idx,idx);


	}

}

void CZeitschriftDisplayList::UpdateZeitschrift(const CZeitschrift& zeitschrift, int listIndex)
{
	if ((listIndex>=0) && (listIndex<m_ZeitschriftenList.count()))
	{
		m_ZeitschriftenList.replace(listIndex,zeitschrift);
		const QModelIndex idx = index(listIndex);
		emit dataChanged(idx,idx);

	}
}


void CZeitschriftDisplayList::ToggleSelection(int theIndex)
{
    if ((theIndex>=0) && (theIndex<rowCount()))
    {
        CZeitschrift temp = m_ZeitschriftenList.at(theIndex);
        temp.setIsSelected(!temp.isSelected());
        m_ZeitschriftenList.replace(theIndex,temp);
        const QModelIndex idx = index(theIndex);
        emit dataChanged(idx,idx);
    }
}

void CZeitschriftDisplayList::deselectAll()
{
    for (int i=0; i<m_ZeitschriftenList.count();++i)
    {
        deselect(i);
    }
}

void CZeitschriftDisplayList::deselect(int theIndex)
{
    if ((theIndex>=0) && (theIndex<rowCount()))
    {
        CZeitschrift temp = m_ZeitschriftenList.at(theIndex);
        temp.setIsSelected(false);
        m_ZeitschriftenList.replace(theIndex,temp);
        const QModelIndex idx = index(theIndex);
        emit dataChanged(idx,idx);
    }
}


QStringList CZeitschriftDisplayList::getSelectedElements()
{
    QStringList elements;
    for (int i=0; i<rowCount(); ++i)
    {
        if (m_ZeitschriftenList.at(i).isSelected())
        {
			elements.append(m_ZeitschriftenList.at(i).getZeitschrift());
        }
    }
    return elements;
}



QHash<int, QByteArray> CZeitschriftDisplayList::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Role_Zeitschrift] = "zeitschrift";//!< Jahrgang der Zeitschrift
    roles[Role_Selection] = "selected";
    roles[Role_Logo] = "logo";
    roles[Role_DBIndex]= "dbIndex";
    roles[Role_Beschreibung] ="beschreibung";
    roles[Role_Notizen] = "notizen";
    roles[Role_Sprache] = "sprache";

    return roles;
}
