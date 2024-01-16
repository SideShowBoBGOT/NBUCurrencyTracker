#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Controllers/NNFileType.hpp>
#include <CppCurrency/Views/TToggle.hpp>
#include <CppCurrency/Views/TCurrencyTable.hpp>
#include <CppCurrency/Views/TIntervalModal.hpp>
#include <CppCurrency/Models/ACurrencyData.hpp>
#include <CppCurrency/Controllers/TController.hpp>
#include <ftxui/component/component.hpp>
#include <magic_enum.hpp>
#include <format>

namespace curr {

static constexpr std::string_view s_sFileTypeToggle = "File type      ";
static constexpr std::string_view s_sCurrentTime 	= "Current time   ";
static constexpr std::string_view s_sChangeInterval = "Change interval";

TUIContainer::TUIContainer() {
	const auto changeIntervalButton = CreateChangeIntervalButton();
	const auto toggle = CreateInitFileTypeToggle();
	const auto table = CreateInitCurrencyTable();
	m_pComponent = ftxui::Container::Vertical({toggle, changeIntervalButton, table});
	m_pComponent = ftxui::Renderer(m_pComponent, [toggle, changeIntervalButton, table]() {
		return ftxui::vbox(
			RenderTime(),
			ftxui::separator(),
			toggle->Render(),
			ftxui::separator(),
			changeIntervalButton->Render(),
			ftxui::separator(),
			table->Render()
		) | ftxui::borderDouble;
	}) | m_pIntervalModal->ModalClosure();
}

const ftxui::Component& TUIContainer::Component() const {
	return m_pComponent;
}

ftxui::Component TUIContainer::CreateInitFileTypeToggle() {
	auto variants = std::vector<std::pair<std::string_view, std::function<void()>>>();
	for(const auto& value : magic_enum::enum_values<NFileType>()) {
		const auto name = magic_enum::enum_name(value);
		const auto closure = [value] {
			TController::Instance().SendMessage(NMessages::FileTypeChanged(value));
		};
		variants.emplace_back(name, closure);
	}
	m_pFileTypeToggle = std::make_shared<TToggle>(variants);
	m_pFileTypeToggle->SelectActive(static_cast<int>(NFileType::XML));
	const auto toggle = m_pFileTypeToggle->Component();
	return ftxui::Renderer(toggle, [toggle]() {
		return ftxui::hbox(
			ftxui::text(s_sFileTypeToggle.data()),
			ftxui::separator(), toggle->Render()
		);
	});;
}

ftxui::Component TUIContainer::CreateInitCurrencyTable() {
	m_pCurrencyTable = std::make_shared<TCurrencyTable>();
	return m_pCurrencyTable->Component();
}

void TUIContainer::UpdateCurrencyTable(AProvideResult&& result) {
	m_pCurrencyTable->Update(std::move(result));
}

ftxui::Element TUIContainer::RenderTime() {
	const auto nanoTp = std::chrono::system_clock::now();
	auto tp = std::chrono::time_point_cast<std::chrono::seconds>(nanoTp);
	auto stp = ftxui::text(std::format("{:%F %T}", tp));
	return ftxui::hbox(ftxui::text(s_sCurrentTime.data()), ftxui::separator(), stp);
}

ftxui::Component TUIContainer::CreateChangeIntervalButton() {
	m_pIntervalModal = std::make_shared<TIntervalModal>();
	auto button = ftxui::Button(s_sChangeInterval.data(),
		[this] { m_pIntervalModal->Show(true); }, ftxui::ButtonOption::Animated());
	return ftxui::Renderer(button, [button]() {
		return ftxui::hbox(
			button->Render(),
			ftxui::separator(),
			ftxui::text("")
		);
	});
}

}