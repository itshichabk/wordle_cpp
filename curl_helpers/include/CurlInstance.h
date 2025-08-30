#pragma once

#include <curl/curl.h>

class CurlInstance
{
private:
	static CurlInstance* _curlInstance;

	CURL* _curl;
	bool _bInitSuccess;

	CurlInstance();
	~CurlInstance();

public:
	CurlInstance(CurlInstance const&) = delete;
	void operator=(CurlInstance const&) = delete;

	CURL* getCurl();
	bool getInitSuccess() const;

	static CurlInstance* getInstance();
};
