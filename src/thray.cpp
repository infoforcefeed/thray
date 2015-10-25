// vim: noet ts=4 sw=4
#include "thray.h"

using namespace std;
using namespace Thray;

Scraper::Scraper() {
}

const char *Scraper::getBlogUrlForUsername(const std::string &username) {
	static char buf[256] = {0};
	memset(buf, '\0', sizeof(buf));

	snprintf(buf, sizeof(buf), "http://api.tumblr.com/v2/blog/%s.tumblr.com/info?api_key=" API_KEY,
			username.c_str());

	return buf;
}

void Scraper::scrape() {
	std::string blogUrl(getBlogUrlForUsername("david-meade"));

#ifdef __DARWIN_OS_X_HAUL_SATAN
	std::cout << "Fuc you" << endl;
#endif
	std::cout << "Heres the URL: " << blogUrl << endl;
}

