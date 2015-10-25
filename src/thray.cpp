// vim: noet ts=4 sw=4
#include "json11.hpp"
#include "thray.h"

using namespace json11;
using namespace std;
using namespace Thray;

Scraper::Scraper(): curl(nullptr) {
	curl = curl_easy_init();
}

Scraper::~Scraper() {
	curl_easy_cleanup(curl);
}

const char *Scraper::getBlogUrlForUsername(const std::string &username) {
	static char buf[256] = {0};
	memset(buf, '\0', sizeof(buf));

	snprintf(buf, sizeof(buf), "http://api.tumblr.com/v2/blog/%s.tumblr.com/info?api_key=" API_KEY,
			username.c_str());

	return buf;
}

static int fyckYou(char *data, size_t size, size_t nmemb, std::string *writerData) {
	writerData->append(data, size*nmemb);
	return size * nmemb;
}

unsigned int Scraper::getPostCountForBlog(const std::string &json) {
	std::string error;
	Json json1 = Json::parse(json, error);
	return json1["response"]["blog"]["posts"].int_value();
}

const char *Scraper::getPostPageUrl(const std::string url, unsigned int page) {
	static char buf[256] = {0};
	memset(buf, '\0', sizeof(buf));

	snprintf(buf, sizeof(buf), "%s/page/%u", url.c_str(), page);

	return buf;
}

void Scraper::makeRequest(const char *url, std::string *writeBugger) {
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fyckYou);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, writeBugger);

	curl_easy_perform(curl);
	curl_easy_reset(curl);
}

void Scraper::scrape() {
	std::string responseBuffer;
	const char *blogUrl = getBlogUrlForUsername("david-meade");

	makeRequest(blogUrl, &responseBuffer);

	unsigned int postCount = getPostCountForBlog(responseBuffer);
	unsigned int i = 1;
	while (postCount-- > 0) {
		const char *what = getPostPageUrl(blogUrl, i++);
		std::string reponseBugger;
		makeRequest(what, &reponseBugger);
		cout << reponseBugger;
	}
	cout << postCount << endl;
}

