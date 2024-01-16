#ifndef CPPCURRENCY_TAPPLICATIONCLI_HPP
#define CPPCURRENCY_TAPPLICATIONCLI_HPP

#include <CLI/CLI.hpp>

namespace curr {

class TApplicationCLI : public CLI::App {
	public:
	TApplicationCLI();

	public:
	std::filesystem::path m_sConfigPath;
};

}

#endif //CPPCURRENCY_TAPPLICATIONCLI_HPP
