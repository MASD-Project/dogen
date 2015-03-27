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
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/settings/path_expander.hpp"
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

class inclusion_expander final : public dynamic::expansion::expander_interface {
public:
    std::string name() const override;

    const std::forward_list<std::string>& dependencies() const override;

    void setup(const dynamic::expansion::expansion_context& ec) override;

    void expand(const sml::qname& qn, const dynamic::schema::scope_types& st,
        dynamic::schema::object& o) const override;
};

std::string inclusion_expander::name() const {
    static std::string name("cpp.types.inclusion_expander");
    return name;
}

const std::forward_list<std::string>& inclusion_expander::
dependencies() const {
    static std::forward_list<std::string>
        r { settings::path_expander::static_name() };
    return r;
}

void inclusion_expander::setup(
    const dynamic::expansion::expansion_context& /*ec*/) {
}

void inclusion_expander::
expand(const sml::qname& /*qn*/, const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& /*o*/) const {

    // const auto i(m.objects().find(qn));
    // if (i == m.objects().end())
    //     return;

    // std::list<std::string> includes;
    // algorithm: domain headers need it for the swap function.
    // includes.push_back(inclusion_constants::std::algorithm());

    // const auto n(sml::string_converter::convert(qn));
    // BOOST_LOG_SEV(lg, error) << qname_not_found << n;
    // BOOST_THROW_EXCEPTION(formatting_error(qname_not_found + n));

    // const auto io_fn(formatters::io::traits::facet_name());
    // const auto iofs(s.select_global_facet_settings(io_fn));
    // const bool io_enabled(iofs.enabled());

    // const auto types_fn(formatters::types::traits::facet_name());
    // const auto tfs(s.select_global_facet_settings(types_fn));
    // const bool use_integrated_io(
    //     tfs.integrated_facets().find(io_fn) != tfs.integrated_facets().end());

    // if (io_enabled && use_integrated_io)
    //     r.push_back(inclusion_constants::std::iosfwd());

    // const auto& o(pair.second);
    // return r;
}

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

boost::shared_ptr<dynamic::expansion::expander_interface>
class_header_formatter::create_expander() const {
    return boost::make_shared<inclusion_expander>();
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
