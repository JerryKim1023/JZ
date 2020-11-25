#pragma once
#include <QWebChannel>
#include <QWebEngineView>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineSettings>

/*
미리 로드를 해놓고 swap 해주기 위해
2개를 player에서 만들것이고,
webengineview는 qwebchannel을 통해
javascript와 통신을 할 것임.
채널을 통해 통신 하기 위해서 QObject를 상속받아.
slot과 slagals을 사용 하게 했음.
*/
class WebEngineView : public QObject
{
	Q_OBJECT

public:
	explicit WebEngineView(QObject *parent = Q_NULLPTR);
	~WebEngineView();

private:
	QWebEngineView *m_webView;
	QWebChannel *m_webChannel;

	double m_dCurrentTime = 0.0;

public:
	QWebEngineView *GetWebView() const { return m_webView; }
	QWebChannel *GetWebChannel() const { return m_webChannel; }

public slots:
	void setCurrentTime(QVariant _currentTime);
	void PlayerReady();

signals:
	void PauseSignal();
	void PlaySignal();

	void ClearVideoDictSignal();
	void SetVideoIdSignal(QString);
	void SetVideoStartSignal(int);
	void SetVideoEndSignal(int);
	void SetQualitySignal(QString);
	void LoadSignal();
};

