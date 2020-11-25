#include "MoveButton.h"

MoveButton::MoveButton(QWidget *parent)
	: QPushButton(parent)
	, m_mousePressed(false)
	, m_window(Q_NULLPTR)
{
}

void MoveButton::setMainWinow(QMainWindow *window)
{
	m_window = window;
}

void MoveButton::mousePressEvent(QMouseEvent *e)
{
	m_mousePressed = true;
	m_mousePos = e->globalPos();

	if( m_window )
		m_windowsPos = m_window->pos(); 
}

void MoveButton::mouseReleaseEvent(QMouseEvent *e)
{
	Q_UNUSED(e);
	m_mousePressed = false;
}

void MoveButton::mouseMoveEvent(QMouseEvent *e)
{
	if( m_window && m_mousePressed )
	{
		m_window->move(m_windowsPos + (e->globalPos() - m_mousePos));
	}
}
