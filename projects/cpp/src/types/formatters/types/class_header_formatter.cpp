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
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

const std::string formatter_id("cpp.formatters.types.class_header_formatter");

using namespace dogen::utility::log;
static logger lg(logger_factory(formatter_id));

// FIXME
const dogen::cpp::includes empty_includes = dogen::cpp::includes();
const boost::filesystem::path empty_path;

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

std::string class_header_formatter::facet_id() const {
    return traits::facet_id;
}

std::string class_header_formatter::formatter_id() const {
    return ::formatter_id;
}

dogen::formatters::file class_header_formatter::
format(const class_info& c, const settings_bundle& sb) const {
    boilerplate_formatter boilerplate_;
    BOOST_LOG_SEV(lg, debug) << "Formatting type: " << c.name();

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    dogen::formatters::indent_filter::push(fo, 4);
    fo.push(s);

    dogen::cpp::formatters::boilerplate_formatter f;
    const auto a(sb.general_settings().annotation());
    f.format_begin(fo, a, empty_includes, empty_path);
    f.format_end(fo, a, empty_path);

    BOOST_LOG_SEV(lg, debug) << "Formatted type: " << c.name();
    dogen::formatters::file r;
    r.content(s.str());

    BOOST_LOG_SEV(lg, debug) << "content: " << r.content();
    return r;
}

} } } }
