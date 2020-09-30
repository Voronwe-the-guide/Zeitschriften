#ifndef CAUSGABEDISPLAYLIST_H
#define CAUSGABEDISPLAYLIST_H

#include <QAbstractListModel>
#include <QObject>
#include "causgabe.h"

class CAusgabeDisplayList  : public QAbstractListModel
{
	Q_OBJECT
public:
    CAusgabeDisplayList(QObject *parent = 0);

	virtual ~CAusgabeDisplayList();

	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

signals:
	void listEmpty();

public slots:

    void deleteAll();
	bool AddElement (CAusgabe &ausgabe);

protected:

	QHash<int, QByteArray> roleNames() const;

private:


	QList<CAusgabe> m_AusgabenList;

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
