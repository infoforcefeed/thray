// vim: noet ts=4 sw=4
#include "thray.h"

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

void Scraper::scrape() {
	CURLcode res;
	std::string responseBuffer;
	const char *blogUrl = getBlogUrlForUsername("david-meade");
#ifdef __DARWIN_OS_X_HAUL_SATAN
	std::cout << "Fuc you" << endl;
#endif
	std::cout << "Heres the URL: " << blogUrl << endl;

	curl_easy_setopt(curl, CURLOPT_URL, blogUrl);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fyckYou);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		std::cout << "Could not fetch username's endpoint." << endl;
	}

	cout << responseBuffer << endl;

	curl_easy_reset(curl);
}
