#ifndef CPPCURRENCY_TCONTROLLER_HPP
#define CPPCURRENCY_TCONTROLLER_HPP

#include <CppCurrency/Helpers/TAtomicQueue.hpp>
#include <CppCurrency/Controllers/NAMessages.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

namespace curr {

class TUIContainer;
class TIntervalClosure;

class TController {
	public:
	static TController& Instance();

	protected:
	TController();

	public:
	void Run();
	void SendMessage(const NMessages::Type& message);

	protected:
	void ClientThread();
	void ProcessMessages();
	void InitTableUpdator(std::chrono::seconds seconds);
	void InitUiTimeUpdator();

	protected:
	ftxui::ScreenInteractive m_xScreen = ftxui::ScreenInteractive::FitComponent();
	std::shared_ptr<TUIContainer> m_pUIContainer = nullptr;
	TAtomicQueue<NMessages::Type> m_qMessages;

	protected:
	NFileType m_xFileType = NFileType::XML;
	std::shared_ptr<TIntervalClosure> m_pTableUpdator = nullptr;
	std::shared_ptr<TIntervalClosure> m_pUiTimeUpdator = nullptr;
};

}

#endif //CPPCURRENCY_TCONTROLLER_HPP
