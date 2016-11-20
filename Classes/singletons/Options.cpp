#include "Options.h"
#include "json/document.h"
#include "platform/CCFileUtils.h"

USING_NS_CC;
USING_NS_UBA;


uba::Options::Options()
	: _language(Language::NONE)
{

}


Options& uba::Options::getInstance()
{
	static Options instance;
	return instance;
}

bool uba::Options::init()
{
	rapidjson::Document doc;

	try
	{
		auto optionsStr = FileUtils::getInstance()->getStringFromFile("options.json");

		doc.Parse<0>(optionsStr.c_str());

		if (doc.HasParseError())
			return false;

		if (doc.HasMember("language"))
		{
			auto& lang = doc["language"];
			if (lang.GetType() == rapidjson::kStringType)
			{
				_languageCode = std::string{ lang.GetString() };

				if (_languageCode == "en")
				{
					_language = Language::ENGLISH;
				}
			}
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}
