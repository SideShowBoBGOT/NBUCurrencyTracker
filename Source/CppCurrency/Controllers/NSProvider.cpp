#include <CppCurrency/Controllers/NSProvider.hpp>

#include <pugixml.hpp>
#include <httplib.h>
#include <magic_enum.hpp>

#include <cassert>
#include <fstream>

namespace curr::NSProvider {

static constexpr std::string_view s_NbuUrl = "https://bank.gov.ua";
static constexpr std::string_view s_XmlUrl = "/NBUStatService/v1/statdirectory/exchangenew";
static constexpr std::string_view s_JsonUrl = "/NBUStatService/v1/statdirectory/exchangenew?json";
static constexpr std::string_view s_OutputFile = "output.txt";

using ASaveDataResult = std::variant<std::monostate, ACurrencyError>;

std::string_view URLByType(const curr::NFileType fileType) {
	switch(fileType) {
		case NFileType::JSON: return s_JsonUrl;
		case NFileType::XML: return s_XmlUrl;
		default: {
			assert(("Not implemented", false));
			return s_XmlUrl;
		}
	}
}

ASaveDataResult SaveDataToReport(const curr::NFileType fileType) {
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
	std::ofstream(s_OutputFile.data()) << result->body;
	return std::monostate{};
}

AProvideResult ReadXml() {
	auto xmlDocument = pugi::xml_document();
	const auto parseResult = xmlDocument.load_file(s_OutputFile.data());
	// TODO: log error
	if(not parseResult) return parseResult.description();
	auto data = std::vector<SCurrencyData>();
	for(const auto& currency : xmlDocument.child("exchange").children("currency")) {
		data.emplace_back(
			currency.child("r030").child_value(),
			currency.child("txt").child_value(),
			currency.child("rate").child_value(),
			currency.child("cc").child_value(),
			currency.child("exchangedate").child_value()
		);
	}
	return data;
}

AProvideResult ReadJson() {
	return ACurrencyError("JSON parse not implemented");
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


