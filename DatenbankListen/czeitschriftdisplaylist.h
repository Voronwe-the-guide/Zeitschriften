#ifndef CZEITSCHRIFTDISPLAYLIST_H
#define CZEITSCHRIFTDISPLAYLIST_H

#include <QAbstractListModel>
#include <QObject>
#include <DatenbankListen/czeitschrift.h>

class CZeitschriftDisplayList : public QAbstractListModel
{
    Q_OBJECT
public:
    CZeitschriftDisplayList(QObject *parent = nullptr);

    virtual ~CZeitschriftDisplayList();

    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

signals:
    void listEmpty();

public slots:
    void deleteAll();
    void AddElement(CZeitschrift &zeitschrift);
    void ToggleSelection(int index);

    QStringList getSelectedElements();

protected:

    QHash<int, QByteArray> roleNames() const;

private:
    QList<CZeitschrift> m_ZeitschriftenList;

    static const int Role_Zeitschrift;
    static const int Role_Selection;
};

#endif // CZEITSCHRIFTDISPLAYLIST_H
