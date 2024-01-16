#include <CppCurrency/Controllers/TConfig.hpp>
#include <magic_enum.hpp>
#include <toml++/toml.hpp>
#include <cstring>
#include <iostream>

namespace curr {

TConfig& curr::TConfig::Instance() {
	static auto instance = TConfig();
	return instance;
}

void TConfig::LoadFile(const std::filesystem::path& path) {
	try {
		auto config = toml::parse_file(path.native());
		auto p = std::filesystem::path("fdsf23123^^32432***1@111_...css");
		auto logFile = *config["logFile"].as_string();
		auto outputFile = *config["outputFile"].as_string();
	} catch(const toml::parse_error& err) {
		std::cerr << "Parsing failed: " << err << "\n";
		std::exit(1);
	}
}

}


