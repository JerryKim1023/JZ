function output(message) {
    var output = document.getElementById("output");
    output.innerHTML = output.innerHTML + message + "\n";
}

$(document).ready(function () {
    output("document.ready");
});

window.onload = function () {
    output("window.onload");
}

new QWebChannel(qt.webChannelTransport, function (channel) {
    window.media = channel.objects.media;

    output("QwebChannel 생성");

    media.PauseSignal.connect(function () { pause(); });
    media.PlaySignal.connect(function () { play(); });
    media.ClearVideoDictSignal.connect(function () { clearVideoDict(); });
    media.SetVideoIdSignal.connect(function (_videoId) { setVideoId(_videoId); });
    media.SetVideoStartSignal.connect(function (_start) { setVideoStart(_start); });
    media.SetVideoEndSignal.connect(function (_end) { setVideoEnd(_end); });
    media.SetQualitySignal.connect(function (_quality) { setQuality(_quality); });
    media.LoadSignal.connect(function () { LoadVideo(); });
});

var player;
var timeupdater;
var currentTime = 0;
var done = false;

/*
// dictVideo를 세팅하고 LoadVideo를 통해서
// yt Player을 로드 시킨다.
*/
var dictVideo = {};

function pause() {
    if (player)
        player.pauseVideo();
}

function play() {
    if (player)
        player.playVideo();
}

function clearVideoDict() {
    dictVideo = {};
}
function setVideoStart(_start) {
    dictVideo['startSeconds'] = _start;
}

function setQuality(_quality) {
    dictVideo['suggestedQuality'] = _quality;
}

function setVideoEnd(_end) {
    dictVideo['endSeconds'] = _end;
}

function setVideoId(_videoId) {
    dictVideo['videoId'] = _videoId;
}

function LoadVideo() {
    if (player) {
        player.loadVideoById(dictVideo);
        output("player.loadVideo");
    }
}

var tag = document.createElement('script');

tag.src = "https://www.youtube.com/iframe_api";
var firstScriptTag = document.getElementsByTagName('script')[0];
firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);
var origin = document.location.origin;
function onYouTubeIframeAPIReady() {
    player = new YT.Player('ytplayer', {
        //videoId: strVideoId,
        // 'RRubcjpTkks'
        playerVars: {
            'autoplay': 0, 'controls': 1
        },
        events: {
            'onReady': onPlayerReady,
            'onStateChange': onPlayerStateChange
        }
    });
    output("onYouTubeIframeAPIReady");
}

function onPlayerReady(event) {
    media.PlayerReady();
    //player.playVideo();
    //player.loadVideoById({ 'videoId': strVideoId, 'startSeconds': 5, 'endSeconds': 15, 'suggestedQuality': 'medium' });
}
function onPlayerStateChange(event) {
    if (event.data == YT.PlayerState.PLAYING) {
        if (!done) {
            timeupdater = setInterval(updateTime, 100);
            done = true;
        }
    }
    else if (event.data != YT.PlayerState.PLAYING) {
        if (timeupdater) {
            clearInterval(timeupdater);
        }
        done = false;
    }
}

function updateTime() {
    if (!player)
        return;

    currentTime = player.getCurrentTime();
    media.setCurrentTime(currentTime);
}