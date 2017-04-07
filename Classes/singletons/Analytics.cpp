#include "Analytics.h"

#include "json/writer.h"
#include "cocos2d.h"
#include "network/HttpClient.h"

USING_NS_UBA;
USING_NS_CC;

using namespace cocos2d::network;

const int SEND_REQUEST_INTERVAL = 0;
const std::string ANALYTICS_CACHE_PATH = "analytics.json";
const std::string SERVER_URL = "http://150.216.57.54:80/api/Activities";

Analytics& Analytics::getInstance()
{
	static Analytics instance;
	return instance;
}


::Analytics::Analytics()
	:_timer(SEND_REQUEST_INTERVAL)
{

}


void uba::Analytics::loadCacheFromStorage()
{
	_queue.empty();

	Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(Analytics::oneSecondUpdate, this), this, 0.1, CC_REPEAT_FOREVER, 0, false, "analytics_cache_one_sec_update");


	std::string fullPath = FileUtils::getInstance()->getWritablePath().append(ANALYTICS_CACHE_PATH.c_str());
	try
	{
		if (!FileUtils::getInstance()->isFileExist(fullPath))
		{
			return;
		}

		unsigned char* pBuffer = NULL;
		ssize_t bufferSize = 0;
		pBuffer = FileUtils::getInstance()->getFileData(fullPath.c_str(), "r", &bufferSize);
		std::string jsonStr(pBuffer, pBuffer + bufferSize);


		rapidjson::Document d;
		d.Parse<0>(jsonStr.c_str());

		if (d.HasParseError())
		{
			throw;
		}

		if (d.GetType() == rapidjson::kArrayType)
		{
			for (unsigned int i = 0; i < d.Size(); i++)
			{
				auto& analyticsJson = d[i];

				if (analyticsJson.GetType() == rapidjson::kObjectType)
				{
					auto analytics = createAnalyticsData(analyticsJson);
					addAnalyticsData(std::move(analytics), false);
				}
			}
		}

	}
	catch (...)
	{
		FileUtils::getInstance()->removeFile(fullPath);
	}
}



void uba::Analytics::addAnalyticsData(AnalyticsData analyticsData, bool cache /*= true*/)
{
	try
	{
		auto data = std::unique_ptr<AnalyticsData>(new AnalyticsData(analyticsData));
		if (data)
		{
			data->id = _queue.size();
			addAnalyticsData(std::move(data), cache);
		}
	}
	catch (...)
	{

	}
}


void uba::Analytics::addAnalyticsData(std::unique_ptr<AnalyticsData> data, bool cache /*= true*/)
{
	if (cache)
	{
		cacheAnalyticsData(data.get());
	}

	_queue.push(std::move(data));
}




void Analytics::oneSecondUpdate(float dt)
{
	if (_timer < SEND_REQUEST_INTERVAL)
	{
		_timer += dt;
	}

	if (_timer >= SEND_REQUEST_INTERVAL && _queue.size() > 0)
	{
		_timer = 0;
        auto obj = _queue.front().get();
        if (obj) {
            sendRequest(_queue.front().get());
        }
        else
        {
            _queue.pop();
        }
		
	}
}

void uba::Analytics::sendRequest(AnalyticsData* analyticsData)
{
	rapidjson::Document doc;
	auto dataObject = getAnalyticsDataJson(analyticsData, doc);

	rapidjson::GenericStringBuffer<rapidjson::UTF8<>> buffer;
	rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<>>> writer(buffer);
	dataObject.Accept(writer);

	auto serialized = buffer.GetString();


	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setUrl(SERVER_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(Analytics::onHttpRequestCompleted, this));

	std::vector<std::string> headers;
	auto contentTypeHeader = "Content-Type: application/json";
	headers.push_back(contentTypeHeader);
	request->setHeaders(headers);



	request->setRequestData(serialized, strlen(serialized));
	request->setUserData(analyticsData);
	HttpClient::getInstance()->sendImmediate(request);
	request->release();

}

void uba::Analytics::cacheAnalyticsData(AnalyticsData* analyticsData)
{
	std::string fullPath = FileUtils::getInstance()->getWritablePath().append(ANALYTICS_CACHE_PATH.c_str());
	try
	{
		rapidjson::Document doc;
		if (FileUtils::getInstance()->isFileExist(fullPath))
		{
			unsigned char* pBuffer = NULL;
			ssize_t bufferSize = 0;
			pBuffer = FileUtils::getInstance()->getFileData(fullPath.c_str(), "r", &bufferSize);
			std::string jsonStr(pBuffer, pBuffer + bufferSize);


			doc.Parse<0>(jsonStr.c_str());

			if (doc.HasParseError())
			{
				throw;
			}
		}
		else
		{
			doc.SetArray();
		}

		

		if (doc.GetType() == rapidjson::kArrayType)
		{

			auto dataObject = getAnalyticsDataJson(analyticsData, doc);

			doc.PushBack(dataObject, doc.GetAllocator());


			rapidjson::GenericStringBuffer<rapidjson::UTF8<>> buffer;
			rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<>>> writer(buffer);
			doc.Accept(writer);

			auto serialized = buffer.GetString();
			FileUtils::getInstance()->writeStringToFile(serialized, fullPath);
		}

	}
	catch (...)
	{
		FileUtils::getInstance()->isFileExist(fullPath);
	}
}

void uba::Analytics::onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
	try
	{
		if (!response)
		{
			return;
		}

		if (response->isSucceed())
		{
			auto analyticsData = static_cast<AnalyticsData*>(response->getHttpRequest()->getUserData());
			auto id = analyticsData->id;
            
            if(_queue.size() != 0)
                _queue.pop();


			std::string fullPath = FileUtils::getInstance()->getWritablePath().append(ANALYTICS_CACHE_PATH.c_str());
			if (FileUtils::getInstance()->isFileExist(fullPath))
			{
				rapidjson::Document doc;
				unsigned char* pBuffer = NULL;
				ssize_t bufferSize = 0;
				pBuffer = FileUtils::getInstance()->getFileData(fullPath.c_str(), "r", &bufferSize);
				std::string jsonStr(pBuffer, pBuffer + bufferSize);


				doc.Parse<0>(jsonStr.c_str());

				if (doc.HasParseError())
				{
					throw;
				}



				auto it = doc.Begin();

				while (it != doc.End())
				{
					auto& obj = *it;

					auto jsonId = obj["id"].GetInt();

					if (jsonId == id)
					{
						it = doc.Erase(it);
					}
					else
					{
						++it;
					}
				}

				if (doc.Size() == 0)
				{
					FileUtils::getInstance()->removeFile(fullPath);
				}
				else
				{
					rapidjson::GenericStringBuffer<rapidjson::UTF8<>> buffer;
					rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<>>> writer(buffer);
					doc.Accept(writer);

					auto serialized = buffer.GetString();
					FileUtils::getInstance()->writeStringToFile(serialized, fullPath);
				}

			}

		}
	}
	catch (...)
	{
	}
}



std::unique_ptr<AnalyticsData> uba::Analytics::createAnalyticsData(const rapidjson::Value& data)
{
	auto result = std::unique_ptr<AnalyticsData>(new AnalyticsData());


	result->category = data["Category"].GetString();
	result->direction = data["direction"].GetString();
	result->parameter = data["parameter"].GetInt();
	result->id = data["id"].GetInt();



	return result;
}


rapidjson::Value uba::Analytics::getAnalyticsDataJson(AnalyticsData* analyticsData, rapidjson::Document& doc)
{
	rapidjson::Value dataObject;
	dataObject.SetObject();


	dataObject.AddMember("Category", rapidjson::StringRef(analyticsData->category.c_str(), analyticsData->category.length()), doc.GetAllocator());
	dataObject.AddMember("direction", rapidjson::StringRef(analyticsData->direction.c_str(), analyticsData->direction.length()), doc.GetAllocator());
	dataObject.AddMember("parameter", analyticsData->parameter, doc.GetAllocator());
	dataObject.AddMember("id", analyticsData->id, doc.GetAllocator());


	return dataObject;
}

