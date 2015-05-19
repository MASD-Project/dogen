/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/make_shared.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_provider_interface.hpp"
#include "dogen/cpp/types/formatters/formatting_assistant.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/hash/traits.hpp"
#include "dogen/cpp/types/formatters/types/class_implementation_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/types/class_implementation_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formatters.types.class_implementation_formatter"));

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

namespace {

class provider final : public formattables::
        inclusion_dependencies_provider_interface<sml::object> {
public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
        provide(const formattables::inclusion_dependencies_builder_factory& f,
        const sml::object& o) const override;
};

std::string provider::formatter_name() const {
    return class_implementation_formatter::static_formatter_name();
}

boost::optional<std::list<std::string> >
provider::provide(const formattables::inclusion_dependencies_builder_factory& f,
    const sml::object& o) const {
    auto builder(f.make());
    builder.add(o.name(), traits::class_implementation_formatter_name());
    return builder.build();
}

}

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
    formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file class_implementation_formatter::
format(const formattables::class_info& c) const {
    formatting_assistant fa(c, ownership_hierarchy(), file_type());
    const auto r(class_implementation_formatter_stitch(fa, c));

    BOOST_LOG_SEV(lg, debug) << "Filename: "
                             << r.path().generic_string();
    BOOST_LOG_SEV(lg, debug) << "Content: " << r.content();

    return r;
}

} } } }
