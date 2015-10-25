// vim: noet ts=4 sw=4
#include <iostream>

#include "thray.h"

using namespace std;
using namespace Thray;

int init() {
	curl_global_init(CURL_GLOBAL_DEFAULT);

	return 0;
}

int cleanup() {
	curl_global_cleanup();

	return 0;
}

int main(int argc, char *argv[]) {
	if (!init())
		return 1;

	Scraper scraper;

	scraper.scrape();

	cleanup();

	return 0;
}
