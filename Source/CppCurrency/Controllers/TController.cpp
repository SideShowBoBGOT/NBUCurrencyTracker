#include <CppCurrency/Controllers/TController.hpp>
#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Controllers/NSProvider.hpp>
#include <CppCurrency/Helpers/NSHelpers.hpp>
#include <CppCurrency/Helpers/TIntervalClosure.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <thread>

namespace curr {

TController::TController() {
	const auto logger = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>("ProvideLogger", "logs.txt");
	spdlog::set_default_logger(logger);
	InitTableUpdator(std::chrono::seconds(5));
	InitUiTimeUpdator();
	m_pUIContainer = std::make_shared<TUIContainer>();
}

void TController::Run() {
	auto clientThread = std::jthread([this]() { ClientThread(); });
	m_xScreen.Loop(m_pUIContainer->Component());
}

void TController::ClientThread() {
	while(true) {
		ProcessMessages();
		m_pUiTimeUpdator->Update();
		m_pTableUpdator->Update();
	}
}

void TController::ProcessMessages() {
	const auto messageOpt = m_qMessages.Pop();
	if(not messageOpt) return;
	const auto& message = messageOpt.value();
	switch(message.index()) {
		case NSHelpers::VariantIndex<NMessages::Type, NMessages::IntervalChanged>(): {
			m_pTableUpdator->Interval = std::get<NMessages::IntervalChanged>(message).Seconds;
			break;
		}
		case NSHelpers::VariantIndex<NMessages::Type, NMessages::FileTypeChanged>(): {
			m_xFileType = std::get<NMessages::FileTypeChanged>(message).FileType;
			break;
		}
	}
}

void TController::InitTableUpdator(std::chrono::seconds seconds) {
	m_pTableUpdator = std::make_shared<TIntervalClosure>(seconds, [this]() {
		m_xScreen.Post([this, data=NSProvider::Do(m_xFileType)]() mutable {
			m_pUIContainer->UpdateCurrencyTable(std::move(data));
		});
		m_xScreen.PostEvent(ftxui::Event::Custom);
	});
}

void TController::InitUiTimeUpdator() {
	using namespace std::chrono_literals;
	m_pUiTimeUpdator = std::make_shared<TIntervalClosure>(1s,
		[this]() { m_xScreen.PostEvent(ftxui::Event::Custom); });
}

}