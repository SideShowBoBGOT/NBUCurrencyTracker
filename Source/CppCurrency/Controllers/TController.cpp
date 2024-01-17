#include <CppCurrency/Controllers/TController.hpp>
#include <CppCurrency/Views/TUIContainer.hpp>
#include <CppCurrency/Controllers/NSProvider.hpp>
#include <CppCurrency/Helpers/NSHelpers.hpp>
#include <CppCurrency/Helpers/TIntervalClosure.hpp>
#include <CppCurrency/Controllers/TConfig.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <thread>

namespace curr {

static constexpr std::string_view s_sLoggerName = "ProvideLogger";

TController& TController::Instance() {
	static auto instance = TController();
	return instance;
}

TController::TController() {
	const auto logger = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>(
		s_sLoggerName.data(), TConfig::Instance().LogFileName());
	spdlog::set_default_logger(logger);
	InitTableUpdator(TConfig::Instance().Interval());
	InitUiTimeUpdator();
	m_xFileType = TConfig::Instance().FileType();
	m_pUIContainer = std::make_shared<TUIContainer>();
}

void TController::Run() {
	auto clientThread = std::jthread([this]() { ClientThread(); });
	m_xScreen.Loop(m_pUIContainer->Component());
}

void TController::SendMessage(const NMessages::Type& message) {
	m_qMessages.Push(message);
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
			m_pTableUpdator->Interval = std::get<NMessages::IntervalChanged>(message).Millis;
			m_xScreen.Post([this]() mutable {
				m_pUIContainer->UpdateInterval(m_pTableUpdator->Interval);
			});
			m_xScreen.PostEvent(ftxui::Event::Custom);
			break;
		}
		case NSHelpers::VariantIndex<NMessages::Type, NMessages::FileTypeChanged>(): {
			m_xFileType = std::get<NMessages::FileTypeChanged>(message).FileType;
			break;
		}
	}
}

void TController::InitTableUpdator(std::chrono::milliseconds millis) {
	m_pTableUpdator = std::make_shared<TIntervalClosure>(millis, [this]() {
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