#ifndef CSELECTIONLISTDISPLAY_H
#define CSELECTIONLISTDISPLAY_H

#include <QAbstractListModel>
#include <QObject>
class CSelectionListDisplay  : public QAbstractListModel
{
	Q_OBJECT
public:
	CSelectionListDisplay(QObject *parent = nullptr);
	virtual ~CSelectionListDisplay();

	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

signals:
	void listEmpty();

public slots:
	void deleteAll();
	void SetList(QList<QString> list);

    void UpdateListDisplay(QString filter);

    QString getElementFromDisplay(int index);


protected:

	QHash<int, QByteArray> roleNames() const;

private:

    void SetElementToDisplayList(const QString& element);

	QList<QString> m_ElementList;
    QList<QString> m_DisplayList;


	static const int  Role_Element;

};

#endif // CRUBRIKLISTDISPLAY_H
