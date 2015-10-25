// vim: noet ts=4 sw=4
#pragma once
#include <cstring>
#include <curl/curl.h>
#include <iostream>
#include <libxml/HTMLparser.h>
#include <oauth.h>
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
			// Methods:
			const char *getBlogUrlForUsername(const std::string &username);
			unsigned int getPostCountForBlog(const std::string &json);
			std::vector<std::string> usernames;

			// Everything else:
			CURL *curl;
	};
}
