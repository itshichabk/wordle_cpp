#pragma once

#include <curl/curl.h>
#include <string>

class HttpRequest
{
private:
	CURL* _curl;

	std::string _strUrl;
	std::string _strBuffer;

	bool _bSuccess;
	CURLcode _resultCode;

public:
	HttpRequest(std::string strUrl);
	~HttpRequest();

	std::string getUrl() const;
	std::string getBuffer() const;
	bool getSuccess() const;
	CURLcode getResultCode() const;

	void setUrl(std::string strUrl);

	bool perform();
};

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp);
