#include <CppCurrency/Helpers/TIntervalClosure.hpp>

namespace curr {

TIntervalClosure::TIntervalClosure(std::chrono::nanoseconds interval, const std::function<void()>& closure)
	: m_Interval{interval}, m_LastTime{std::chrono::system_clock::now()}, m_Closure{closure} {}

void TIntervalClosure::Update() {
	const auto currentTime = std::chrono::system_clock::now();
	if(currentTime - m_LastTime > m_Interval) {
		m_Closure();
		m_LastTime = currentTime;
	}
}

}
