#include <CppCurrency/Views/NSTable.hpp>
#include <CppCurrency/Views/NSToggle.hpp>

#include <pugixml.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

int main() {
	auto xmlDocument = pugi::xml_document();
	if(not xmlDocument.load_file("fff.xml")) return -1;

	auto data = std::vector<std::vector<std::string>>();
	data.push_back({"Id", "Full name", "Rate", "Short name", "Exchange date"});
	for(const auto& currency : xmlDocument.child("exchange").children("currency")) {
		auto row = std::vector<std::string>();
		for(const auto& attr : currency.children()) {
			row.push_back(attr.child_value());
		}
		data.push_back(std::move(row));
	}

	const auto table = curr::NSTable::New(std::move(data));
	constexpr auto rr = std::array{"JSON", "XML", "CSV"};
	const auto toggle = curr::NSToggle::New({std::make_pair(rr[0], nullptr), std::make_pair(rr[1], nullptr), std::make_pair(rr[2], nullptr)});
	const auto vert = ftxui::Renderer(ftxui::Container::Vertical({toggle, table}), [toggle, table]() {
		return ftxui::vbox(toggle->Render() | ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, 5) , table->Render());
	});

	auto screen = ftxui::ScreenInteractive::FitComponent();
	screen.Loop(vert);

	return 0;
}