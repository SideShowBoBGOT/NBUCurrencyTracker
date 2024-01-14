#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Models/NNFileType.hpp>
#include <CppCurrency/Views/NSToggle.hpp>
#include <CppCurrency/Views/TCurrencyDataView.hpp>
#include <CppCurrency/Models/SCurrencyData.hpp>
#include <ftxui/component/component.hpp>
#include <magic_enum.hpp>

namespace curr {

TUIContainer::TUIContainer() {
	const auto tableBody = ftxui::Container::Vertical({});

	const auto vContainer = ftxui::Container::Vertical({
		CreateFileTypeToggle(),
		CreateTableHeader(),
	});
}

NFileType TUIContainer::FileType() const {
	return static_cast<NFileType>(m_FileType.load());
}

const ftxui::Component& TUIContainer::Component() const {
	return m_Component;
}

ftxui::Component TUIContainer::CreateFileTypeToggle() {
	auto variants = std::vector<std::pair<std::string_view, std::function<void()>>>();
	for(const auto value : magic_enum::enum_values<NFileType>()) {
		const auto name = magic_enum::enum_name<NFileType>(value);
		variants.emplace_back(name, [this, value]() { m_FileType.store(value); });
	}
	return NSToggle::New(variants);
}

ftxui::Component TUIContainer::CreateTableHeader() const {
	return ftxui::Make<TCurrencyDataView>(
		SCurrencyData("Id", "Full name", "Rate", "Short name", "Exchange date"));
}

void TUIContainer::UpdateCurrencyTable(AProvideResult&& result) {
	if(std::holds_alternative<ACurrencyError>(result)) {
		m_TableErrorMessage = std::move(std::get<ACurrencyError>(result));
		return;
	}


}

}