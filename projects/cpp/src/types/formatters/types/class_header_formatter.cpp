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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

const std::string formatter_settings_not_found(
    "Could not find settings for formatter: ");
const std::string inclusion_path_not_set(
    "Inclusion path for formatter is not set. Formatter: ");
const std::string file_path_not_set(
    "File path for formatter is not set. Formatter: ");

const std::string qname_not_found("Could not find qualified name in model: ");

using namespace dogen::utility::log;
using namespace dogen::cpp::formatters::types;
static logger lg(logger_factory(traits::class_header_formatter_name()));

// FIXME
const dogen::cpp::formattables::includes empty_includes =
    dogen::cpp::formattables::includes();

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

void class_header_formatter::validate(
    const settings::formatter_settings& fs) const {

    if (!fs.inclusion_path() || fs.inclusion_path()->empty()) {
        BOOST_LOG_SEV(lg, error) << inclusion_path_not_set << formatter_name();
        BOOST_THROW_EXCEPTION(formatting_error(inclusion_path_not_set
                + formatter_name()));
    }

    if (fs.file_path().empty()) {
        BOOST_LOG_SEV(lg, error) << file_path_not_set << formatter_name();
        BOOST_THROW_EXCEPTION(formatting_error(file_path_not_set
                + formatter_name()));
    }
}

settings::formatter_settings class_header_formatter::
formatter_settings_for_formatter(const formattables::class_info& c) const {
    const auto& fs(c.settings().formatter_settings());
    const auto i(fs.find(formatter_name()));
    if (i == fs.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_settings_not_found
                                 << formatter_name();

        BOOST_THROW_EXCEPTION(formatting_error(
                formatter_settings_not_found + formatter_name()));
    }
    return i->second;
}

file_types class_header_formatter::file_type() const {
    return file_types::cpp_header;
}

std::string class_header_formatter::facet_name() const {
    return traits::facet_name();
}

std::string class_header_formatter::formatter_name() const {
    return traits::class_header_formatter_name();
}

/*
formattables::file_properties
class_header_formatter::provide_file_properties(const settings::selector& s,
    const sml::qname& qn) const {

    path_ingredients_factory pif;
    const auto pi(pif.make(s, *this, qn));

    path_factory pf;
    formattables::file_properties r;
    r.file_path(pf.make_file_path(pi, qn));

    formattables::inclusion inc;
    using dt = formattables::inclusion_delimiter_types;
    inc.inclusion_delimiter_type(dt::double_quotes);
    inc.inclusion_path(pf.make_include_path(pi, qn));
    r.inclusion(inc);

    return r;
}

std::list<formattables::inclusion> class_header_formatter::
provide_inclusion_dependencies(const settings::selector& s,
    const sml::model& m,
    const std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, formattables::file_properties>
        >& file_properties_by_formatter_name,
    const sml::qname& qn) const {
    std::list<formattables::inclusion>  r;

    // algorithm: domain headers need it for the swap function.
    // const auto ts(s.select_type_settings(types_fn));
    // if (

    const auto i(m.objects().find(qn));
    if (i == m.objects().end()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << qname_not_found << n;
        BOOST_THROW_EXCEPTION(formatting_error(qname_not_found + n));
    }

    const auto io_fn(formatters::io::traits::facet_name());
    const auto iofs(s.select_global_facet_settings(io_fn));
    const bool io_enabled(iofs.enabled());

    const auto types_fn(formatters::types::traits::facet_name());
    const auto tfs(s.select_global_facet_settings(types_fn));
    const bool use_integrated_io(
        tfs.integrated_facets().find(io_fn) != tfs.integrated_facets().end());

    if (io_enabled && use_integrated_io)
        r.push_back(inclusion_constants::std::iosfwd());

    // const auto& o(pair.second);
    return r;
}
*/

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

    const auto ip(*fs.inclusion_path());
    dogen::cpp::formatters::boilerplate_formatter f;
    const auto gs(c.settings().general_settings());
    if (gs)
        f.format_begin(fo, gs->annotation(), empty_includes, ip);

    // do formatting.

    if (gs)
        f.format_end(fo, gs->annotation(), ip);

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
