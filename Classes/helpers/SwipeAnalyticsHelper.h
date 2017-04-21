#ifndef SwipeAnalyticsHelper_h__
#define SwipeAnalyticsHelper_h__

#include "macros/AppMacros.h"
#include "singletons/Analytics.h"

#include <string>
#include "math/Vec2.h"
#include "math/Vec3.h"

NS_UBA_BEGIN

class SwipeAnalyticsHelper
{
public:
	SwipeAnalyticsHelper();

	bool init(std::vector<std::pair<int64_t, cocos2d::Vec2>> input);
	bool initAccData(std::vector<cocos2d::Vec3> input);

	AnalyticsData getAnalyticsData() const;

	void setIsUpOrDown(bool isUp);

private:

	float getTotalLength() const;
	float getTotalTime() const;
	float getWitdh() const;
	float getHeight() const;
	float getMaxSpeed() const;
	float getAverageSpeed() const;
	float getVecAngle() const;
	std::vector<cocos2d::Vec2> getSpeedVector() const;
	std::vector<cocos2d::Vec2> getAccelVector() const;
	float getMaxAccel() const;
	float getAvgAccel() const;
	float getAccPos(cocos2d::Vec3 axis, bool starting) const;
	float getAccVel(cocos2d::Vec3 axis, bool starting) const;

	std::vector<int64_t> _timeStamps;
	std::vector<cocos2d::Vec2> _positions;
	std::vector <cocos2d::Vec3> _accs;

	bool _isUp;
};

NS_UBA_END

#endif // SwipeAnalyticsHelper_h__
