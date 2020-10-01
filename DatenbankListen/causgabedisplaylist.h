#ifndef CAUSGABEDISPLAYLIST_H
#define CAUSGABEDISPLAYLIST_H

#include <QAbstractListModel>
#include <QObject>
#include "causgabe.h"


class CAusgabeDisplayList  : public QAbstractListModel
{
	Q_OBJECT

public:
	struct searchStruct
	{
		QString magazin;
		int jahr = 0;
		int ausgabe = 0;
		QString getAsString() {return QString("%1_%2_%3").arg(magazin).arg(jahr).arg(ausgabe);}
		void setDBElement(QString columnName,QByteArray columnText)
		{
			if (columnName == AUSGABE_JAHR)
			{
				jahr = columnText.toInt();
			}
			if (columnName == AUSGABE_AUSGABE)
			{
				 ausgabe = columnText.toInt();
			}
			if (columnName == AUSGABE_ZEITSCHRIFT)
			{
				 magazin = columnText;
			}
		}
	};

  /*  struct jahrElement
    {
        QMap<int,int> m_ausgaben;
           //  jahre, ausgaben
    };
*/


    CAusgabeDisplayList(QObject *parent = 0);

	virtual ~CAusgabeDisplayList();

	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

signals:
	void listEmpty();

public slots:

    void deleteAll();
	bool AddElement (CAusgabe &element,int &index);
//	CAusgabe getElement (const QString& AuZeitschrift,int &listIndex);
	CAusgabe getElement (int listIndex);
	void UpdateElement(const CAusgabe& element, int listIndex);

protected:

	QHash<int, QByteArray> roleNames() const;

private:


	QList<CAusgabe> m_AusgabenList;
  //  QMap<QString,jahrElement> m_zeitungen;
     //     Zeitung, Jahre

	static const int Role_DBIndex;
	static const int Role_Jahr;
	static const int Role_Ausgabe;
	static const int Role_Zeitschrift;
    static const int Role_COVER	;
    static const int Role_PREIS;
    static const int Role_WAEHRUNG;
    static const int Role_SPRACHE;
    static const int Role_SEITENZAHL;
    static const int Role_CHEFREDAKTEUR;
    static const int Role_NOTIZEN;
    static const int Role_UNTERTITEL;
};

#endif // CAUSGABEDISPLAYLIST_H
