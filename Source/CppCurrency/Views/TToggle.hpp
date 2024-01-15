#ifndef CPPCURRENCY_TTOGGLE_HPP
#define CPPCURRENCY_TTOGGLE_HPP

#include <ftxui/component/component_base.hpp>
#include <atomic>

namespace curr {

class TToggle {
	public:
	TToggle(const std::vector<std::string_view>& variants);

	public:
	const ftxui::Component& Component() const;
	void SelectActive(const int index);
	int SelectedVariant() const;

	protected:
	ftxui::Component m_pButtons = nullptr;
	ftxui::Component m_pComponent = nullptr;
	std::atomic_int32_t m_iSelected = 0;
};

}

#endif //CPPCURRENCY_TTOGGLE_HPP
