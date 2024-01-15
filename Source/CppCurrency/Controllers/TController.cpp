#include <CppCurrency/Controllers/TController.hpp>
#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Controllers/NSProvider.hpp>
#include <CppCurrency/Helpers/TIntervalClosure.hpp>

#include <spdlog/spdlog.h>
#include "spdlog/async.h"
#include <spdlog/sinks/basic_file_sink.h>

#include <thread>

namespace curr {

TController::TController()
	: m_pUIContainer{std::make_shared<TUIContainer>()} {}

void TController::Run() {
	spdlog::set_default_logger(
		spdlog::create_async<spdlog::sinks::basic_file_sink_mt>("ProvideLogger", "logs.txt")
	);
	auto clientThread = std::jthread([this]() { ClientThread(); });
	m_xScreen.Loop(m_pUIContainer->Component());
}

void TController::ClientThread() {
	using namespace std::chrono_literals;
	// provider lives long enough, so it is relatively safe to store the reference
	auto dataUpdator = TIntervalClosure(5s, [this]() {
		m_xScreen.Post([this, data=NSProvider::Do(m_pUIContainer->FileType())]() mutable {
			m_pUIContainer->UpdateCurrencyTable(std::move(data));
		});
		m_xScreen.PostEvent(ftxui::Event::Custom);
	});
	auto uiTimeUpdator = TIntervalClosure(1s, [this]() { m_xScreen.PostEvent(ftxui::Event::Custom); });
	while(true) {
		uiTimeUpdator.Update();
		dataUpdator.Update();
	}
}

}