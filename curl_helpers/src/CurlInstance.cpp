#include "CurlInstance.h"

CurlInstance::CurlInstance()
{
	_curl = curl_easy_init();

	if (_curl)
	{
		_bInitSuccess = true;
	}
	else
	{
		_bInitSuccess = false;
	}
}

CurlInstance::~CurlInstance()
{
	if (_bInitSuccess)
	{
		curl_easy_cleanup(_curl);
	}
}

CURL* CurlInstance::getCurl()
{
	return _curl;
}

bool CurlInstance::getInitSuccess() const
{
	return _bInitSuccess;
}

CurlInstance* CurlInstance::getInstance()
{
	if (_curlInstance == nullptr)
	{
		_curlInstance = new CurlInstance();
	}

	return _curlInstance;
}
