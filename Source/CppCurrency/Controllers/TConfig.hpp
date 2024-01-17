#ifndef CPPCURRENCY_TCONFIG_HPP
#define CPPCURRENCY_TCONFIG_HPP

#include <filesystem>
#include <CppCurrency/Controllers/NNFileType.hpp>

namespace curr {

class TConfig {
	public:
	static TConfig& Instance();

	public:
	void LoadFile(const std::filesystem::path& path);

	protected:
	TConfig()=default;

	protected:
	std::string m_sLogFileName;
	std::string m_sOutputFileName;
	std::chrono::seconds m_tInterval = std::chrono::seconds(0);
	NFileType m_xFileType = NFileType::XML;
};

}

#endif //CPPCURRENCY_TCONFIG_HPP
