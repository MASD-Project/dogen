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
    const inclusion_directives_repository& rp) : repository_(rp) {}

const settings::inclusion_directives_settings& inclusion_directives_selector::
inclusion_directives_for_qname(const sml::qname& qn) const {
    const auto i(repository_.inclusion_directives_by_qname().find(qn));
    if (i == repository_.inclusion_directives_by_qname().end()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << qname_inclusion_directives_missing << n;
        BOOST_THROW_EXCEPTION(
            selection_error(qname_inclusion_directives_missing + n));
    }
    return i->second;
}

const settings::inclusion_directive_settings&
inclusion_directives_selector::inclusion_directives_for_formatter(
    const settings::inclusion_directives_settings& ids,
    const std::string& formatter_name) const {

    const auto i(ids.inclusion_directive_settings().find(formatter_name));
    if (i == ids.inclusion_directive_settings().end()) {
        BOOST_LOG_SEV(lg, error) << formatter_inclusion_directives_missing
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(selection_error(
                formatter_inclusion_directives_missing + formatter_name));
    }
    return i->second;
}

boost::optional<std::string>
inclusion_directives_selector::select_inclusion_directive(
    const sml::qname& qn,
    const std::string& formatter_name) const {

    const auto& id_qn(inclusion_directives_for_qname(qn));
    bool inclusion_not_required(!id_qn.inclusion_required());
    if (inclusion_not_required)
        return boost::optional<std::string>();

    const auto& fn(formatter_name);
    const auto& id_fmt(inclusion_directives_for_formatter(id_qn, fn));
    inclusion_not_required = !id_fmt.inclusion_required();
    if (inclusion_not_required)
        return boost::optional<std::string>();

    if (!id_fmt.inclusion_directive()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << formatter_inclusion_directives_missing
                                 << n;
        BOOST_THROW_EXCEPTION(
            selection_error(formatter_inclusion_directives_missing + n));
    }
    return id_fmt.inclusion_directive();
}

} } }
