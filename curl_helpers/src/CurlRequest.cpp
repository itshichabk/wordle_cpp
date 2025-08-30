#include "CurlRequest.h"
#include "CurlRequest.h"

CurlRequest::CurlRequest(std::string strUrl)
{
	_curlInstance = CurlInstance::getInstance();

	setUrl(strUrl);

	_strBuffer = "";
	_bSuccess = false;
	_resultCode = CURLcode::CURLE_FAILED_INIT;

	if (_curlInstance->getInitSuccess())
	{
		curl_easy_setopt(_curlInstance->getCurl(), CURLOPT_URL, strUrl.c_str());
		curl_easy_setopt(_curlInstance->getCurl(), CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(_curlInstance->getCurl(), CURLOPT_WRITEDATA, &_strBuffer);

		_resultCode = CURLcode::CURLE_OK;
	}
}

CurlRequest::~CurlRequest()
{
	_strUrl = "";
	_strBuffer = "";
	_bSuccess = false;
	_resultCode = CURLcode::CURLE_OK;

	if (_curlInstance->getInitSuccess())
	{
		curl_easy_setopt(_curlInstance->getCurl(), CURLOPT_URL, nullptr);
		curl_easy_setopt(_curlInstance->getCurl(), CURLOPT_WRITEFUNCTION, nullptr);
		curl_easy_setopt(_curlInstance->getCurl(), CURLOPT_WRITEDATA, nullptr);
	}
}

std::string CurlRequest::getUrl() const
{
	return _strUrl;
}

std::string CurlRequest::getBuffer() const
{
	return _strBuffer;
}

bool CurlRequest::getSuccess() const
{
	return _bSuccess;
}

CURLcode CurlRequest::getResultCode() const
{
	return _resultCode;
}

void CurlRequest::setUrl(std::string strUrl)
{
	// add url validation?
	_strUrl = strUrl;
}

bool CurlRequest::perform()
{
	_strBuffer = "";
	_bSuccess = false;

	bool bResult = false;

	if (_curlInstance->getInitSuccess())
	{
		_resultCode = curl_easy_perform(_curlInstance->getCurl());
		
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
