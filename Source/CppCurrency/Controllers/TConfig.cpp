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
static constexpr std::string_view s_sInterval = "interval";
static constexpr std::string_view s_sHours = "hours";
static constexpr std::string_view s_sMinutes = "minutes";
static constexpr std::string_view s_sSeconds = "seconds";
static constexpr int64_t s_iHourSeconds = 3600;
static constexpr int64_t s_iMinuteSeconds = 60;
static constexpr std::string_view s_sFileType = "fileType";
static constexpr auto s_vFileTypesNames = magic_enum::enum_names<NFileType>();
static constexpr auto s_vFileTypesValues = magic_enum::enum_values<NFileType>();

TConfig& curr::TConfig::Instance() {
	static auto instance = TConfig();
	return instance;
}

template<typename T>
static void CheckContainstKey(const T& tableView, const std::string_view& key, const toml::node_type type) {
	if(not tableView[key]) {
		std::cerr << "Table does not contain key: " << key << "\n";
		std::exit(1);
	}
	if(tableView[key].type() != type) {
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

static int64_t CheckTimeUnit(const toml::node_view<toml::node>& tableView, const std::string_view& key) {
	CheckContainstKey(tableView, key, toml::node_type::integer);
	const auto& unit = tableView[key].ref<int64_t>();
	constexpr auto maxUint32 = std::numeric_limits<uint32_t>::max();
	if(unit < 0 or unit >= maxUint32) {
		std::cerr << fmt::format("Time unit is not in range of [{}; {}]", 0, maxUint32);
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
	return s_vFileTypesValues[std::distance(it, s_vFileTypesNames.end())];
}

void TConfig::LoadFile(const std::filesystem::path& path) {
	try {
		auto config = toml::parse_file(path.native());
		m_sLogFileName = CheckFileName(config, s_sLogFileName);
		m_sOutputFileName = CheckFileName(config, s_sOutputFileName);
		CheckContainstKey(config, s_sInterval, toml::node_type::table);
		const auto hours = CheckTimeUnit(config[s_sInterval], s_sHours);
		const auto minutes = CheckTimeUnit(config[s_sInterval], s_sMinutes);
		const auto seconds = CheckTimeUnit(config[s_sInterval], s_sSeconds);
		const auto totalInterval = hours * s_iHourSeconds + minutes * s_iMinuteSeconds + seconds;
		m_tInterval = std::chrono::seconds(totalInterval);
		m_xFileType = CheckFileType(config);
	} catch(const toml::parse_error& err) {
		std::cerr << "Parsing failed: " << err << "\n";
		std::exit(1);
	}
}

}


