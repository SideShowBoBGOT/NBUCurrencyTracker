#ifndef CPPCURRENCY_TINTERVALMODAL_HPP
#define CPPCURRENCY_TINTERVALMODAL_HPP

#include <ftxui/component/component_base.hpp>

namespace curr {

class TIntervalModal {
	public:
	TIntervalModal();

	public:
	const ftxui::Component& Component() const;

	protected:
	static bool FilterDigits(ftxui::Event event);

	protected:
	ftxui::Component m_pComponent = nullptr;
	ftxui::Component m_pHoursInput = nullptr;
	ftxui::Component m_pMinutesInput = nullptr;
	ftxui::Component m_pSecondsInput = nullptr;

	protected:
	void OnApplyButton();
	void OnReturnButton();

	protected:
	std::string m_sHours;
	std::string m_sMinutes;
	std::string m_sSeconds;
};

}

#endif //CPPCURRENCY_TINTERVALMODAL_HPP
