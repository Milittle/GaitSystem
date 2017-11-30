#pragma once
#include <QEvent.h>

class MyEvent:public QEvent
{
public:
	MyEvent(QEvent::Type type);
	~MyEvent();
	void SetValue(int nValue);
	int GetValue();

private:
	int m_nValue;
};

