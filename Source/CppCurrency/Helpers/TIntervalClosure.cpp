#include <CppCurrency/Helpers/TIntervalClosure.hpp>

namespace curr {

TIntervalClosure::TIntervalClosure(std::chrono::seconds interval, const std::function<void()>& closure)
	: Interval{interval}, m_tLastTime{std::chrono::system_clock::now()}, m_fClosure{closure} {}

void TIntervalClosure::Update() {
	const auto currentTime = std::chrono::system_clock::now();
	if(currentTime - m_tLastTime > Interval) {
		m_fClosure();
		m_tLastTime = currentTime;
	}
}

}
