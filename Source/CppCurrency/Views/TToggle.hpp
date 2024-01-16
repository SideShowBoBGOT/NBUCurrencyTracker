#ifndef CPPCURRENCY_TTOGGLE_HPP
#define CPPCURRENCY_TTOGGLE_HPP

#include <ftxui/component/component_base.hpp>

namespace curr {

class TToggle {
	public:
	TToggle(const std::vector<std::pair<std::string_view, std::function<void()>>>& variants);

	public:
	const ftxui::Component& Component() const;
	void SelectActive(const int index);

	protected:
	ftxui::Component m_pButtons = nullptr;
	ftxui::Component m_pComponent = nullptr;

	protected:
	std::vector<std::pair<std::string_view, std::function<void()>>> m_vVariants;
};

}

#endif //CPPCURRENCY_TTOGGLE_HPP
