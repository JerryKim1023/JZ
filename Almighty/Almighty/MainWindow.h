#pragma once

#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QClipboard>
#include <QPalette>
#include <QMainWindow>
#include <QFocusEvent>
#include "MediaPlayer.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

public:
	void enterEvent(QEvent *e) override;
	void leaveEvent(QEvent *e) override;

private:
	Ui::MainWindow *ui;
	int m_resizeScale;
	unsigned int m_controlBarHeight;
	QString html;

	MediaPlayer *m_player;

private slots:
	void resizeClicked(bool clicked);
	void youtubeClicked(bool clicked);
	void handleHTML(QString _html);

signals:
	void getHTML(QString _html);


};
