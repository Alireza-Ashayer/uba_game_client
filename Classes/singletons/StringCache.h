#ifndef StringCache_h__
#define StringCache_h__


#include "macros/AppMacros.h"

#include <string>
#include <map>

NS_UBA_BEGIN


class StringCache
{
public:
	static StringCache& getInstance();

	bool init(const std::string& languageCode);

	std::string getStringByKey(const std::string& key) const;

	StringCache(const StringCache&) = delete;
	void operator=(const StringCache&) = delete;

private:
	StringCache();

	std::map<std::string, std::string> _data;
};

NS_UBA_END

#endif // StringCache_h__
