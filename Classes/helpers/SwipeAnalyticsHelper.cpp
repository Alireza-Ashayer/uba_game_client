#include "SwipeAnalyticsHelper.h"
#include "singletons/User.h"
#include <limits>

USING_NS_UBA;
USING_NS_CC;


uba::SwipeAnalyticsHelper::SwipeAnalyticsHelper()
{

}


bool uba::SwipeAnalyticsHelper::init(std::vector<std::pair<int64_t, cocos2d::Vec2>> input)
{
	try
	{
		_timeStamps.clear();
		_positions.clear();


		for (auto it = input.begin(); it < input.end(); it++)
		{
			_timeStamps.push_back(it->first);
			_positions.push_back(it->second);
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}

uba::AnalyticsData uba::SwipeAnalyticsHelper::getAnalyticsData() const
{
	AnalyticsData result;

	result.category = 1;

	result.direction = getDirection();

	result.username = User::getInstance().getUsername();
	result.gender = User::getInstance().getSex();
	result.ageGroup = User::getInstance().getAgeGroup();

	result.totalLength = getTotalLength();
	result.totalTime = getTotalTime();
	result.width = getWitdh();
	result.height = getHeight();
	result.maxSpeed = getMaxSpeed();
	result.averageSpeed = getAverageSpeed();
	result.vecAngle = getVecAngle();
	result.maxAccel = getMaxAccel();
	result.avgAccel = getAvgAccel();

	result.startAccX = getAccPos(Vec3::UNIT_X, true);
	result.startAccY = getAccPos(Vec3::UNIT_Y, true);
	result.startAccZ = getAccPos(Vec3::UNIT_Z, true);

	result.endAccX = getAccPos(Vec3::UNIT_X, false);
	result.endAccY = getAccPos(Vec3::UNIT_Y, false);
	result.endAccZ = getAccPos(Vec3::UNIT_Z, false);


	result.startAccVX = getAccVel(Vec3::UNIT_X, true);
	result.startAccVY = getAccVel(Vec3::UNIT_Y, true);
	result.startAccVZ = getAccVel(Vec3::UNIT_Z, true);

	result.endAccVX = getAccVel(Vec3::UNIT_X, false);
	result.endAccVY = getAccVel(Vec3::UNIT_Y, false);
	result.endAccVZ = getAccVel(Vec3::UNIT_Z, false);


	return result;
}


int uba::SwipeAnalyticsHelper::getDirection() const
{
	return 0;
}


float uba::SwipeAnalyticsHelper::getTotalLength() const
{
	float result = 0;
	for (unsigned int i = 0; i < _positions.size() - 1; i++)
	{
		auto pos = _positions[i];
		auto nextPos = _positions[i + 1];

		auto distance = pos.distance(nextPos);
		result += distance;
	}

	return result;
}

float uba::SwipeAnalyticsHelper::getTotalTime() const
{
	float result = 0;

	result = _timeStamps[_timeStamps.size() - 1] - _timeStamps[0];

	return result;
}

float uba::SwipeAnalyticsHelper::getWitdh() const
{
	float minX = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();

	for (unsigned int i = 0; i < _positions.size(); i++)
	{
		auto position = _positions[i];
		if (position.x < minX)
		{
			minX = position.x;
		}

		if (position.x > maxX)
		{
			maxX = position.x;
		}
	}

	auto result = maxX - minX;

	if (result < 0)
		result = 0;

	return result;
}

float uba::SwipeAnalyticsHelper::getHeight() const
{
	float minY = std::numeric_limits<float>::max();
	float maxY = std::numeric_limits<float>::min();

	for (unsigned int i = 0; i < _positions.size(); i++)
	{
		auto position = _positions[i];
		if (position.y < minY)
		{
			minY = position.y;
		}

		if (position.y > maxY)
		{
			maxY = position.y;
		}
	}

	auto result = maxY - minY;

	if (result < 0)
		result = 0;

	return result;
}

float uba::SwipeAnalyticsHelper::getMaxSpeed() const
{
	float maxSpeed = std::numeric_limits<float>::min();

	for (unsigned int i = 0; i < _positions.size() - 1; i++)
	{
		float distance = _positions[i + 1].distance(_positions[i]);
		float time = _timeStamps[i + 1] - _timeStamps[i];

		if (time > 0)
		{
			auto speed = distance / time;

			if (maxSpeed < speed)
			{
				maxSpeed = speed;
			}
		}
	}

	return maxSpeed;
}

float uba::SwipeAnalyticsHelper::getAverageSpeed() const
{
	float sumSpeed = 0;
	int count = 0;

	for (unsigned int i = 0; i < _positions.size() - 1; i++)
	{
		float distance = _positions[i + 1].distance(_positions[i]);
		float time = _timeStamps[i + 1] - _timeStamps[i];

		if (time > 0)
		{
			auto speed = distance / time;
			sumSpeed += speed;
			count++;
		}
	}

	if (count <= 0)
	{
		return 0;
	}

	return sumSpeed / count;
}

float uba::SwipeAnalyticsHelper::getVecAngle() const
{
	if (_positions.size() > 2)
	{
		auto moveVec = _positions[_positions.size() - 1] - _positions[0];
		return moveVec.getAngle();
	}

	return 0;
}

std::vector<cocos2d::Vec2> uba::SwipeAnalyticsHelper::getSpeedVector() const
{
	std::vector<cocos2d::Vec2> result;

	for (unsigned int i = 0; i < _positions.size() - 1; i++)
	{
		auto distance = _positions[i + 1] - (_positions[i]);
		float time = _timeStamps[i + 1] - _timeStamps[i];

		if (time > 0)
		{
			auto speed = distance / time;

			result.push_back(speed);
		}
	}

	return result;
}

std::vector<cocos2d::Vec2> uba::SwipeAnalyticsHelper::getAccelVector() const
{
	std::vector<cocos2d::Vec2> result;
	auto speedVector = getSpeedVector();

	for (unsigned int i = 0; i < speedVector.size() - 1 && i < _timeStamps.size() - 2; i++)
	{
		auto distance = speedVector[i + 1] - (speedVector[i]);
		float time = _timeStamps[i + 2] - _timeStamps[i];

		if (time > 0)
		{
			auto acc = distance / time;

			result.push_back(acc);
		}
	}

	return result;
}

float uba::SwipeAnalyticsHelper::getMaxAccel() const
{
	float maxAcc = std::numeric_limits<float>::min();

	auto accVec = getAccelVector();

	for (unsigned int i = 0; i < accVec.size(); i++)
	{
		auto vec = accVec[i];
		if (vec.length() > maxAcc)
		{
			maxAcc = vec.length();
		}
	}

	return maxAcc;
}

float uba::SwipeAnalyticsHelper::getAvgAccel() const
{
	float totalAcc = 0;
	int count = 0;

	auto accVec = getAccelVector();

	for (unsigned int i = 0; i < accVec.size(); i++)
	{
		auto vec = accVec[i];
		if (vec.length() > 0)
		{
			totalAcc += vec.length();
			count++;
		}
	}

	if (count <= 0)
	{
		return 0;
	}

	return totalAcc / count;
}

bool uba::SwipeAnalyticsHelper::initAccData(std::vector<cocos2d::Vec3> input)
{
	_accs.clear();
	_accs = std::vector<cocos2d::Vec3>(input);

	return true;
}

float uba::SwipeAnalyticsHelper::getAccPos(cocos2d::Vec3 axis, bool starting) const
{
	if (_accs.size() < 1)
	{
		return 0;
	}

	auto selected = Vec3::ZERO;
	if (starting)
	{
		selected = _accs.at(0);
	}
	else
	{
		selected = _accs.at(_accs.size() - 1);
	}

	if (axis == Vec3::UNIT_X)
	{
		return selected.x;
	}
	else if (axis == Vec3::UNIT_Y)
	{
		return selected.y;
	}
	else if (axis == Vec3::UNIT_Z)
	{
		return selected.z;
	}

	return 0;
}

float uba::SwipeAnalyticsHelper::getAccVel(cocos2d::Vec3 axis, bool starting) const
{
	if (_accs.size() < 2 || _timeStamps.size() < 2)
	{
		return 0;
	}

	int64_t t1 = 0;
	int64_t t2 = 0;
	

	auto x2 = Vec3::ZERO;
	auto x1 = Vec3::ZERO;

	if (starting)
	{
		x1 = _accs[0];
		x2 = _accs[1];

		t1 = _timeStamps[0];
		t2 = _timeStamps[1];
	}
	else
	{
		x1 = _accs.at(_accs.size() - 2);
		x2 = _accs.at(_accs.size() - 1);

		t1 = _timeStamps.at(_accs.size() - 2);
		t2 = _timeStamps.at(_accs.size() - 1);
	}

	auto dx = x2 - x1;
	float dt = t2 - t1;

	auto velocity = dx / dt;


	if (axis == Vec3::UNIT_X)
	{
		return velocity.x;
	}
	else if (axis == Vec3::UNIT_Y)
	{
		return velocity.y;
	}
	else if (axis == Vec3::UNIT_Z)
	{
		return velocity.z;
	}

	return 0;
}

