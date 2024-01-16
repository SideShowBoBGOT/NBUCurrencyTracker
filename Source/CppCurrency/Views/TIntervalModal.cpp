#include <CppCurrency/Views/TIntervalModal.hpp>
#include <CppCurrency/Helpers/NSHelpers.hpp>
#include <ftxui/component/component.hpp>

namespace curr {

static constexpr std::string_view s_sHours 		= "Hours  ";
static constexpr std::string_view s_sMinutes 	= "Minutes";
static constexpr std::string_view s_sSeconds 	= "Seconds";
static constexpr std::string_view s_sApply 		= "Apply  ";
static constexpr std::string_view s_sReturn 	= "Return ";
static constexpr auto s_uMaxInput = 10u;
static constexpr auto s_uHourSeconds = 3600u;
static constexpr auto s_uMinutesSeconds = 60u;

auto TIntervalModal::FilterDigits(std::string* s) {
	return [s](ftxui::Event event) {
		return event.is_character()
			and (
				not std::isdigit(event.character()[0])
				or s->size() > s_uMaxInput
			);
	};
}

TIntervalModal::TIntervalModal() {
	m_pHoursInput = ftxui::Input(&m_sHours, s_sHours.data()) | ftxui::CatchEvent(FilterDigits(&m_sHours));
	m_pMinutesInput = ftxui::Input(&m_sMinutes, s_sMinutes.data()) | ftxui::CatchEvent(FilterDigits(&m_sMinutes));
	m_pSecondsInput = ftxui::Input(&m_sSeconds, s_sSeconds.data()) | ftxui::CatchEvent(FilterDigits(&m_sSeconds));

	auto timeUnitsInput = ftxui::Container::Vertical({
		m_pHoursInput,
		m_pMinutesInput,
		m_pSecondsInput
	});

	timeUnitsInput = ftxui::Renderer(timeUnitsInput, [this]() {
		return ftxui::vbox(
			ftxui::hbox(ftxui::text(s_sHours.data()), ftxui::separator(), m_pHoursInput->Render()),
			ftxui::hbox(ftxui::text(s_sMinutes.data()), ftxui::separator(), m_pMinutesInput->Render()),
			ftxui::hbox(ftxui::text(s_sSeconds.data()), ftxui::separator(), m_pSecondsInput->Render())
		);
	});

	const auto applyButton = ftxui::Button(s_sApply.data(),
		[this]{ OnApplyButton(); }, ftxui::ButtonOption::Animated());
	const auto returnButton = ftxui::Button(s_sReturn.data(),
		[this]{ OnReturnButton(); }, ftxui::ButtonOption::Animated());

	auto buttons = ftxui::Container::Horizontal({applyButton, returnButton});
	buttons = ftxui::Renderer(buttons, [applyButton, returnButton] {
		return ftxui::hbox(
			applyButton->Render(),
			ftxui::separator(),
			returnButton->Render()
		);
	});

	auto component = ftxui::Container::Vertical({timeUnitsInput, buttons});
	component = ftxui::Renderer(component, [timeUnitsInput, buttons] {
		return ftxui::vbox(
			timeUnitsInput->Render(),
			ftxui::separator(),
			buttons->Render()
		);
	}) | ftxui::border;

	m_fClosure = ftxui::Modal(component, &m_bIsShow);
}

void TIntervalModal::Show(const bool isShow) {
	m_bIsShow = isShow;
}

const TIntervalModal::TModalClosure& TIntervalModal::ModalClosure() const {
	return m_fClosure;
}

void TIntervalModal::OnApplyButton() {
	const auto hours = std::stoll(m_sHours) * s_uHourSeconds;
	const auto minutes = std::stoll(m_sMinutes) * s_uMinutesSeconds;
	const auto seconds = std::stoll(m_sSeconds);
	const auto totalSeconds = std::chrono::seconds(hours + minutes + seconds);
	if(totalSeconds.count() == 0) {

		return;
	}


}

void TIntervalModal::OnReturnButton() {
	Show(false);
}



}
