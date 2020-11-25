#include "WebEngineView.h"
#include <windows.h>

WebEngineView::WebEngineView(QObject *parent) : QObject(parent)
, m_webView(Q_NULLPTR)
, m_webChannel(Q_NULLPTR)
{
	// 생성자에서 webView와 webChannel, load를 진행 하고 있는데. 나중에 위치 옮겨 됨.
	// 현재 문제는 webView를 디버깅할 수 있는 기능을 추가 해야한다는 것임.
	m_webView = new QWebEngineView();
	m_webView->page()->setBackgroundColor(Qt::black);
	m_webView->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
	m_webView->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
	m_webView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

	//웹 채널
	m_webChannel = new QWebChannel(this);
	m_webChannel->registerObject("media", this);
	m_webView->page()->setWebChannel(m_webChannel);

	QUrl url = QUrl(QStringLiteral("qrc:/index.html"));
	m_webView->load(url);
}


WebEngineView::~WebEngineView()
{
}

/*
* webchannel에서 currentTime을 받아오는 함수이고, 받아올때는 QVariant, QjsonValue, QJsonDocument로
* 받아와야함을 기억 하고 있을 것.
*/
void WebEngineView::setCurrentTime(QVariant _currentTime)
{
	m_dCurrentTime = _currentTime.toDouble();

	//OutputDebugString(std::to_wstring(m_dCurrentTime).c_str());
}

void WebEngineView::PlayerReady()
{
	emit ClearVideoDictSignal();
	emit SetVideoIdSignal("oWhkL4899u8");
	emit SetVideoStartSignal(0.0);
	emit SetVideoEndSignal(80.0);

	emit LoadSignal();
}
