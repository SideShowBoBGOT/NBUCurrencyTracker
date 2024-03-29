#include <CppCurrency/Views/TCurrencyDataView.hpp>

namespace curr {

TCurrencyDataView::TCurrencyDataView(ACurrencyData&& data) {
	auto rendered = ftxui::Elements();
	const auto attrSize = data.size();
	rendered.reserve(attrSize);
	for(auto i = 0u; i < attrSize - 1; ++i) {
		rendered.push_back(ftxui::text(std::move(data[i])));
		rendered.push_back(ftxui::separator());
	}
	rendered.push_back(ftxui::text(std::move(data.back())));
	m_pRow = ftxui::hbox(std::move(rendered));
}

ftxui::Element TCurrencyDataView::Render() {
	using TFocusManagement = std::shared_ptr<ftxui::Node>(*)(std::shared_ptr<ftxui::Node>);
	TFocusManagement focusManagement = nullptr;
	if(Focused()) {
		focusManagement = ftxui::focus;
	} else if(Active()) {
		focusManagement = ftxui::select;
	} else {
		focusManagement = ftxui::nothing;
	}
	return m_pRow | focusManagement;
}

bool TCurrencyDataView::Focusable() const {
	return true;
}

}