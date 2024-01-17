#include <CppCurrency/Views/TIntervalModal.hpp>
#include <CppCurrency/Controllers/TController.hpp>
#include <CppCurrency/Controllers/TConfig.hpp>
#include <ftxui/component/component.hpp>

namespace curr {

static constexpr std::string_view s_sMillis 	= "Millis";
static constexpr std::string_view s_sApply 		= "Apply ";
static constexpr std::string_view s_sReturn 	= "Return";
static constexpr std::string_view s_sZero 		= "0";
static constexpr auto s_uMaxInput = 10u;

auto TIntervalModal::FilterDigits(std::string* s) {
	return [s](ftxui::Event event) {
		if(event == ftxui::Event::Return) return true;
		return event.is_character()
			and (
				not std::isdigit(event.character()[0])
				or s->size() > s_uMaxInput
			);
	};
}

TIntervalModal::TIntervalModal() {
	m_sMillis = std::to_string(TConfig::Instance().Interval().count());
	m_sPrevSeconds = m_sMillis;
	m_pSecondsInput = ftxui::Input(&m_sMillis, s_sZero.data()) | ftxui::CatchEvent(FilterDigits(&m_sMillis));

	auto timeUnitsInput = ftxui::Container::Vertical({
		m_pSecondsInput
	});

	timeUnitsInput = ftxui::Renderer(timeUnitsInput, [this]() {
		return ftxui::vbox(
			ftxui::hbox(ftxui::text(s_sMillis.data()), ftxui::separator(), m_pSecondsInput->Render())
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
	component = ftxui::Renderer(component, [this, timeUnitsInput, buttons] {
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
	m_sMillis = m_sPrevSeconds;
}

const TIntervalModal::TModalClosure& TIntervalModal::ModalClosure() const {
	return m_fClosure;
}

void TIntervalModal::OnApplyButton() {
	if(m_sMillis.empty()) {
		return;
	}
	const auto millis = std::chrono::milliseconds(std::stoll(m_sMillis));
	if(millis.count() == 0) {
		return;
	}
	m_sPrevSeconds = m_sMillis;
	TController::Instance().SendMessage(NMessages::IntervalChanged(millis));
	Show(false);
}

void TIntervalModal::OnReturnButton() {
	Show(false);
}



}
