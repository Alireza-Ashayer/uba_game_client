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
	std::string category;
	std::string direction;
	std::string username;
	std::string sex;
	float totalLength;
	float maxSpeed;
	float totalTime;
	float averageSpeed;
	float width;
	float height;
	float maxAcc;
	float avgAcc;
	float vecAngle;
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
