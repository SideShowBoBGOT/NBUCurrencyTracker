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
	ftxui::ScreenInteractive m_Screen = ftxui::ScreenInteractive::FitComponent();
	std::unique_ptr<TUIContainer> m_UIContainer = nullptr;
};

}

#endif //CPPCURRENCY_TCONTROLLER_HPP
