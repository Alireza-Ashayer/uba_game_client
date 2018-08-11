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

bool uba::User::init(const std::string& username, const std::string& sex, const std::string& ageGroup)
{
	try
	{
		_username = username;

		if (sex == "male")
			_sex = 1;
		else if (sex == "female") 
			_sex = 0;
		else
			_sex = -1;

		if (ageGroup == "+40") 
			_ageGroup = 1;
		else if (ageGroup == "-40")
			_ageGroup = 0;
		else
			_ageGroup = -1;
		


		return true;
	}
	catch (...)
	{
		return false;
	}
}