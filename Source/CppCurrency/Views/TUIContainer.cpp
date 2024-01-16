#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Models/NNFileType.hpp>
#include <CppCurrency/Views/TToggle.hpp>
#include <CppCurrency/Views/TCurrencyTable.hpp>
#include <CppCurrency/Views/TIntervalModal.hpp>
#include <CppCurrency/Models/ACurrencyData.hpp>
#include <ftxui/component/component.hpp>
#include <magic_enum.hpp>
#include <format>

namespace curr {

static constexpr auto s_vFileTypes = magic_enum::enum_names<NFileType>();
static constexpr std::string_view s_sFileTypeToggle = "File type     ";
static constexpr std::string_view s_sCurrentTime 	= "Current time  ";
static constexpr std::string_view s_sIntervalInput 	= "Interval input";

TUIContainer::TUIContainer() {
	const auto interval = CreateInitIntervalInput();
	const auto toggle = CreateInitFileTypeToggle();
	const auto table = CreateInitCurrencyTable();
	m_pComponent = ftxui::Container::Vertical({toggle, interval, table});
	m_pComponent = ftxui::Renderer(m_pComponent, [toggle, interval, table]() {
		return ftxui::vbox(
			toggle->Render(),
			ftxui::separator(),
			RenderTime(),
			ftxui::separator(),
			interval->Render(),
			ftxui::separator(),
			table->Render()
		) | ftxui::borderDouble;
	});
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

ftxui::Component TUIContainer::CreateInitIntervalInput() {
	m_pIntervalInput = std::make_shared<TIntervalModal>();
	const auto interval = m_pIntervalInput->Component();
	return ftxui::Renderer(interval, [interval]() {
		return ftxui::hbox(
			ftxui::text(s_sIntervalInput.data()),
			ftxui::separator(),
			interval->Render()
		);
	});
}

}