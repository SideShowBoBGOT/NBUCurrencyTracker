#include <CppCurrency/Helpers/TIntervalClosure.hpp>

namespace curr {

TIntervalClosure::TIntervalClosure(std::chrono::nanoseconds interval, const std::function<void()>& closure)
	: m_tInterval{interval}, m_tLastTime{std::chrono::system_clock::now()}, m_fClosure{closure} {}

void TIntervalClosure::Update() {
	const auto currentTime = std::chrono::system_clock::now();
	if(currentTime - m_tLastTime > m_tInterval) {
		m_fClosure();
		m_tLastTime = currentTime;
	}
}

}
