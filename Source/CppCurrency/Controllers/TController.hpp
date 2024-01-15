#ifndef CPPCURRENCY_TCONTROLLER_HPP
#define CPPCURRENCY_TCONTROLLER_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <memory>

namespace curr {

class TUIContainer;

class TController {
	public:
	TController();

	public:
	void Run();

	protected:
	void ClientThread();

	protected:
	ftxui::ScreenInteractive m_xScreen = ftxui::ScreenInteractive::FitComponent();
	std::shared_ptr<TUIContainer> m_pUIContainer = nullptr;
};

}

#endif //CPPCURRENCY_TCONTROLLER_HPP
