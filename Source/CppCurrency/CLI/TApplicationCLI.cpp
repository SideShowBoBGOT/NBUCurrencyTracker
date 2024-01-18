#include <CppCurrency/CLI/TApplicationCLI.hpp>
#include <CppCurrency/Controllers/TConfig.hpp>
#include <CppCurrency/Controllers/TController.hpp>

namespace curr {

TApplicationCLI::TApplicationCLI() {
	add_option("--config,-c", m_sConfigPath, "Path to config file")
		->required(true)->check(CLI::ExistingFile);
	parse_complete_callback([this]() {
		const auto parentPath = m_sConfigPath.parent_path();
		if(not parentPath.empty()) {
			std::filesystem::current_path(parentPath);
			m_sConfigPath = m_sConfigPath.filename();
		}
		curr::TConfig::Instance().LoadFile(m_sConfigPath);
		curr::TController::Instance().Run();
	});
}

}