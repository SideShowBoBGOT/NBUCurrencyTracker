#ifndef CPPCURRENCY_TCURRENCYDATAVIEW_HPP
#define CPPCURRENCY_TCURRENCYDATAVIEW_HPP

#include <ftxui/component/component_base.hpp>

namespace curr {

struct SCurrencyData;

class TCurrencyDataView : public ftxui::ComponentBase {
	public:
	TCurrencyDataView(SCurrencyData&& data);

	public:
	virtual ftxui::Element Render() override;
	virtual bool Focusable() const override;

	protected:
	ftxui::Element m_Row = nullptr;
};

}

#endif //CPPCURRENCY_TCURRENCYDATAVIEW_HPP
