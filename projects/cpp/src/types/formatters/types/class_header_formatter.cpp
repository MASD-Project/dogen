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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"

namespace {

const std::string formatter_id("cpp.formatters.types.class_header_formatter");

using namespace dogen::utility::log;
static logger lg(logger_factory(formatter_id));

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
format(const new_class_info& c, const settings_bundle /*s*/) const {
    BOOST_LOG_SEV(lg, debug) << "Formatting type: " << c.name();
    dogen::formatters::file r;

    BOOST_LOG_SEV(lg, debug) << "Formatted type: " << c.name();
    return r;
}

} } } }
