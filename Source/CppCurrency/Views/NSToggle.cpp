#include <CppCurrency/Views/NSToggle.hpp>

#include <ftxui/component/component.hpp>

namespace curr::NSToggle {

std::function<void()> OnButtonClickDecorator(const std::function<void()>& func) {
	return [func]() { if(func) func(); };
}

ftxui::Component New(const std::vector<std::pair<std::string_view, std::function<void()>>>& variants) {
	auto buttons = ftxui::Container::Horizontal({});
	const auto style = ftxui::ButtonOption::Animated(ftxui::Color::Default, ftxui::Color::Default, ftxui::Color::Default, ftxui::Color::Default);
	for(const auto& [name, func] : variants) {
		buttons->Add(ftxui::Button(name.data(), OnButtonClickDecorator(func), style));
	}
	return buttons;
}

}