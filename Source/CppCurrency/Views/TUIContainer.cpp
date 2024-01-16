#include <CppCurrency/Views/TUIContainer.hpp>
#include "CppCurrency/Controllers/NNFileType.hpp"
#include <CppCurrency/Views/TToggle.hpp>
#include <CppCurrency/Views/TCurrencyTable.hpp>
#include <CppCurrency/Views/TIntervalModal.hpp>
#include <CppCurrency/Models/ACurrencyData.hpp>
#include <ftxui/component/component.hpp>
#include <magic_enum.hpp>
#include <format>

namespace curr {

static constexpr auto s_vFileTypes = magic_enum::enum_names<NFileType>();
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

NFileType TUIContainer::FileType() const {
	return static_cast<NFileType>(m_pFileTypeToggle->SelectedVariant());
}

const ftxui::Component& TUIContainer::Component() const {
	return m_pComponent;
}

ftxui::Component TUIContainer::CreateInitFileTypeToggle() {
	m_pFileTypeToggle = std::make_shared<TToggle>(
		std::vector(s_vFileTypes.begin(), s_vFileTypes.end()));
	m_pFileTypeToggle->SelectActive(static_cast<int>(NFileType::JSON));
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