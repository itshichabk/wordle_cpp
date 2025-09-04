#include <gtest/gtest.h>
#include "HttpRequest.h"

TEST(network, HttpRequest_SimpleRequest)
{
	const std::string strUrl = "https://pastebin.com/raw/gYWggAN9";
	const std::string strMsg = "Hello GTest!";

	HttpRequest hr(strUrl);
	EXPECT_EQ(hr.getResultCode(), CURLcode::CURLE_OK);

	hr.perform();
	EXPECT_TRUE(hr.getSuccess());

	EXPECT_EQ(hr.getBuffer(), strMsg);
}

TEST(network, HttpRequest_RequestFail)
{
	const std::string strUrl = "http://noexist.itshichabk.io";

	HttpRequest hr(strUrl);
	EXPECT_EQ(hr.getResultCode(), CURLcode::CURLE_OK);

	hr.perform();
	EXPECT_FALSE(hr.getSuccess());
}
