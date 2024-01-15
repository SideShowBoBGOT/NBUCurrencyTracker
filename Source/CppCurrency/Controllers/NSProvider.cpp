#include <CppCurrency/Controllers/NSProvider.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <pugixml.hpp>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <magic_enum.hpp>

#include <cassert>
#include <fstream>

namespace curr::NSProvider {

static const std::string s_sNbuUrl = "https://bank.gov.ua";
static const std::string s_sXmlUrl = "/NBUStatService/v1/statdirectory/exchangenew";
static const std::string s_sJsonUrl = "/NBUStatService/v1/statdirectory/exchangenew?json";
static const std::string s_sJsonFileNotOpen = "JSON: File not open";
static const std::string s_sJsonParseFailed = "JSON: Parse failed";
static const std::string s_sR030 = "r030";
static const std::string s_sTxt = "txt";
static const std::string s_sRate = "rate";
static const std::string s_sCc = "cc";
static const std::string s_sExchangeDate = "exchangedate";
static const std::string s_sExchange = "exchange";
static const std::string s_sCurrency = "currency";
static const std::string s_sOutputFile = "output.txt";
static const std::string s_sLoggerName = "ProvideLogger";

static const std::string s_sSaveDataToReport = "SaveDataToReport: ";
static const std::string s_sReadJson = "ReadJson: ";
static const std::string s_sReadXml = "ReadXml: ";
static const std::string s_sLoggedJson = "Logged Json";
static const std::string s_sLoggedXML = "Logged XML";

using ASaveDataResult = std::variant<std::monostate, ACurrencyError>;

static std::shared_ptr<spdlog::logger> GetLogger() {
	return spdlog::get(s_sLoggerName);
}

static void LogFlush(const std::string& msg) {
	auto logger = GetLogger();
	logger->error(msg);
	logger->flush();
}

static ACurrencyError LogError(const std::string& msg) {
	LogFlush(msg);
	return msg;
}

static std::string_view URLByType(const curr::NFileType fileType) {
	switch(fileType) {
		case NFileType::JSON: return s_sJsonUrl;
		case NFileType::XML: return s_sXmlUrl;
		default: {
			assert(("Not implemented", false));
			return s_sXmlUrl;
		}
	}
}

static ASaveDataResult SaveDataToReport(const curr::NFileType fileType) {
	const auto url = URLByType(fileType);
	const auto result = httplib::Client(s_sNbuUrl.data()).Get(url.data());
	if(not result) {
		return LogError(s_sSaveDataToReport + to_string(result.error()));
	}
	if(result->status != httplib::StatusCode::OK_200) {
		const auto status = static_cast<httplib::StatusCode>(result->status);
		return LogError(s_sSaveDataToReport + std::string(magic_enum::enum_name(status)));
	}
	std::ofstream(s_sOutputFile) << result->body;
	return std::monostate{};
}

static AProvideResult ReadXml() {
	auto xmlDocument = pugi::xml_document();
	const auto parseResult = xmlDocument.load_file(s_sOutputFile.data());
	if(not parseResult) {
		return LogError(s_sReadXml + parseResult.description());
	}
	auto data = std::vector<ACurrencyData>();
	for(const auto& currency : xmlDocument.child(s_sExchange.data()).children(s_sCurrency.data())) {
		data.push_back({
			currency.child(s_sR030.data()).child_value(), currency.child(s_sTxt.data()).child_value(),
			currency.child(s_sRate.data()).child_value(), currency.child(s_sCc.data()).child_value(),
			currency.child(s_sExchangeDate.data()).child_value()});
	}
	LogFlush(s_sLoggedXML);
	return data;
}

static AProvideResult ReadJson() {
	auto document = std::ifstream(s_sOutputFile);
	if(not document.is_open()) {
		return LogError(s_sReadJson + s_sJsonFileNotOpen);
	}
	auto jsonData = nlohmann::json::parse(document, nullptr, false);
	if(jsonData.is_discarded()) {
		return LogError(s_sReadJson + s_sJsonParseFailed);
	}
	auto data = std::vector<ACurrencyData>();
	for(const auto& record : jsonData) {
		data.push_back({
			to_string(record[s_sR030]), record[s_sTxt],
			to_string(record[s_sRate]), record[s_sCc],
			record[s_sExchangeDate]});
	}
	LogFlush(s_sLoggedJson);
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


