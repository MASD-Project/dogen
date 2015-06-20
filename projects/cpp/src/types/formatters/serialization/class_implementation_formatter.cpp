#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/entity_formatting_assistant.hpp"
#include "dogen/cpp/types/formatters/serialization//class_implementation_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/serialization/class_implementation_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

std::string class_implementation_formatter::static_formatter_name() {
    return traits::class_implementation_formatter_name();
}

dynamic::ownership_hierarchy
class_implementation_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            class_implementation_formatter::static_formatter_name(),
            formatters::traits::implementation_formatter_group_name());
    return r;
}

file_types class_implementation_formatter::file_type() const {
    return file_types::cpp_implementation;
}

void class_implementation_formatter::register_inclusion_dependencies_provider(
    formattables::registrar& /*rg*/) const {
}

dogen::formatters::file class_implementation_formatter::
format(const formattables::class_info& c) const {
    entity_formatting_assistant fa(c, ownership_hierarchy(), file_type());
    const auto r(class_implementation_formatter_stitch(fa, c));
    return r;
}

} } } }
