#include "User.h"

USING_NS_UBA;


uba::User::User()
{

}


User& uba::User::getInstance()
{
	static User instance;
	return instance;
}

bool uba::User::init(const std::string& username, const std::string& sex)
{
	try
	{
		_username = username;

		if (sex == "male")
		{
			_sex = 1;
		}
		else
		{
			_sex = 0;
		}


		return true;
	}
	catch (...)
	{
		return false;
	}
}