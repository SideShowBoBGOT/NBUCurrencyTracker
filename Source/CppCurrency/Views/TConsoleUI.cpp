#include <CppCurrency/Views/TConsoleUI.hpp>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/table.hpp>

#include <ftxui/component/captured_mouse.hpp>  // for ftxui
#include <ftxui/component/component.hpp>       // for Toggle, Renderer, Vertical
#include <ftxui/component/component_base.hpp>  // for ComponentBase
#include <ftxui/component/screen_interactive.hpp>  // for Component, ScreenInteractive
#include <ftxui/dom/elements.hpp>  // for text, hbox, vbox, Element

#include <magic_enum.hpp>

namespace curr {

static const auto s_vFileTypesArray = magic_enum::enum_names<NFileType>();
static const auto s_vFileTypesVector = std::vector<std::string>(s_vFileTypesArray.begin(), s_vFileTypesArray.end());

TConsoleUI::TConsoleUI() {
	auto fileTypeToggle = ftxui::Toggle(&s_vFileTypesVector, reinterpret_cast<int*>(&m_FileType));

//	auto table = ftxui::Table();
//	table.Render();
//	m_pElements = ftxui::Container::Vertical({
//		fileTypeToggle,
//		table.Render(),
//	});


}

void TConsoleUI::Render() const {
	//	auto xmlDocument = pugi::xml_document();
	//	if(not xmlDocument.load_file("fff.xml")) return -1;
	//	constexpr auto columnNames = std::array{"Id", "Full name", "Rate", "Short name", "Exchange date"};
	//
	//	auto data = std::vector<ftxui::Element>();
	//	for(auto i = 0u; i < columnNames.size(); ++i) {
	//		auto column = std::vector<ftxui::Element>();
	//		column.push_back(ftxui::text(columnNames[i]));
	//		for(const auto& currency : xmlDocument.child("exchange").children("currency")) {
	//			auto it = std::next(currency.children().begin(), i);
	//			column.push_back(ftxui::text((*it).child_value()));
	//		}
	//		data.push_back(ftxui::vbox(std::move(column)));
	//	}
	//	auto table = ftxui::hbox(std::move(data));
//	auto screen = ftxui::ScreenInteractive::TerminalOutput();
//	screen.Loop(fileTypeToggle);
}

}