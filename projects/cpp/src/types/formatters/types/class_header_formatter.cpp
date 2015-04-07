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
#include <memory>
#include <sstream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_provider_interface.hpp"
#include "dogen/cpp/types/expansion/provision_error.hpp"
#include "dogen/cpp/types/expansion/inclusion_directives_selector.hpp"
#include "dogen/cpp/types/formatters/selector.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::cpp::formatters::types;
static logger lg(logger_factory(traits::class_header_formatter_name()));

const std::string formatter_settings_not_found(
    "Could not find settings for formatter: ");
const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");
const std::string header_guard_not_set(
    "Header guard for formatter is not set. Formatter: ");
const std::string include_directive_not_set(
    "Include directive for formatter is not set. Formatter: ");

const std::string no_fields_for_formatter(
    "Could not find any fields for formatter: ");
const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string qname_not_found("Could not find qualified name in model: ");
const std::string path_details_missing("Path details not found for qname: ");

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

class provider : public expansion::
        inclusion_dependencies_provider_interface<sml::object> {

    std::pair<std::string, std::list<std::string> >
    provide(const dynamic::schema::repository& rp, const std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, std::string>
        >& inclusion_directives,
        const sml::object& o) const;
};

std::pair<std::string, std::list<std::string> >
provider::provide(const dynamic::schema::repository& rp,
    const std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, std::string> >&
    /*inclusion_directives*/,
    const sml::object& o) const {
    std::pair<std::string, std::list<std::string> > r;
    r.first = traits::class_header_formatter_name();

    // algorithm: domain headers need it for the swap function.
    r.second.push_back(inclusion_constants::std::algorithm());

    selector s(rp, o.extensions());
    const auto io_fn(formatters::io::traits::facet_name());
    const bool io_enabled(s.is_formatter_enabled(io_fn));

    const auto types_fn(formatters::types::traits::facet_name());
    const bool use_integrated_io(s.is_facet_integrated(types_fn, io_fn));

    if (io_enabled && use_integrated_io)
        r.second.push_back(inclusion_constants::std::iosfwd());

    // const auto& rel(o.relationships());
    // const expansion::path_derivatives_selector pd_sel(pd);
    // auto i(rel.find(sml::relationship_types::weak_associations));
    // if (i != rel.end()) {
    //     const auto fn(traits::forward_declarations_formatter_name());
    //     for (const auto aqn : i->second)
    //         r.second.push_back(pd_sel.select_inclusion_directive(aqn, fn));
    // }

    // i = rel.find(sml::relationship_types::regular_associations);
    // if (i != rel.end()) {
    //     const auto fn(traits::class_header_formatter_name());
    //     for (const auto aqn : i->second)
    //         r.second.push_back(pd_sel.select_inclusion_directive(aqn, fn));
    // }

    return r;
}

void class_header_formatter::validate(
    const settings::formatter_settings& fs) const {

    const auto& fn(ownership_hierarchy().formatter_name());
    if (fs.file_path().empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(file_path_not_set + fn));
    }

    if (!fs.header_guard() || fs.header_guard()->empty()) {
        BOOST_LOG_SEV(lg, error) << header_guard_not_set << fn;
        BOOST_THROW_EXCEPTION(formatting_error(header_guard_not_set + fn));
    }
}

settings::formatter_settings class_header_formatter::
formatter_settings_for_formatter(const formattables::class_info& c) const {
    const auto& fs(c.settings().formatter_settings());
    const auto& fn(ownership_hierarchy().formatter_name());
    const auto i(fs.find(fn));
    if (i == fs.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_settings_not_found << fn;

        BOOST_THROW_EXCEPTION(
            formatting_error(formatter_settings_not_found + fn));
    }
    return i->second;
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
    boilerplate_formatter boilerplate_;
    BOOST_LOG_SEV(lg, debug) << "Formatting type: " << c.name();

    std::ostringstream ss;
    boost::iostreams::filtering_ostream fo;
    dogen::formatters::indent_filter::push(fo, 4);
    fo.push(ss);

    const auto fs(formatter_settings_for_formatter(c));
    validate(fs);

    const auto hg(*fs.header_guard());
    dogen::cpp::formatters::boilerplate_formatter f;
    const auto gs(c.settings().general_settings());
    if (gs)
        f.format_begin(fo, gs->annotation(), fs.inclusion_dependencies(), hg);

    // do formatting.

    if (gs)
        f.format_end(fo, gs->annotation(), hg);

    BOOST_LOG_SEV(lg, debug) << "Formatted type: " << c.name();
    dogen::formatters::file r;
    r.content(ss.str());
    r.path(fs.file_path());

    BOOST_LOG_SEV(lg, debug) << "Filename: "
                             << r.path().generic_string();
    BOOST_LOG_SEV(lg, debug) << "Content: " << r.content();
    return r;
}

} } } }
