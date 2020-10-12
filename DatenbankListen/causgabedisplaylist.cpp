#include <DatenbankListen/causgabedisplaylist.h>
#include <QDebug>
#include <QTime>
const int  CAusgabeDisplayList::Role_Jahr  = Qt::UserRole+1;
const int  CAusgabeDisplayList::Role_Ausgabe  = Qt::UserRole+2;
const int  CAusgabeDisplayList::Role_Zeitschrift = Qt::UserRole+3;
const int CAusgabeDisplayList::Role_COVER  = Qt::UserRole+4	;
const int CAusgabeDisplayList::Role_PREIS  = Qt::UserRole+5;
const int CAusgabeDisplayList::Role_WAEHRUNG  = Qt::UserRole+6;
const int CAusgabeDisplayList::Role_SPRACHE  = Qt::UserRole+7;
const int CAusgabeDisplayList::Role_SEITENZAHL  = Qt::UserRole+8;
const int CAusgabeDisplayList::Role_CHEFREDAKTEUR  = Qt::UserRole+9;
const int CAusgabeDisplayList::Role_NOTIZEN  = Qt::UserRole+10;
const int  CAusgabeDisplayList::Role_UNTERTITEL = Qt::UserRole+11;
const int CAusgabeDisplayList::Role_DBIndex = Qt::UserRole+12;


CAusgabeDisplayList::CAusgabeDisplayList(QObject *parent) :
    QAbstractListModel(parent)
{

}

CAusgabeDisplayList::~CAusgabeDisplayList()
{
	deleteAll();
}

int CAusgabeDisplayList::rowCount ( const QModelIndex & /*parent*/) const
{
	return m_AusgabenList.count();
}
int CAusgabeDisplayList::columnCount ( const QModelIndex & /*parent*/) const
{
	return 3;
}

QVariant CAusgabeDisplayList::data ( const QModelIndex & index, int role) const
{
	QVariant ret = QVariant::Invalid;
	 if(index.row() < m_AusgabenList.size())
	{
		CAusgabe temp = m_AusgabenList[index.row()];
		switch (role)
		{
			case Qt::DisplayRole:
			case Role_Jahr: return temp.getJahr();
			case Role_Ausgabe: return temp.getAusgabe();
			case Role_Zeitschrift: return temp.getZeitschrift();
            case Role_COVER: return temp.getCover()	;
            case Role_PREIS: return temp.getPreisAsString();
            case Role_WAEHRUNG: return temp.getWaehrung();
            case Role_SPRACHE: return temp.getSprache();
            case Role_SEITENZAHL: return temp.getSeitenzahl();
            case Role_CHEFREDAKTEUR: return temp.getChefredakteur();
            case Role_NOTIZEN: return temp.getNotizen();
        case  Role_UNTERTITEL: return temp.getUntertitel();
		case Role_DBIndex: return temp.getUniqueIndex();
		}
	}

	return ret;
}

/*!
 * from: https://stackoverflow.com/questions/15836253/c-populate-vector-from-sqlite3-callback-function
 * Answer by: https://stackoverflow.com/users/11654/cl
 */

void CAusgabeDisplayList::deleteAll()
{
	if (!(m_AusgabenList.isEmpty()))
	{
		beginRemoveRows(QModelIndex(),0,(rowCount()-1));//This is to keep the list in QML updated
		 m_AusgabenList.clear();
		 endRemoveRows();
	}
  //  m_zeitungen.clear();
	emit listEmpty();
}


bool CAusgabeDisplayList::AddElement(CAusgabe &ausgabe, int&listIndex)
{


    QTime startTime = QTime::currentTime();
    for (int i=0; i<m_AusgabenList.count(); i++)
	{
		if ((ausgabe.getZeitschrift() == m_AusgabenList.at(i).getZeitschrift())
				&& (ausgabe.getJahr() == m_AusgabenList.at(i).getJahr())
				&& (ausgabe.getAusgabe() == m_AusgabenList.at(i).getAusgabe()))
		{
			//Allready there
			listIndex = i;
			return false;
		}
	}
    QTime forTime = QTime::currentTime();
    beginInsertRows(QModelIndex(),rowCount(),rowCount());//This is to keep the list in QML updated
	m_AusgabenList << ausgabe;
	endInsertRows();
    QTime endTime = QTime::currentTime();
  //  qDebug()<<"Add Element "<< startTime.msecsTo(forTime)<<" - "<<forTime.msecsTo(endTime);
	listIndex = m_AusgabenList.count()-1;
	return true;

}

CAusgabe  CAusgabeDisplayList::getElement (int listIndex)
{
	CAusgabe ausgabe;
	if ((listIndex>=0 ) && (listIndex<m_AusgabenList.count()))
	{
		ausgabe = m_AusgabenList.at(listIndex);
	}
	return ausgabe;
}

int CAusgabeDisplayList::getDBIndex(int listIndex)
{
	CAusgabe ausgabe = getElement(listIndex);
	return ausgabe.getUniqueIndex();
}
void  CAusgabeDisplayList::UpdateElement(const CAusgabe& element, int listIndex)
{
	if ((listIndex>=0) && (listIndex<m_AusgabenList.count()))
	{
		m_AusgabenList.replace(listIndex,element);
		const QModelIndex idx = index(listIndex);
		emit dataChanged(idx,idx);

	}
}

int CAusgabeDisplayList::getIndexInList(const CAusgabe& ausgabe)
{
    for (int i=0; i<m_AusgabenList.count(); i++)
    {
        if ((m_AusgabenList.at(i).getZeitschrift() == ausgabe.getZeitschrift())
            && (m_AusgabenList.at(i).getJahr() == ausgabe.getJahr())
            && (m_AusgabenList.at(i).getAusgabe() == ausgabe.getAusgabe()))
        {
            return i;
        }
    }

    return -1;

}

QHash<int, QByteArray> CAusgabeDisplayList::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[Role_Jahr] = "jahr";
	roles[Role_Ausgabe] = "ausgabe";
	roles[Role_Zeitschrift] = "zeitschrift";
    roles[Role_COVER] = "cover"	;
    roles[Role_PREIS] = "preis";
    roles[Role_WAEHRUNG] = "waehrung";
    roles[Role_SPRACHE] = "sprache";
    roles[Role_SEITENZAHL] = "seitenzahl";
    roles[Role_CHEFREDAKTEUR] = "chefredakteur";
    roles[Role_NOTIZEN] = "notizen";
    roles[Role_UNTERTITEL]="untertitel";
	roles[Role_DBIndex]="dbIndex";
    return roles;
}
