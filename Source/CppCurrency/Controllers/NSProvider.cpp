#include <CppCurrency/Controllers/NSProvider.hpp>

#include <pugixml.hpp>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <magic_enum.hpp>

#include <cassert>
#include <fstream>

namespace curr::NSProvider {

static constexpr std::string_view s_NbuUrl = "https://bank.gov.ua";
static constexpr std::string_view s_XmlUrl = "/NBUStatService/v1/statdirectory/exchangenew";
static constexpr std::string_view s_JsonUrl = "/NBUStatService/v1/statdirectory/exchangenew?json";
static constexpr std::string_view s_JsonFileNotOpen = "JSON: File not open";
static constexpr std::string_view s_JsonParseFailed = "JSON: Parse failed";
static const std::string s_OutputFile = "output.txt";

using ASaveDataResult = std::variant<std::monostate, ACurrencyError>;

static std::string_view URLByType(const curr::NFileType fileType) {
	switch(fileType) {
		case NFileType::JSON: return s_JsonUrl;
		case NFileType::XML: return s_XmlUrl;
		default: {
			assert(("Not implemented", false));
			return s_XmlUrl;
		}
	}
}

static ASaveDataResult SaveDataToReport(const curr::NFileType fileType) {
	const auto url = URLByType(fileType);
	const auto result = httplib::Client(s_NbuUrl.data()).Get(url.data());
	// TODO: log error
	if(not result) {
		return to_string(result.error());
	}
	if(result->status != httplib::StatusCode::OK_200) {
		const auto status = static_cast<httplib::StatusCode>(result->status);
		return magic_enum::enum_name(status).data();
	}
	std::ofstream(s_OutputFile) << result->body;
	return std::monostate{};
}

static AProvideResult ReadXml() {
	auto xmlDocument = pugi::xml_document();
	const auto parseResult = xmlDocument.load_file(s_OutputFile.data());
	// TODO: log error
	if(not parseResult) return parseResult.description();
	auto data = std::vector<ACurrencyData>();
	for(const auto& currency : xmlDocument.child("exchange").children("currency")) {
		data.push_back({
			currency.child("r030").child_value(), currency.child("txt").child_value(),
			currency.child("rate").child_value(), currency.child("cc").child_value(),
			currency.child("exchangedate").child_value()});
	}
	return data;
}

static AProvideResult ReadJson() {
	auto document = std::ifstream(s_OutputFile);
	if(not document.is_open()) {
		return s_JsonFileNotOpen.data();
	}
	auto jsonData = nlohmann::json::parse(document, nullptr, false);
	if(jsonData.is_discarded()) {
		return s_JsonParseFailed.data();
	}
	auto data = std::vector<ACurrencyData>();
	for(const auto& record : jsonData) {
		data.push_back({record["r030"], record["txt"],record["rate"],
			record["cc"], record["exchangedate"]});
	}
	return data;
}

AProvideResult Do(const curr::NFileType fileType) {
	auto result = SaveDataToReport(fileType);
	if(std::holds_alternative<ACurrencyError>(result)) {
		return std::get<ACurrencyError>(result);
	}
	switch(fileType) {
		case NFileType::JSON: return ReadJson();
		case NFileType::XML: return ReadXml();
		default: {
			assert(("Not implemented", false));
			return {};
		}
	}
}

}


