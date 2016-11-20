#include "StringCache.h"
#include "json/document.h"
#include "platform/CCFileUtils.h"
#include "base/ccUTF8.h"

USING_NS_CC;
USING_NS_UBA;

const std::string STRING_FILE_PATH = "strings/strings_%s.json";

uba::StringCache::StringCache()
{

}


StringCache& uba::StringCache::getInstance()
{
	static StringCache instance;
	return instance;
}

bool uba::StringCache::init(const std::string& languageCode)
{
	_data.clear();

	rapidjson::Document doc;

	try
	{
		auto filePath = StringUtils::format(STRING_FILE_PATH.c_str(), languageCode.c_str());
		auto stringsStr = FileUtils::getInstance()->getStringFromFile(filePath);

		doc.Parse<0>(stringsStr.c_str());

		if (doc.HasParseError())
			return false;

		if (doc.GetType() != rapidjson::kObjectType)
			return false;

		for (auto it = doc.MemberBegin(); it != doc.MemberEnd(); ++it)
		{
			auto& keyObj = it->name;
			auto& valueObj = it->value;

			if (keyObj.GetType() == rapidjson::kStringType && valueObj.GetType() == rapidjson::kStringType)
			{
				auto keyStr = std::string{ keyObj.GetString() };
				auto valueStr = std::string{ valueObj.GetString() };
				_data.insert(std::make_pair(keyStr, valueStr));
			}
		}


		return true;
	}
	catch (...)
	{
		return false;
	}
}

std::string uba::StringCache::getStringByKey(const std::string& key) const
{
	if (_data.find(key) != _data.end())
	{
		return _data.at(key);
	}
	
	return std::string{ key };
}
