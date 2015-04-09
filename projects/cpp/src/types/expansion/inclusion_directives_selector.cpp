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
#include "dogen/cpp/types/expansion/selection_error.hpp"
#include "dogen/cpp/types/expansion/inclusion_directives_selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.expansion.inclusion_directives_selector"));

const std::string formatter_inclusion_directives_missing(
    "Could not find inclusion directives for formatter: ");
const std::string qname_inclusion_directives_missing(
    "Could not find inclusion directives for qname: ");

}

namespace dogen {
namespace cpp {
namespace expansion {

inclusion_directives_selector::inclusion_directives_selector(
    const std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, std::string> >& id)
    : inclusion_directives_(id) {}

boost::optional<std::string> inclusion_directives_selector::
inclusion_directives_for_formatter_name(
    const std::unordered_map<std::string, std::string>& id,
    const std::string& formatter_name) const {

    const auto i(id.find(formatter_name));
    if (i == id.end()) {
        BOOST_LOG_SEV(lg, warn) << formatter_inclusion_directives_missing
                                << formatter_name;
        return boost::optional<std::string>();
    }
    return i->second;
}

const std::unordered_map<std::string, std::string>&
inclusion_directives_selector::
inclusion_directives_for_qname(const sml::qname& qn) const {
    const auto i(inclusion_directives_.find(qn));
    if (i == inclusion_directives_.end()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << qname_inclusion_directives_missing << n;
        BOOST_THROW_EXCEPTION(
            selection_error(qname_inclusion_directives_missing + n));
    }
    return i->second;
}

boost::optional<std::string> inclusion_directives_selector::
select_inclusion_directive(const sml::qname& qn,
    const std::string& formatter_name) const {
    const auto& id(inclusion_directives_for_qname(qn));
    const auto r(inclusion_directives_for_formatter_name(id, formatter_name));
    return r;
}

} } }
