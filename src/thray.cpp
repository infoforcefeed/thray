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

const char *Scraper::getAPIBlogUrlForUsername(const std::string &username, unsigned int page) {
	static char buf[256] = {0};
	memset(buf, '\0', sizeof(buf));

	unsigned int offset = 20*page;
	snprintf(buf, sizeof(buf), "https://api.tumblr.com/v2/blog/%s.tumblr.com/posts?api_key=%s&notes_info=true&reblog_info=true&filter=text&offset=%u\n",
			username.c_str(), API_KEY, offset);

	return buf;
}

static int fyckYou(char *data, size_t size, size_t nmemb, std::string *writerData) {
	writerData->append(data, size*nmemb);
	return size * nmemb;
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
	bool done = false;
	unsigned int page = 0;
	std::string responseBuffer;
	while (!done) {
		responseBuffer.clear();
		const char *APIBlogUrl = getAPIBlogUrlForUsername("david-meade", page++);
		makeRequest(APIBlogUrl, &responseBuffer);

		std::string error;
		Json resJson = Json::parse(responseBuffer, error)["response"];
		Json blogJson = resJson["blog"];
		Json::array postsJson = resJson["posts"].array_items();
		for(unsigned int i = 0; i < postsJson.size(); i++) {
			Json::object postObj = postsJson[i].object_items();
		}
		done = postsJson.size() < 20;
	};
}
