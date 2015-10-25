// vim: noet ts=4 sw=4
#pragma once
#include <cstring>
#include <curl/curl.h>
#include <iostream>
#include <oauth.h>
#include <string>
#include <vector>

#define API_KEY "IkJtqSbg6Nd3OBnUdaGl9YWE3ocupygJcnPebHRou8eFbd4RUv"

namespace Thray {

	class Scraper {
		public:
			Scraper();
			void scrape();
		private:
			const char *getBlogUrlForUsername(const std::string &username);
			std::vector<std::string> usernames;
	};
}
