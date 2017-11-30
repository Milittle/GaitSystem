#include "MyEvent.h"




MyEvent::MyEvent(QEvent::Type type):QEvent(type)
{
	m_nValue = 0;
}


MyEvent::~MyEvent()
{
}


void MyEvent::SetValue(int nValue)
{
	m_nValue = nValue;
}

int MyEvent::GetValue()
{
	return m_nValue;
}