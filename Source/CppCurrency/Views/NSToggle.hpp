#ifndef CPPCURRENCY_NSTOGGLE_HPP
#define CPPCURRENCY_NSTOGGLE_HPP

#include <ftxui/component/component_base.hpp>

namespace curr::NSToggle {

ftxui::Component New(const std::vector<std::pair<std::string_view, std::function<void()>>>& variants);

}

#endif //CPPCURRENCY_NSTOGGLE_HPP
