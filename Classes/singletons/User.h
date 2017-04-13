#ifndef User_h__
#define User_h__

#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

class User
{
public:
	static User& getInstance();

	bool init(const std::string& username, const std::string& sex);

	User(const User&) = delete;
	void operator=(const User&) = delete;

	std::string getUsername() const { return _username; }
	std::string getSex() const { return _sex; }
private:
	User();

	std::string _username;
	std::string _sex;
};

NS_UBA_END

#endif // User_h__
