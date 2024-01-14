#ifndef CPPCURRENCY_TUICONTAINER_HPP
#define CPPCURRENCY_TUICONTAINER_HPP

#include <CppCurrency/Models/ACurrencyData.hpp>
#include <CppCurrency/Models/NNFileType.hpp>
#include <ftxui/component/component_base.hpp>
#include <atomic>

namespace curr {

class TCurrencyTable;

class TUIContainer {
	public:
	TUIContainer();

	public:
	NFileType FileType() const;
	const ftxui::Component& Component() const;
	void UpdateCurrencyTable(AProvideResult&& result);

	protected:
	ftxui::Component CreateFileTypeToggle();

	protected:
	std::atomic_int32_t m_FileType = static_cast<int>(NFileType::XML);
	std::shared_ptr<TCurrencyTable> m_CurrencyTable = nullptr;
	ftxui::Component m_Component = nullptr;
};

}

#endif //CPPCURRENCY_TUICONTAINER_HPP
