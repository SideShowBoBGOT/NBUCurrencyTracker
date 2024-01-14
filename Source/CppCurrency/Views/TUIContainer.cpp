#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Models/NNFileType.hpp>
#include <CppCurrency/Views/NSToggle.hpp>
#include <CppCurrency/Views/TCurrencyDataView.hpp>
#include <CppCurrency/Views/TCurrencyTable.hpp>
#include <CppCurrency/Models/ACurrencyData.hpp>
#include <ftxui/component/component.hpp>
#include <magic_enum.hpp>

namespace curr {

TUIContainer::TUIContainer() {
	m_CurrencyTable = std::make_shared<TCurrencyTable>();
	m_Component = ftxui::Container::Vertical({
		CreateFileTypeToggle(),
		m_CurrencyTable->Component()
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

void TUIContainer::UpdateCurrencyTable(AProvideResult&& result) {
	m_CurrencyTable->Update(std::move(result));
}

}