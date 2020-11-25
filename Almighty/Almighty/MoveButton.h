#pragma once


#include <QPushButton>
#include <QMouseEvent>
#include <QMainWindow>

class MoveButton : public QPushButton
{
	Q_OBJECT
private:
	bool m_mousePressed;
	QPoint m_windowsPos;
	QPoint m_mousePos;
	QMainWindow *m_window;

public:
	MoveButton(QWidget *parent = Q_NULLPTR);

	void setMainWinow(QMainWindow *window);
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
};