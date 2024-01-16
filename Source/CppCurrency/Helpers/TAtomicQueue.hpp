#ifndef CPPCURRENCY_TATOMICQUEUE_HPP
#define CPPCURRENCY_TATOMICQUEUE_HPP

#include <optional>
#include <atomic>
#include <queue>

namespace curr {

template<typename T>
class TAtomicQueue {
	public:
	TAtomicQueue()=default;

	public:
	template<typename U>
	void Push(U&& value);
	std::optional<T> Pop();

	protected:
	std::atomic_flag m_xFlag;
	std::queue<T> m_qQueue;
};

// Probably, it should work based on RAII, but std::mutex is
// more expensive to lock than atomic variable
template<typename T>
template<typename U>
void TAtomicQueue<T>::Push(U&& value) {
	while(m_xFlag.test_and_set());
	m_qQueue.push(std::forward<U>(value));
	m_xFlag.clear();
}

template<typename T>
std::optional<T> TAtomicQueue<T>::Pop() {
	while(m_xFlag.test_and_set());
	if(m_qQueue.empty()) {
		m_xFlag.clear();
		return std::nullopt;
	}
	auto popped = std::move(m_qQueue.front());
	m_qQueue.pop();
	m_xFlag.clear();
	return popped;
}

}

#endif //CPPCURRENCY_TATOMICQUEUE_HPP
