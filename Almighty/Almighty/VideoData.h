#pragma once
#include <QString>

struct tVideoData
{
	QString url;
	QString title;
	double startTime;
	double endTime;
	double speed;

	tVideoData() :
		url("")
		, title("")
		, startTime(0.0)
		, endTime(0.0)
		, speed(1.0)
	{
	}
};
