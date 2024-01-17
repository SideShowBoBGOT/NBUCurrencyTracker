#ifndef CPPCURRENCY_NAMESSAGES_HPP
#define CPPCURRENCY_NAMESSAGES_HPP

#include <CppCurrency/Controllers/NNFileType.hpp>
#include <chrono>

namespace curr {

namespace NMessages {

struct IntervalChanged { std::chrono::milliseconds Millis; };
struct FileTypeChanged { NFileType FileType = NFileType::XML; };
// other types of messages
using Type = std::variant<IntervalChanged, FileTypeChanged>;

}

}

#endif //CPPCURRENCY_NAMESSAGES_HPP
