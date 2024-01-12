#include <iostream>
#include <fstream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/table.hpp>

int main() {
//	trantor::Logger::setLogLevel(trantor::Logger::kTrace);
//	auto client = drogon::HttpClient::newHttpClient("https://bank.gov.ua");
//	auto req = drogon::HttpRequest::newHttpRequest();
//	req->setMethod(drogon::Get);
//	req->setPath("/NBUStatService/v1/statdirectory/exchangenew");
//	client->sendRequest(req, [](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
//		if(result != drogon::ReqResult::Ok) {
//			std::cout << "error while sending request to server! result: " << result << std::endl;
//			return;
//		}
//		std::ofstream("fff.txt") << response->getBody();
//	});
//	drogon::app().run();

	using namespace ftxui;

	auto table = Table({
		{"Version", "Marketing name", "Release date", "API level", "Runtime"},
		{"2.3", "Gingerbread", "February 9 2011", "10", "Dalvik 1.4.0"},
		{"4.0", "Ice Cream Sandwich", "October 19 2011", "15", "Dalvik"},
		{"4.1", "Jelly Bean", "July 9 2012", "16", "Dalvik"},
		{"4.2", "Jelly Bean", "November 13 2012", "17", "Dalvik"},
		{"4.3", "Jelly Bean", "July 24 2013", "18", "Dalvik"},
		{"4.4", "KitKat", "October 31 2013", "19", "Dalvik and ART"},
		{"5.0", "Lollipop", "November 3 2014", "21", "ART"},
		{"5.1", "Lollipop", "March 9 2015", "22", "ART"},
		{"6.0", "Marshmallow", "October 5 2015", "23", "ART"},
		{"7.0", "Nougat", "August 22 2016", "24", "ART"},
		{"7.1", "Nougat", "October 4 2016", "25", "ART"},
		{"8.0", "Oreo", "August 21 2017", "26", "ART"},
		{"8.1", "Oreo", "December 5 2017", "27", "ART"},
		{"9", "Pie", "August 6 2018", "28", "ART"},
		{"10", "10", "September 3 2019", "29", "ART"},
		{"11", "11", "September 8 2020", "30", "ART"},
	});

	table.SelectAll().Border(LIGHT);

	// Add border around the first column.
	table.SelectColumn(0).Border(LIGHT);

	// Make first row bold with a double border.
	table.SelectRow(0).Decorate(bold);
	table.SelectRow(0).SeparatorVertical(LIGHT);
	table.SelectRow(0).Border(DOUBLE);

	// Align right the "Release date" column.
	table.SelectColumn(2).DecorateCells(align_right);

	// Select row from the second to the last.
	auto content = table.SelectRows(1, -1);
	// Alternate in between 3 colors.
	content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
	content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
	content.DecorateCellsAlternateRow(color(Color::White), 3, 2);

	auto document = table.Render();



	auto screen = Screen::Create(Dimension::Fit(document));
	Render(screen, document);
	screen.Print();
	std::cout << std::endl;


	return 0;
}
