#ifndef CPPCURRENCY_TUICONTAINER_HPP
#define CPPCURRENCY_TUICONTAINER_HPP

#include <CppCurrency/Models/ACurrencyData.hpp>
#include <CppCurrency/Models/NNFileType.hpp>
#include <ftxui/component/component_base.hpp>
#include <atomic>

namespace curr {

class TCurrencyTable;
class TToggle;

class TUIContainer {
	public:
	TUIContainer();

	public:
	NFileType FileType() const;
	const ftxui::Component& Component() const;
	void UpdateCurrencyTable(AProvideResult&& result);

	protected:
	ftxui::Component CreateInitFileTypeToggle();
	ftxui::Component CreateInitCurrencyTable();
	static ftxui::Element RenderTime();

	protected:
	std::shared_ptr<TCurrencyTable> m_pCurrencyTable = nullptr;
	std::shared_ptr<TToggle> m_pFileTypeToggle = nullptr;
	ftxui::Component m_pComponent = nullptr;
};

}

#endif //CPPCURRENCY_TUICONTAINER_HPP
