#ifndef CPPCURRENCY_TUICONTAINER_HPP
#define CPPCURRENCY_TUICONTAINER_HPP

#include <CppCurrency/Models/SCurrencyData.hpp>
#include <CppCurrency/Models/NNFileType.hpp>
#include <ftxui/component/component_base.hpp>
#include <atomic>

namespace curr {

class TUIContainer {
	public:
	TUIContainer();

	public:
	NFileType FileType() const;
	const ftxui::Component& Component() const;
	void UpdateCurrencyTable(AProvideResult&& result);

	protected:
	ftxui::Component CreateFileTypeToggle();
	ftxui::Component CreateTableHeader() const;

	protected:
	std::atomic_int32_t m_FileType = static_cast<int>(NFileType::XML);
	ftxui::Component m_Component = nullptr;
	ACurrencyError m_TableErrorMessage;
};

}

#endif //CPPCURRENCY_TUICONTAINER_HPP
