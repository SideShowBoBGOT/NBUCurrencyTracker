#ifndef CPPCURRENCY_TCURRENCYDATAVIEW_HPP
#define CPPCURRENCY_TCURRENCYDATAVIEW_HPP

#include <CppCurrency/Models/ACurrencyData.hpp>
#include <ftxui/component/component_base.hpp>

namespace curr {

class TCurrencyDataView : public ftxui::ComponentBase {
	public:
	TCurrencyDataView(ACurrencyData&& data);

	public:
	virtual ftxui::Element Render() override;
	virtual bool Focusable() const override;

	protected:
	ftxui::Element m_Row = nullptr;
};

}

#endif //CPPCURRENCY_TCURRENCYDATAVIEW_HPP
