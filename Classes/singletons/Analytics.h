#ifndef Analytics_h__
#define Analytics_h__


#include <queue>
#include <memory>


#include "macros/AppMacros.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "json/document.h"

NS_UBA_BEGIN

struct AnalyticsData
{
	int id;
	int category;
	int direction;
	std::string username;
	int gender;
	int ageGroup;
	float totalLength;
	float maxSpeed;
	int totalTime;
	float averageSpeed;
	float width;
	float height;
	float maxAccel;
	float avgAccel;
	float vecAngle;
	float startAccX;
	float startAccY;
	float startAccZ;
	float startAccVX;
	float startAccVY;
	float startAccVZ;
	float endAccX;
	float endAccY;
	float endAccZ;
	float endAccVX;
	float endAccVY;
	float endAccVZ;
};

class Analytics
{
public:
	static Analytics& getInstance();

	void loadCacheFromStorage();
	void addAnalyticsData(AnalyticsData analyticsData, bool cache = true);

	void oneSecondUpdate(float dt);
private:
	Analytics();

	void addAnalyticsData(std::unique_ptr<AnalyticsData> analyticsData, bool cache = true);
	void sendRequest(AnalyticsData* analyticsData);
	void cacheAnalyticsData(AnalyticsData* analyticsData);
	std::unique_ptr<AnalyticsData> createAnalyticsData(const rapidjson::Value& data);
	rapidjson::Value  getAnalyticsDataJson(AnalyticsData* analyticsData, rapidjson::Document& doc);

	void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);


	std::queue<std::unique_ptr<AnalyticsData>> _queue;

	float _timer;

	bool _sendingRequest;
};

NS_UBA_END

#endif // Analytics_h__
