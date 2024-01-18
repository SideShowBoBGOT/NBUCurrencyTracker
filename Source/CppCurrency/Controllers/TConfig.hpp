#ifndef CPPCURRENCY_TCONFIG_HPP
#define CPPCURRENCY_TCONFIG_HPP

#include <CppCurrency/Controllers/NNFileType.hpp>
#include <filesystem>

namespace curr {

class TConfig {
	public:
	static TConfig& Instance();

	public:
	void LoadFile(const std::filesystem::path& path);

	protected:
	TConfig()=default;

	public:
	const std::string& LogFileName() const;
	const std::string& OutputFileName() const;
	std::chrono::milliseconds Interval() const;
	NFileType FileType() const;

	protected:
	std::string m_sLogFileName;
	std::string m_sOutputFileName;
	std::chrono::milliseconds m_tInterval = std::chrono::milliseconds(0);
	NFileType m_xFileType = NFileType::XML;
};

}

#endif //CPPCURRENCY_TCONFIG_HPP
