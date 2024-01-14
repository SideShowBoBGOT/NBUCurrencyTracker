#include <CppCurrency/Controllers/TController.hpp>
#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Controllers/NSProvider.hpp>
#include <CppCurrency/Helpers/TIntervalClosure.hpp>
#include <thread>

namespace curr {

static constexpr std::string_view s_OutputFileName = "fff.txt";

TController::TController()
	: m_UIContainer{std::make_shared<TUIContainer>()} {}

void TController::Run() {
	auto clientThread = std::jthread([this]() { ClientThread(); });
	m_Screen.Loop(m_UIContainer->Component());
}

void TController::ClientThread() {
	using namespace std::chrono_literals;
	auto uiTimeUpdator = TIntervalClosure(1s, [this]() { m_Screen.PostEvent(ftxui::Event::Custom); });
	auto dataUpdator = TIntervalClosure(5s, [this]() {
		m_Screen.Post([this, data=NSProvider::Do(m_UIContainer->FileType())]() mutable {
			m_UIContainer->UpdateCurrencyTable(std::move(data));
		});
		m_Screen.PostEvent(ftxui::Event::Custom);
	});
	while(true) {
		uiTimeUpdator.Update();
		dataUpdator.Update();
	}
}

}