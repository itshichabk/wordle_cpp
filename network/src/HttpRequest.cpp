#include "HttpRequest.h"

HttpRequest::HttpRequest(std::string strUrl)
{
	_curl = curl_easy_init();

	if (_curl)
	{
		curl_easy_setopt(_curl, CURLOPT_URL, strUrl.c_str());
		curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_strBuffer);

		_resultCode = CURLcode::CURLE_OK;
	}
	else
	{
		_resultCode = CURLcode::CURLE_FAILED_INIT;
	}

	setUrl(strUrl);

	_strBuffer = "";
	_bSuccess = false;
}

HttpRequest::~HttpRequest()
{
	curl_easy_cleanup(_curl);
	_curl = nullptr;

	_strUrl = "";
	_strBuffer = "";
	_bSuccess = false;
}

std::string HttpRequest::getUrl() const
{
	return _strUrl;
}

std::string HttpRequest::getBuffer() const
{
	return _strBuffer;
}

bool HttpRequest::getSuccess() const
{
	return _bSuccess;
}

CURLcode HttpRequest::getResultCode() const
{
	return _resultCode;
}

void HttpRequest::setUrl(std::string strUrl)
{
	// add url validation?
	_strUrl = strUrl;
}

bool HttpRequest::perform()
{
	_strBuffer = "";
	_bSuccess = false;

	bool bResult = false;

	if (_curl)
	{
		_resultCode = curl_easy_perform(_curl);
		
		if (_resultCode == CURLE_OK)
		{
			bResult = true;
		}
		else
		{
			bResult = false;
		}
	}
	else
	{
		bResult = false;
	}

	_bSuccess = bResult;
	return bResult;
}

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}
