#ifndef CPPCURRENCY_NAMESSAGES_HPP
#define CPPCURRENCY_NAMESSAGES_HPP

#include <CppCurrency/Controllers/NNFileType.hpp>
#include <chrono>

namespace curr {

namespace NMessages {

struct IntervalChanged { std::chrono::seconds Seconds = std::chrono::seconds(0); };
struct FileTypeChanged { NFileType FileType = NFileType::XML; };
// other types of messages
using Type = std::variant<IntervalChanged, FileTypeChanged>;

}

}

#endif //CPPCURRENCY_NAMESSAGES_HPP
