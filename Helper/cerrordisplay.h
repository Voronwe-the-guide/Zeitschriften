#ifndef CERRORDISPLAY_H
#define CERRORDISPLAY_H

#include <QObject>

class CErrorDisplay : public QObject
{
	Q_OBJECT
public:
	explicit CErrorDisplay(QObject *parent = nullptr);

public slots:
	void gotErrorMessage(QString sender, QString Message);

signals:
	void displayError(QString error);

};

#endif // CERRORDISPLAY_H
