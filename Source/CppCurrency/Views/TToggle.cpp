#include <CppCurrency/Views/TToggle.hpp>
#include <ftxui/component/component.hpp>

namespace curr {

static const auto s_xButtonStyle = ftxui::ButtonOption::Animated(ftxui::Color::Default,
	ftxui::Color::Default, ftxui::Color::Default, ftxui::Color::Default);

TToggle::TToggle(const std::vector<std::pair<std::string_view, std::function<void()>>>& variants) {
	m_pButtons = ftxui::Container::Horizontal({});
	for(const auto& [name, func] : variants) {
		m_pButtons->Add(ftxui::Button(name.data(), func, s_xButtonStyle));
	}

	m_pComponent = ftxui::Renderer(m_pButtons, [this]() {
		auto elements = ftxui::Elements();
		const auto lastIndex = m_pButtons->ChildCount() - 1;
		for(auto i = 0; i < lastIndex; ++i) {
			elements.push_back(m_pButtons->ChildAt(i)->Render());
			elements.push_back(ftxui::separatorCharacter("|"));
		}
		elements.push_back(m_pButtons->ChildAt(lastIndex)->Render());
		return ftxui::hbox(std::move(elements));
	});
}

const ftxui::Component& TToggle::Component() const {
	return m_pComponent;
}

void TToggle::SelectActive(const int index) {
	m_pButtons->SetActiveChild(m_pButtons->ChildAt(index));
}

}


