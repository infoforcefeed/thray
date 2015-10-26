// vim: noet ts=4 sw=4
#pragma once
#include <cstring>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>

#define API_KEY "IkJtqSbg6Nd3OBnUdaGl9YWE3ocupygJcnPebHRou8eFbd4RUv"

namespace Thray {

	class Scraper {
		public:
			Scraper();
			~Scraper();
			void scrape();
		private:

			void makeRequest(const char *url, std::string *writeBugger);
			// Methods:
			const char *getAPIBlogUrlForUsername(const std::string &username, unsigned int page);
			std::vector<std::string> usernames;

			// Everything else:
			CURL *curl;
	};
}
