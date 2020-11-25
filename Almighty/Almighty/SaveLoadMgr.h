#pragma once
#include <vector>
#include "define.h"
#include "VideoData.h"

class SaveLoadMgr
{
	SINGLE(SaveLoadMgr);

public:
	enum class SaveFormat
	{
		Json, Binary
	};

	SaveFormat m_saveFormat;
	std::vector<tVideoData> m_vecVides;
	QString m_fileName;
	QString m_filePath;

public:
	bool load(SaveFormat _loadFormat);
	bool save(SaveFormat _saveFormat);
};

