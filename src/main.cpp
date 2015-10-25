// vim: noet ts=4 sw=4
#include <iostream>

#include "thray.h"

using namespace std;
using namespace Thray;

bool init() {
	curl_global_init(CURL_GLOBAL_DEFAULT);

	return true;
}

bool cleanup() {
	curl_global_cleanup();

	return true;
}

int main(int argc, char *argv[]) {
	if (!init())
		return 1;

	Scraper scraper;

	scraper.scrape();

	cleanup();

	return 0;
}
