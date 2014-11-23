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
#include "dogen/cpp/types/name_builder.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

const std::string formatter_id("cpp.formatters.types.class_header_formatter");
const std::string path_spec_details_for_formatter_not_found(
    "Path spec details for formatter not found. Formatter: ");

using namespace dogen::utility::log;
static logger lg(logger_factory(formatter_id));

// FIXME
const dogen::cpp::includes empty_includes = dogen::cpp::includes();

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

class includes_builder : public includes_builder_interface {
public:
    includes build(const sml::model& m, const sml::qname qn,
        const std::unordered_map<sml::qname,
        includes_builder_interface::path_by_formatter_type>&
        relative_file_names_by_formatter_by_qname) const override;
};

includes includes_builder::build(const sml::model& /*m*/,
    const sml::qname /*qn*/,
    const std::unordered_map<sml::qname, includes_builder_interface::
                             path_by_formatter_type>&
    /*relative_file_names_by_formatter_by_qname*/) const {
    includes r;
    return r;
}

boost::filesystem::path class_header_formatter::
get_relative_path(const class_info& c) const {
    const auto& details(c.path_spec_details_for_formatter());
    const auto i(details.find(formatter_id()));
    if (i == details.end()) {
        BOOST_LOG_SEV(lg, error) << path_spec_details_for_formatter_not_found
                                 << formatter_id();

        /* FIXME
        BOOST_THROW_EXCEPTION(formatting_error(
        path_spec_details_for_formatter_not_found +
                formatter_id()));
        */
        return boost::filesystem::path();
    }
    return i->second.relative_path();
}

std::string class_header_formatter::facet_id() const {
    return traits::facet_id;
}

std::string class_header_formatter::formatter_id() const {
    return ::formatter_id;
}

boost::filesystem::path class_header_formatter::
make_file_name(const settings_bundle& sb, const sml::qname& qn) const {
    name_builder b;
    return b.header_file_name(sb, qn);
}

std::shared_ptr<includes_builder_interface>
class_header_formatter::make_includes_builder() const {
    return std::make_shared<includes_builder>();
}

dogen::formatters::file class_header_formatter::
format(const settings_bundle& sb, const class_info& c) const {
    boilerplate_formatter boilerplate_;
    BOOST_LOG_SEV(lg, debug) << "Formatting type: " << c.name();

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    dogen::formatters::indent_filter::push(fo, 4);
    fo.push(s);

    const auto rp(get_relative_path(c));
    dogen::cpp::formatters::boilerplate_formatter f;
    const auto a(sb.general_settings().annotation());
    f.format_begin(fo, a, empty_includes, rp);
    f.format_end(fo, a, rp);

    BOOST_LOG_SEV(lg, debug) << "Formatted type: " << c.name();
    dogen::formatters::file r;
    r.content(s.str());
    r.relative_path(rp);

    BOOST_LOG_SEV(lg, debug) << "filename: "
                             << r.relative_path().generic_string();
    BOOST_LOG_SEV(lg, debug) << "content: " << r.content();
    return r;
}

} } } }
