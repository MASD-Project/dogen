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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/selection_error.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_directives_selector"));

}

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_directives_selector::inclusion_directives_selector(
    const inclusion_directives_repository& rp) : repository_(rp) {}

boost::optional<std::string>
inclusion_directives_selector::select_inclusion_directive(
    const sml::qname& qn,
    const std::string& formatter_name) const {

    const auto i(repository_.inclusion_directives_by_qname().find(qn));
    if (i == repository_.inclusion_directives_by_qname().end())
        return boost::optional<std::string>();

    const auto j(i->second.find(formatter_name));
    if (j == i->second.end())
        return boost::optional<std::string>();

    return j->second;
}

} } }
