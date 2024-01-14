#include <CppCurrency/Views/NSToggle.hpp>
#include <ftxui/component/component.hpp>
#include <cassert>

namespace curr::NSToggle {

std::function<void()> OnButtonClickDecorator(const std::function<void()>& func) {
	return [func]() { if(func) func(); };
}

ftxui::Component New(const std::vector<std::pair<std::string_view, std::function<void()>>>& variants) {
	auto buttons = ftxui::Container::Horizontal({});
	const auto style = ftxui::ButtonOption::Animated(ftxui::Color::Default, ftxui::Color::Default,
		ftxui::Color::Default, ftxui::Color::Default);
	for(const auto& [name, func] : variants) {
		buttons->Add(ftxui::Button(name.data(), OnButtonClickDecorator(func), style));
	}
	return ftxui::Renderer(buttons, [buttons]() {
		auto elements = ftxui::Elements();
		const auto lastIndex = buttons->ChildCount() - 1;
		for(auto i = 0; i < lastIndex; ++i) {
			elements.push_back(buttons->ChildAt(i)->Render());
			elements.push_back(ftxui::separatorCharacter("|"));
		}
		elements.push_back(buttons->ChildAt(lastIndex)->Render());
		return ftxui::hbox(std::move(elements));
	});
}

}


