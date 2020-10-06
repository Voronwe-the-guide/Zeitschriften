#include "cwindowinfo.h"

CWindowInfo::CWindowInfo()
{

}

CWindowInfo::CWindowInfo(QSize size):
	CWindowInfo()
{
	 m_windowSize =size;
}

QSize CWindowInfo::getWindowSize() const
{
	return m_windowSize;
}

void CWindowInfo::setWindowSize(const QSize &windowSize)
{
	m_windowSize = windowSize;
}


QJsonObject CWindowInfo::getAsJSON()
{
	QJsonObject jsonObject;
	jsonObject["Height"]=m_windowSize.height();
	jsonObject["Width"]=m_windowSize.width();
	return jsonObject;

}
void CWindowInfo::setFromJSON(QJsonObject array)
{
	setWindowSize(QSize(array["Width"].toInt(),array["Height"].toInt()));
}
