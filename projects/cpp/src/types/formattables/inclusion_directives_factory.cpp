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
#include "dogen/tack/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/settings/inclusion_directives_settings_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_directives_factory"));

const std::string name_not_found("Expected name not found: ");
const std::string empty_include_directive("Include directive is empty.");
const std::string missing_include_directive(
    "Expected include directive is missing: ");
const std::string formatter_name_not_found("Formatter name not found: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_directives_factory::inclusion_directives_factory(
    const dynamic::repository& srp,
    const formatters::container& fc,
    const path_derivatives_repository& pdrp)
    : dynamic_repository_(srp), container_(fc), path_repository_(pdrp) {}

std::unordered_map<std::string, formattables::path_derivatives>
inclusion_directives_factory::path_derivatives_for_name(
    const tack::name& n) const {
    const auto i(path_repository_.path_derivatives_by_name().find(n));
    if (i == path_repository_.path_derivatives_by_name().end()) {
        const auto sn(tack::string_converter::convert(n));
        BOOST_LOG_SEV(lg, error) << name_not_found << sn;
        BOOST_THROW_EXCEPTION(building_error(name_not_found + sn));
    }
    return i->second;
}

formattables::path_derivatives
inclusion_directives_factory::path_derivatives_for_formatter_name(
    const std::unordered_map<std::string,
                             formattables::path_derivatives>& pd,
    const std::string& formatter_name) const {

    const auto i(pd.find(formatter_name));
    if (i == pd.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_name_not_found
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(
            building_error(formatter_name_not_found + formatter_name));
    }
    return i->second;
}

void inclusion_directives_factory::validate_inclusion_directive(
    const std::string& id,
    const std::string& formatter_name,
    const std::string& type_name) const {

    if (!id.empty())
        return;

    std::ostringstream s;
    s << empty_include_directive << formatter_name
      << " for type: " << type_name;

    const auto msg(s.str());
    BOOST_LOG_SEV(lg, error) << msg;
    BOOST_THROW_EXCEPTION(building_error(msg));
}

settings::inclusion_directives_settings inclusion_directives_factory::
create_inclusion_directives_settings(const dynamic::object& o) const {
    using factory = settings::inclusion_directives_settings_factory;
    const factory f(dynamic_repository_, container_);
    return f.make(o);
}

boost::optional<std::pair<std::string, std::string> >
inclusion_directives_factory::obtain_include_directive(
    const std::string& formatter_name,
    const std::string& type_name,
    const std::unordered_map<std::string,
                             formattables::path_derivatives>& pd,
    const settings::inclusion_directive_settings& s) const {

    if (!s.inclusion_required()) {
        BOOST_LOG_SEV(lg, debug) << "Inclusion directive not required. "
                                 << "Type: " << type_name
                                 << " formatter: " << formatter_name;
        return boost::optional<std::pair<std::string, std::string> >();
    }

    if (s.inclusion_directive()) {
        const auto id(*s.inclusion_directive());
        validate_inclusion_directive(id, formatter_name, type_name);
        return std::make_pair(formatter_name, id);
    }

    const auto pdfn(path_derivatives_for_formatter_name(pd, formatter_name));
    const auto id(pdfn.inclusion_directive());
    if (!id) {
        BOOST_LOG_SEV(lg, error) << missing_include_directive
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(
            building_error(missing_include_directive + formatter_name));
    }
    validate_inclusion_directive(*id, formatter_name, type_name);
    return std::make_pair(formatter_name, *id);
}

boost::optional<std::unordered_map<std::string, std::string> >
inclusion_directives_factory::
make(const dynamic::object& o, const tack::name& n) const {
    const auto tn(tack::string_converter::convert(n));
    const auto directives_settings(create_inclusion_directives_settings(o));
    if (!directives_settings.inclusion_required()) {
        BOOST_LOG_SEV(lg, debug) << "Inclusion directive not required: " << tn;
        return boost::optional<std::unordered_map<std::string, std::string> >();
    }

    const auto pd(path_derivatives_for_name(n));
    std::unordered_map<std::string, std::string> r;
    for (const auto& p : directives_settings.inclusion_directive_settings()) {
        const auto fn(p.first);
        const auto ds(p.second);

        const auto id_pair(obtain_include_directive(fn, tn, pd, ds));
        if (!id_pair)
            continue;

        r.insert(*id_pair);
    }
    return r;
}

} } }
