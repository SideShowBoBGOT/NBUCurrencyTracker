#include <CppCurrency/Controllers/TController.hpp>
#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Controllers/NSProvider.hpp>
#include <thread>

namespace curr {

static constexpr std::string_view s_OutputFileName = "fff.txt";

TController::TController()
	: m_UIContainer{std::make_unique<TUIContainer>()} {}

void TController::Run() {
	auto clientThread = std::jthread([this]() { ClientThread(); });
	m_Screen.Loop(m_UIContainer->Component());
}

void TController::ClientThread() {
	while(true) {
		m_Screen.Post([this, data=NSProvider::Do(m_UIContainer->FileType())]() mutable {
			m_UIContainer->UpdateCurrencyTable(std::move(data));
		});
		while(true);
	}
}

}