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
#include <sstream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_builder.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_provider_interface.hpp"
#include "dogen/cpp/types/expansion/provision_error.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/selector.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::cpp::formatters::types;
static logger
lg(logger_factory(class_header_formatter::static_formatter_name()));

const std::string include_directive_not_set(
    "Include directive for formatter is not set. Formatter: ");

const std::string no_fields_for_formatter(
    "Could not find any fields for formatter: ");
const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string qname_not_found("Could not find qualified name in model: ");
const std::string path_details_missing("Path details not found for qname: ");
const std::string inclusion_missing(
    "Expected inclusion is missing. Formatter: ");

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

namespace {

class provider final : public expansion::
        inclusion_dependencies_provider_interface<sml::object> {
public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
    provide(const dynamic::schema::repository& srp,
        const expansion::inclusion_directives_repository& idr,
        const sml::object& o) const override;
};

std::string provider::formatter_name() const {
    return class_header_formatter::static_formatter_name();
}

boost::optional<std::list<std::string> >
provider::provide(const dynamic::schema::repository& rp,
    const expansion::inclusion_directives_repository& idr,
    const sml::object& o) const {

    const auto self_fn(class_header_formatter::static_formatter_name());
    expansion::inclusion_dependencies_builder builder(idr);

    // algorithm: domain headers need it for the swap function.
    builder.add(inclusion_constants::std::algorithm());

    selector s(rp, o.extensions());
    if (s.is_integrated_io_enabled() || o.is_parent() || o.is_child())
        builder.add(inclusion_constants::std::iosfwd());

    if (s.is_serialization_enabled()) {
        using ser = formatters::serialization::traits;
        const auto ser_fwd_fn(ser::forward_declarations_formatter_name());
        builder.add(o.name(), ser_fwd_fn);
    }

    const auto lambda([&](const sml::object& o,
            const sml::relationship_types rt,
            const std::string& fn) {
            auto i(o.relationships().find(rt));
            if (i == o.relationships().end())
                return;

            builder.add(i->second, fn);
        });

    using rt = sml::relationship_types;
    const auto fwd_fn(traits::forward_declarations_formatter_name());
    lambda(o, rt::weak_associations, fwd_fn);
    lambda(o, rt::regular_associations, self_fn);
    lambda(o, rt::hash_container_keys, self_fn);
    lambda(o, rt::parents, self_fn);
    if (o.is_visitable())
        lambda(o, rt::visited_by, self_fn);

    return builder.build();
}

}

std::string class_header_formatter::static_formatter_name() {
    return traits::class_header_formatter_name();
}

dynamic::schema::ownership_hierarchy
class_header_formatter::ownership_hierarchy() const {
    static dynamic::schema::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            class_header_formatter::static_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types class_header_formatter::file_type() const {
    return file_types::cpp_header;
}

void class_header_formatter::register_inclusion_dependencies_provider(
    expansion::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file
class_header_formatter::format(const formattables::class_info& c) const {
    formatting_assistant fa(c, ownership_hierarchy(), file_type());
    const auto r(class_header_formatter_stitch(fa, c));
    return r;
}

} } } }
