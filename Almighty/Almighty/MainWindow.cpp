#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	//ui 메인 윈도우 설정.
	ui->setupUi(this);
	//style sheet 설정
	//this->setStyleSheet("background-color: black;");
	QPalette pal(palette());
	pal.setColor(QPalette::Background, Qt::black);
	setPalette(pal);

	//movePushButton 메인 윈도우 설정
	ui->movePushButton->setMainWinow(this);

	//화면 세팅
	// windowflags 설정
	setWindowFlags(Qt::Widget | Qt::WindowStaysOnTopHint); //| Qt::FramelessWindowHint


	m_resizeScale = 2;
	m_controlBarHeight = 28;
	// 화면 해상도 사이즈 가져옴.
	QRect rect = QApplication::desktop()->screenGeometry(this);
	int width = 128 * (m_resizeScale + 2);
	int height = 72 * (m_resizeScale + 2);

	ui->controlWidget->setVisible(true);
	if( ui->controlWidget->isVisible() ) // 생성자에서 이 함수는 x, 아직 생성안됨.
	{
		height += m_controlBarHeight;
	}

	// 위젯의 위치와 크기를 세팅
	setGeometry(rect.width() / 2 - width / 2, rect.height() / 2 - height / 2, width, height);

	//시그널 세팅
	connect(ui->verticalLayout_2, SIGNAL(getHTML(QString)), this, SLOT(handleHTML(QString)));
	connect(ui->resizePushButton, SIGNAL(clicked(bool)), this, SLOT(resizeClicked(bool)));
	connect(ui->goPushButton, SIGNAL(clicked(bool)), this, SLOT(youtubeClicked(bool)));

	//수정할 부분.
    // 미디어 플레이어 
	m_player = new MediaPlayer(this);
	m_player->Start();
	ui->verticalLayout_2->insertWidget(0, m_player->GetSwapWebView1());
	ui->verticalLayout_2->insertWidget(1, m_player->GetSwapWebView2());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::enterEvent(QEvent *e)
{
	return;
	int width = 128 * (m_resizeScale + 2);
	int height = 72 * (m_resizeScale + 2);

	//if( ui->controlWidget->isVisible() )
	{
		height += m_controlBarHeight;
	}
	ui->controlWidget->setVisible(true);
	setGeometry(geometry().x(), geometry().y(), width, height);

	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(150);
	animation->setStartValue(windowOpacity());
	animation->setEndValue(0.7);
	animation->start();

	//객체 삭제
	connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater));

	setFocus(Qt::MouseFocusReason);
}

void MainWindow::leaveEvent(QEvent *e)
{
	return;
	int width = 128 * (m_resizeScale + 2);
	int height = 72 * (m_resizeScale + 2);

	//if( ui->controlWidget->isVisible() )
	{
		//height += m_controlBarHeight;
	}
	setGeometry(geometry().x(), geometry().y(), width, height);
	ui->controlWidget->setVisible(false);

	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(150);
	animation->setStartValue(windowOpacity());
	animation->setEndValue(1.0);
	animation->start();

	//객체 삭제
	connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater));
}


void MainWindow::resizeClicked(bool clicked)
{
	m_resizeScale = (--m_resizeScale);

	if( m_resizeScale < 0 )
	{
		m_resizeScale = 3;
	}

	int width = 128 * (m_resizeScale + 2);
	int height = 72 * (m_resizeScale + 2);

	if( ui->controlWidget->isVisible() )
	{
		height += m_controlBarHeight;
	}

	setGeometry(geometry().x(), geometry().y(), width, height);
}


bool bCh = false;

void MainWindow::youtubeClicked(bool clicked)
{
	/*int i = ui->verticalLayout_2->count();
	ui->verticalLayout_2->insertWidget(1, ui->verticalLayout_2->itemAt(0)->widget());

	QWebEnginePage *page1 = (bCh == false) ? m_player->GetWebView()->page() : m_player->GetNextWebView()->page();
	QWebEnginePage *page2 = (bCh == false) ? m_player->GetNextWebView()->page() : m_player->GetWebView()->page();
	
	bCh = (bCh == false) ? true : false;
	page1->setWebChannel(Q_NULLPTR);
	page2->setWebChannel(m_player->GetWebChannel());

	m_player->Update();*/
	//m_player->Pause();

	//QClipboard *clipboard = QApplication::clipboard();
	//QString originalText = clipboard->text();

	//setUrl(originalText);

	//html 정보 가져오기
	//m_webView->page()->toHtml([this](const QString &result) mutable {emit getHTML(result); });
}

void MainWindow::handleHTML(QString _html)
{
	html = _html;
}
