#pragma once
#include <vector>
#include <QWebEngineView>
#include <memory>
#include <QTimer>
#include <QWebChannel>
#include <QWebEngineView>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineSettings>
#include <QUrlQuery>
#include <QWebEngineUrlRequestInfo>
#include <QWebEngineProfile>
#include <QJSEngine>
#include "VideoData.h"
#include "WebEngineView.h"

class MediaPlayer : public QObject
{
	Q_OBJECT

public:
	explicit MediaPlayer(QObject *parent = Q_NULLPTR);
	~MediaPlayer();

private:
	std::vector<tVideoData> vecVideoList;

	WebEngineView *m_mainView;
	WebEngineView *m_swapView1;
	WebEngineView *m_swapView2;

	int m_iCurrentIndex;
	int m_iPrevIndex;
	int m_iNextIndex;

	bool m_bPause;
	bool m_bLoop;

public:
	void Play();
	void Pause();

	QWebEngineView *GetMainWebView() const { return m_mainView->GetWebView(); }
	QWebEngineView *GetSwapWebView1() const { return m_swapView1->GetWebView(); }
	QWebEngineView *GetSwapWebView2() const { return m_swapView2->GetWebView(); }

	void setUrl(const QString &urlStr);
	QString getVUrl(const QString &urlStr);

	void pushVideoList(QString _url, QString _title, double _startTime, double _endTime, double _speed);
	tVideoData GetVideoData_From_VideoList(int _index);

public:
	void Awake();
	void Start();
	void Update();

private slots:
	void OnTimerCallback();
};

