#include <CppCurrency/Controllers/TConfig.hpp>
#include <magic_enum.hpp>
#include <toml++/toml.hpp>
#include <boost/filesystem.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <iostream>
#include <limits>

template <>
struct magic_enum::customize::enum_range<toml::node_type> {
	static constexpr int min = std::numeric_limits<uint8_t>::min();
	static constexpr int max = std::numeric_limits<uint8_t>::max();
};

namespace curr {

static constexpr std::string_view s_sLogFileName = "logFileName";
static constexpr std::string_view s_sOutputFileName = "outputFileName";
static constexpr std::string_view s_sIntervalMillis = "intervalMillis";
static constexpr std::string_view s_sFileType = "fileType";
static constexpr auto s_vFileTypesNames = magic_enum::enum_names<NFileType>();
static constexpr auto s_vFileTypesValues = magic_enum::enum_values<NFileType>();

TConfig& curr::TConfig::Instance() {
	static auto instance = TConfig();
	return instance;
}

static void CheckContainstKey(const toml::table& table, const std::string_view& key, const toml::node_type type) {
	if(not table[key]) {
		std::cerr << "Table does not contain key: " << key << "\n";
		std::exit(1);
	}
	if(table[key].type() != type) {
		std::cerr << fmt::format("Table key \"{}\" does not match type of \"{}\"\n",
			key, magic_enum::enum_name(type));
		std::exit(1);
	}
}

static std::string CheckFileName(const toml::table& tableView, const std::string_view& key) {
	CheckContainstKey(tableView, key, toml::node_type::string);
	const auto& fileName = tableView[key].ref<std::string>();
	if(not boost::filesystem::portable_file_name(fileName)) {
		std::cerr << fmt::format("File name \"{}\" is not viable file name\n", fileName);
		std::exit(1);
	}
	return fileName;
}

static int64_t CheckTimeUnit(const toml::table& tableView, const std::string_view& key) {
	CheckContainstKey(tableView, key, toml::node_type::integer);
	const auto& unit = tableView[key].ref<int64_t>();
	if(unit <= 0) {
		std::cerr << fmt::format("Millis is less or equal zero");
		std::exit(1);
	}
	return unit;
}

static NFileType CheckFileType(const toml::table& tableView) {
	CheckContainstKey(tableView, s_sFileType, toml::node_type::string);
	const auto& fileType = tableView[s_sFileType].ref<std::string>();
	const auto it = std::find(s_vFileTypesNames.begin(), s_vFileTypesNames.end(), fileType.data());
	if(it == s_vFileTypesNames.end()) {
		std::cerr << fmt::format("No such file type: {}. Possible values are {::}.",
			fileType, s_vFileTypesNames);
		std::exit(1);
	}
	return s_vFileTypesValues[std::distance(s_vFileTypesNames.begin(), it)];
}

void TConfig::LoadFile(const std::filesystem::path& path) {
	try {
		auto config = toml::parse_file(path.native());
		m_sLogFileName = CheckFileName(config, s_sLogFileName);
		m_sOutputFileName = CheckFileName(config, s_sOutputFileName);
		const auto millis = CheckTimeUnit(config, s_sIntervalMillis);
		m_tInterval = std::chrono::milliseconds(millis);
		m_xFileType = CheckFileType(config);
	} catch(const toml::parse_error& err) {
		std::cerr << "Parsing failed: " << err << "\n";
		std::exit(1);
	}
}

const std::string& TConfig::LogFileName() const {
	return m_sLogFileName;
}

const std::string& TConfig::OutputFileName() const {
	return m_sOutputFileName;
}

std::chrono::milliseconds TConfig::Interval() const {
	return m_tInterval;
}

NFileType TConfig::FileType() const {
	return m_xFileType;
}

}


