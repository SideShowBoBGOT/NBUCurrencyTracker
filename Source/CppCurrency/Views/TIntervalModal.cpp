#include <CppCurrency/Views/TIntervalModal.hpp>
#include <CppCurrency/Helpers/NSHelpers.hpp>
#include <ftxui/component/component.hpp>

namespace curr {

static constexpr std::string_view s_sHours 		= "Hours  ";
static constexpr std::string_view s_sMinutes 	= "Minutes";
static constexpr std::string_view s_sSeconds 	= "Seconds";
static constexpr std::string_view s_sApply 		= "Apply";
static constexpr std::string_view s_sReturn 	= "Return";

TIntervalModal::TIntervalModal() {
	m_pHoursInput = ftxui::Input(&m_sHours, s_sHours.data()) | ftxui::CatchEvent(&FilterDigits);
	m_pMinutesInput = ftxui::Input(&m_sMinutes, s_sMinutes.data()) | ftxui::CatchEvent(&FilterDigits);
	m_pSecondsInput = ftxui::Input(&m_sSeconds, s_sSeconds.data()) | ftxui::CatchEvent(&FilterDigits);

	m_pComponent = ftxui::Container::Vertical({
		m_pHoursInput,
		m_pMinutesInput,
		m_pSecondsInput
	});

	m_pComponent = ftxui::Renderer(m_pComponent, [this]() {
		return ftxui::vbox(
			ftxui::hbox(ftxui::text(s_sHours.data()), ftxui::separator(), m_pHoursInput->Render()),
			ftxui::hbox(ftxui::text(s_sMinutes.data()), ftxui::separator(), m_pMinutesInput->Render()),
			ftxui::hbox(ftxui::text(s_sSeconds.data()), ftxui::separator(), m_pSecondsInput->Render())
		);
	});

	m_pComponent = ftxui::Container::Vertical({
		m_pComponent,
		ftxui::Container::Horizontal({
			ftxui::Button()
		})
	});




}

const ftxui::Component& TIntervalModal::Component() const {
	return m_pComponent;
}

bool TIntervalModal::FilterDigits(ftxui::Event event) {
	return event.is_character() and not std::isdigit(event.character()[0]);
}

void TIntervalModal::OnApplyButton() {

}

void TIntervalModal::OnReturnButton() {

}

}
