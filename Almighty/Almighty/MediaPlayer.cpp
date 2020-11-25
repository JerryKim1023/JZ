#include "MediaPlayer.h"
#include <windows.h>
#include <string>

#define EPSILON 0.01

MediaPlayer::MediaPlayer(QObject *parent) : QObject(parent)
, m_mainView(Q_NULLPTR)
, m_swapView1(Q_NULLPTR)
, m_swapView2(Q_NULLPTR)
, m_iCurrentIndex(0)
, m_iPrevIndex(0)
, m_iNextIndex(0)
, m_bPause(false)
, m_bLoop(false)
{


}


MediaPlayer::~MediaPlayer()
{
}

void MediaPlayer::Play()
{

}

void MediaPlayer::Pause()
{

}

void MediaPlayer::Awake()
{
}

void MediaPlayer::Start()
{
	m_swapView1 = new WebEngineView;
	m_swapView2 = new WebEngineView;

	m_mainView = m_swapView1;

	// 일단 test용으로 데이터 하나 준비해서 넣는중.
	pushVideoList("oWhkL4899u8",
		"바보",
		0.0,
		80.0,
		1.0
	);

}

void MediaPlayer::Update()
{
	//m_bPause = false;
	////한번 만 가져오기.
	//tVideoData currentVideo = vecVideoList[m_iCurrentIndex];
	//QString strVideoId = getVUrl(currentVideo.url);
	//QString strVideoTitle = currentVideo.title;
	//double startTime = currentVideo.startTime;
	//double endTime = currentVideo.endTime;
	//double playBackRate = currentVideo.speed;

	//// 계속 업데이트
	//if( m_bPause == true )
	//	return;

	//if( strVideoId.isEmpty() )
	//	return;

	//emit ClearVideoDictSignal((int)eSignalNum::MAIN);
	//emit SetVideoIdSignal(strVideoId, (int)eSignalNum::MAIN);
	//if( startTime > 0 )
	//	emit SetVideoStartSignal(startTime, (int)eSignalNum::MAIN);
	//if( endTime > 0 )
	//	emit SetVideoEndSignal(endTime, (int)eSignalNum::MAIN);
	//if( abs(playBackRate - 1.0) >= EPSILON )
	//{
	//	// 속도 변경.
	//}

	//emit LoadSignal((int)eSignalNum::MAIN);

	//if( abs(m_dCurrentTime - endTime) >= EPSILON )
	//{
	//	m_dCurrentTime = 0;
	//	m_iPrevIndex = m_iCurrentIndex;
	//	++m_iCurrentIndex; // 다음 곡으로 넘어가기.	
	//	m_iNextIndex = m_iCurrentIndex + 1;

	//	if( vecVideos.size() < m_iCurrentIndex )
	//	{
	//		currentVideo = vecVideos[m_iCurrentIndex];

	//		startTime = currentVideo.startTime.toInt();
	//		endTime = currentVideo.endTime.toInt();
	//	}
	//	else
	//	{
	//		// 루프로 돌아가거나 할것.
	//	}
	//}

}

void MediaPlayer::OnTimerCallback()
{
	//// web페이지에 java에서 현재 video getCurrentTime 갱신해서 가져오기.
	//if( m_webView == Q_NULLPTR )
	//	return;
	//QString functionJs = "function findFirstVideoTag() {"
	//	"var all = document.getElementsByTagName('video');"
	//	"if (all.length > 0)"
	//	"return all[0];"
	//	"else {"
	//	"var i, frames;"
	//	"frames = document.getElementsByTagName('iframe');"
	//	"for (i = 0; i < frames.length; ++i) {"
	//	"try { var childDocument = frame.contentDocument } catch (e) { continue };"
	//	"all = frames[i].contentDocument.document.getElementsByTagName('video');"
	//	"if (all.length > 1)"
	//	"return all[0];"
	//	"}"
	//	"return null;"
	//	"}"
	//	"}"
	//	"video_element = findFirstVideoTag();"
	//	"if(video_element != null)"
	//	"video_element.getCurrentTime();";

	//m_webView->page()->runJavaScript(functionJs, [this](const QVariant &v) {
	//	m_iCurrentTime = v.toInt();
	//	});
}


void MediaPlayer::setUrl(const QString &urlStr)
{
	QUrl url = QUrl::fromUserInput(urlStr);
	QUrlQuery query(url);

	if( url.isValid() && query.hasQueryItem("v") && url.host() == "www.youtube.com" )
	{
		//QUrl embedLink = QUrl::fromUserInput(QString("https://www.youtube.com/embed/").append(query.queryItemValue("v")));

		//ui->addressLineEdit->setText(url.toString());

		//m_webView->load(embedLink);

		QString videoId = query.queryItemValue("v");

		//m_webView->load(url);
	}
}

QString MediaPlayer::getVUrl(const QString &urlStr)
{
	QUrl url = QUrl::fromUserInput(urlStr);
	QUrlQuery query(url);

	if( url.isValid() && query.hasQueryItem("v") && url.host() == "www.youtube.com" )
	{
		return  query.queryItemValue("v");
	}

	return "";
}

void MediaPlayer::pushVideoList(QString _url, QString _title, double _startTime, double _endTime, double _speed)
{
	tVideoData videoData;
	videoData.url = _url;

	//videoData.url = "http://www.youtube.com/watch?v=xBusf1L2vhk&t=3s";
	videoData.title = _title;
	videoData.startTime = _startTime;
	videoData.endTime = _endTime;
	videoData.speed = _speed;

	vecVideoList.push_back(videoData);
}

tVideoData MediaPlayer::GetVideoData_From_VideoList(int _index)
{
	if( vecVideoList.size() <= _index || _index < 0 )
		return tVideoData();

	//한번 만 가져오기.
	tVideoData currentVideo = vecVideoList[_index];
	QString strVideoId = getVUrl(currentVideo.url);
	QString strVideoTitle = currentVideo.title;
	double startTime = currentVideo.startTime;
	double endTime = currentVideo.endTime;
	double playBackRate = currentVideo.speed;

	return currentVideo;
}
