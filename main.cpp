#include <iostream>
#include <fstream>
#include <drogon/drogon.h>

int main() {
	trantor::Logger::setLogLevel(trantor::Logger::kTrace);
	auto client = drogon::HttpClient::newHttpClient("https://bank.gov.ua");
	auto req = drogon::HttpRequest::newHttpRequest();
	req->setMethod(drogon::Get);
	req->setPath("/NBUStatService/v1/statdirectory/exchangenew");
	client->sendRequest(req, [](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
		if(result != drogon::ReqResult::Ok) {
			std::cout << "error while sending request to server! result: " << result << std::endl;
			return;
		}
		std::ofstream("fff.txt") << response->getBody();
	});
	drogon::app().run();
	return 0;
}
