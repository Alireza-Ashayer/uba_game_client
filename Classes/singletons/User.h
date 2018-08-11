#ifndef User_h__
#define User_h__

#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

class User
{
public:
	static User& getInstance();

	bool init(const std::string& username, const std::string& sex, const std::string& ageGroup);

	User(const User&) = delete;
	void operator=(const User&) = delete;

	std::string getUsername() const { return _username; }
	int getSex() const { return _sex; }
	int getAgeGroup() const { return _ageGroup; }
private:
	User();

	std::string _username;
	int _sex;
	int _ageGroup;
};

NS_UBA_END

#endif // User_h__
