#ifndef CPPCURRENCY_TINTERVALMODAL_HPP
#define CPPCURRENCY_TINTERVALMODAL_HPP

#include <ftxui/component/component_base.hpp>

namespace curr {

class TIntervalModal {
	public:
	TIntervalModal();

	public:
	using TModalClosure = std::function<ftxui::Component(ftxui::Component)>;
	const TModalClosure& ModalClosure() const;
	void Show(const bool isShow);

	protected:
	static auto FilterDigits(std::string* s);

	protected:
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

	protected:

	protected:
	bool m_bIsShow = false;
	TModalClosure m_fClosure = nullptr;
};

}

#endif //CPPCURRENCY_TINTERVALMODAL_HPP
