#include <CppCurrency/CLI/TApplicationCLI.hpp>
#include <CppCurrency/Controllers/TConfig.hpp>
#include <CppCurrency/Controllers/TController.hpp>

namespace curr {

TApplicationCLI::TApplicationCLI() {
	add_option("--config,-c", m_sConfigPath, "Config file")
		->required(true)->check(CLI::ExistingFile);
	parse_complete_callback([this]() {
		curr::TConfig::Instance().LoadFile(m_sConfigPath);
		curr::TController::Instance().Run();
	});
}

}