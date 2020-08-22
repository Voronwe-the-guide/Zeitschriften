#ifndef CJAHR_H
#define CJAHR_H

#include "causgabe.h"

class CJahr
{
public:
	CJahr();
	CJahr (const  CJahr&) = default;
	CJahr& operator=(const CJahr&) = default;
	CJahr ( CJahr&&) = default;
	CJahr& operator=( CJahr&&) = default;

	virtual ~CJahr() = default;

	bool setDBElement(QString columnName, QString columnEntry);

	int Jahr() const;
	void setJahr(int jahr);

private:
	int m_Jahr;

};

#endif // CJAHR_H
