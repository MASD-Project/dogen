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
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_for_formatter.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_provider_interface.hpp"
#include "dogen/cpp/types/expansion/provision_error.hpp"
#include "dogen/cpp/types/expansion/inclusion_directives_selector.hpp"
#include "dogen/cpp/types/formatters/formatting_assistant.hpp"
#include "dogen/cpp/types/formatters/selector.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::cpp::formatters::types;
static logger lg(logger_factory(traits::class_header_formatter_name()));

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

class provider : public expansion::
        inclusion_dependencies_provider_interface<sml::object> {

    boost::optional<expansion::inclusion_dependencies_for_formatter>
    provide(const dynamic::schema::repository& rp, const std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, std::string>
        >& inclusion_directives,
        const sml::object& o) const;
};

boost::optional<expansion::inclusion_dependencies_for_formatter>
provider::provide(const dynamic::schema::repository& rp,
    const std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, std::string> >&
    inclusion_directives,
    const sml::object& o) const {
    boost::optional<expansion::inclusion_dependencies_for_formatter>
        r = expansion::inclusion_dependencies_for_formatter();
    r->formatter_name(traits::class_header_formatter_name());

    // algorithm: domain headers need it for the swap function.
    auto& id(r->inclusion_dependencies());
    id.push_back(inclusion_constants::std::algorithm());

    selector s(rp, o.extensions());
    const auto io_fn(formatters::io::traits::facet_name());
    const bool io_enabled(s.is_formatter_enabled(io_fn));

    const auto types_fn(formatters::types::traits::facet_name());
    const bool use_integrated_io(s.is_facet_integrated(types_fn, io_fn));

    if (io_enabled && (use_integrated_io || o.is_parent() || o.is_child()))
        id.push_back(inclusion_constants::std::iosfwd());

    const expansion::inclusion_directives_selector id_sel(inclusion_directives);
    const auto ser_fn(formatters::serialization::traits::facet_name());
    const bool ser_enabled(s.is_facet_enabled(ser_fn));
    if (ser_enabled) {
        const auto fn(formatters::serialization::traits::
            forward_declarations_formatter_name());
        const auto id2(id_sel.select_inclusion_directive(o.name(), fn));
        if (!id2) {
            BOOST_LOG_SEV(lg, error) << inclusion_missing << fn;
            BOOST_THROW_EXCEPTION(formatting_error(inclusion_missing + fn));
        } else
            id.push_back(*id2);
    }

    const auto& rel(o.relationships());
    auto i(rel.find(sml::relationship_types::weak_associations));
    if (i != rel.end()) {
        const auto fn(traits::forward_declarations_formatter_name());
        for (const auto aqn : i->second) {
            const auto id2(id_sel.select_inclusion_directive(aqn, fn));
            if (id2)
                id.push_back(*id2);
        }
    }

    i = rel.find(sml::relationship_types::regular_associations);
    if (i != rel.end()) {
        const auto fn(traits::class_header_formatter_name());
        for (const auto aqn : i->second) {
            const auto id2(id_sel.select_inclusion_directive(aqn, fn));
            if (id2)
                id.push_back(*id2);
        }
    }

    i = rel.find(sml::relationship_types::visited_by);
    if (i != rel.end()) {
        const auto fn(traits::class_header_formatter_name());
        for (const auto aqn : i->second) {
            const auto id2(id_sel.select_inclusion_directive(aqn, fn));
            if (id2)
                id.push_back(*id2);
        }
    }

    i = rel.find(sml::relationship_types::parents);
    if (i != rel.end()) {
        const auto fn(traits::class_header_formatter_name());
        for (const auto aqn : i->second) {
            const auto id2(id_sel.select_inclusion_directive(aqn, fn));
            if (id2)
                id.push_back(*id2);
        }
    }

    return r;
}

}

dynamic::schema::ownership_hierarchy
class_header_formatter::ownership_hierarchy() const {
    static dynamic::schema::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            traits::class_header_formatter_name(),
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
