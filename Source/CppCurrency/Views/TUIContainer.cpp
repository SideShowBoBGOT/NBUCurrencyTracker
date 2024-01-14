#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Models/NNFileType.hpp>
#include <CppCurrency/Views/NSToggle.hpp>
#include <CppCurrency/Views/TCurrencyTable.hpp>
#include <CppCurrency/Models/ACurrencyData.hpp>
#include <ftxui/component/component.hpp>
#include <magic_enum.hpp>
#include <format>

namespace curr {

static constexpr std::string_view s_FileTypeToggle = "File type";

TUIContainer::TUIContainer() {
	m_CurrencyTable = std::make_shared<TCurrencyTable>();
	const auto toggle = CreateFileTypeToggle();
	const auto table = m_CurrencyTable->Component();
	m_Component = ftxui::Container::Vertical({toggle, table});
	m_Component = ftxui::Renderer(m_Component, [toggle, table]() {
		auto tp = std::chrono::system_clock::now();
		tp = std::chrono::time_point_cast<std::chrono::seconds>(tp);
		auto stp = ftxui::text(std::format("{:%Y-%m-%d %H:%M:%S}", tp));
		stp = ftxui::hbox(ftxui::text("Current time"), ftxui::separator(), stp);
		return ftxui::vbox(
			toggle->Render(),
			ftxui::separator(),
			std::move(stp),
			ftxui::separator(),
			table->Render()) | ftxui::borderDouble;
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
	const auto toggle = NSToggle::New(variants);
	return ftxui::Renderer(toggle, [toggle]() {
		return ftxui::hbox(
			ftxui::text(s_FileTypeToggle.data()),
			ftxui::separator(), toggle->Render()
		);
	});;
}

void TUIContainer::UpdateCurrencyTable(AProvideResult&& result) {
	m_CurrencyTable->Update(std::move(result));
}

}