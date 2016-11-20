#ifndef Options_h__
#define Options_h__

#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

enum class Language
{
	ENGLISH,
	NONE
};


class Options
{
public:
	static Options& getInstance();

	bool init();



	nba::Language getLanguage() const { return _language; }
	std::string getLanguageCode() const { return _languageCode; }


	Options(const Options&) = delete;
	void operator=(const Options&) = delete;

private:
	Options();


	Language _language;

	std::string _languageCode;
};

NS_UBA_END

#endif // Options_h__
