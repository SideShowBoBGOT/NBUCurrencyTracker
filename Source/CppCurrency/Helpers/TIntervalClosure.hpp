#ifndef CPPCURRENCY_TINTERVALCLOSURE_HPP
#define CPPCURRENCY_TINTERVALCLOSURE_HPP

#include <chrono>
#include <functional>

namespace curr {

class TIntervalClosure {
	public:
	TIntervalClosure(std::chrono::nanoseconds interval, const std::function<void()>& closure);

	public:
	void Update();

	protected:
	std::chrono::nanoseconds m_tInterval;
	std::chrono::system_clock::time_point m_tLastTime;
	std::function<void()> m_fClosure = nullptr;
};

}

#endif //CPPCURRENCY_TINTERVALCLOSURE_HPP
