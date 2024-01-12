#ifndef CPPCURRENCY_TCONSOLEUI_HPP
#define CPPCURRENCY_TCONSOLEUI_HPP

#include <CppCurrency/Views/NNFileType.hpp>

#include <ftxui/component/component_base.hpp>

namespace curr {

class TConsoleUI {
	public:
	TConsoleUI();

	public:
	void Render() const;

	protected:

	protected:
	NFileType m_FileType = NFileType::XML;
	std::shared_ptr<ftxui::ComponentBase> m_pElements = nullptr;
};

}

#endif //CPPCURRENCY_TCONSOLEUI_HPP
