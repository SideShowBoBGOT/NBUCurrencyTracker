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
	std::filesystem::path m_sLogFile;
	std::filesystem::path m_sOutputFile;
	NFileType m_xFileType = NFileType::XML;

};

}

#endif //CPPCURRENCY_TCONFIG_HPP
