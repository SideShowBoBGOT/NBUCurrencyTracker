#ifndef CPPCURRENCY_TUICONTAINER_HPP
#define CPPCURRENCY_TUICONTAINER_HPP

#include <CppCurrency/Models/ACurrencyData.hpp>
#include "CppCurrency/Controllers/NNFileType.hpp"
#include <ftxui/component/component_base.hpp>
#include <atomic>

namespace curr {

class TCurrencyTable;
class TToggle;
class TIntervalModal;

class TUIContainer {
	public:
	TUIContainer();

	public:
	const ftxui::Component& Component() const;
	void UpdateCurrencyTable(AProvideResult&& result);

	protected:
	ftxui::Component CreateInitFileTypeToggle();
	ftxui::Component CreateInitCurrencyTable();
	ftxui::Component CreateChangeIntervalButton();
	static ftxui::Element RenderTime();

	protected:
	std::shared_ptr<TIntervalModal> m_pIntervalModal = nullptr;
	std::shared_ptr<TCurrencyTable> m_pCurrencyTable = nullptr;
	std::shared_ptr<TToggle> m_pFileTypeToggle = nullptr;
	ftxui::Component m_pComponent = nullptr;
};

}

#endif //CPPCURRENCY_TUICONTAINER_HPP
