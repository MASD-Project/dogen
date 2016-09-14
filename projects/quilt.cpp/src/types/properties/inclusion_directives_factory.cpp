/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/types/settings/inclusion_directives_settings_factory.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.inclusion_directives_factory"));

const std::string name_not_found("Expected name not found: ");
const std::string empty_include_directive("Include directive is empty.");
const std::string formatter_name_not_found("Formatter name not found: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

inclusion_directives_factory::inclusion_directives_factory(
    const dynamic::repository& srp,
    const formatters::container& fc,
    const path_derivatives_repository& pdrp)
    : dynamic_repository_(srp), container_(fc), path_repository_(pdrp) {}

std::unordered_map<std::string, path_derivatives>
inclusion_directives_factory::path_derivatives_for_name(
    const yarn::name& n) const {
    const auto i(path_repository_.by_name().find(n));
    if (i == path_repository_.by_name().end()) {
        const auto id(n.id());
        BOOST_LOG_SEV(lg, error) << name_not_found << id;
        BOOST_THROW_EXCEPTION(building_error(name_not_found + id));
    }
    return i->second;
}

path_derivatives
inclusion_directives_factory::path_derivatives_for_formatter_name(
    const std::unordered_map<std::string, path_derivatives>& pd,
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
    const std::unordered_map<std::string, path_derivatives>& pd,
    const settings::inclusion_directive_settings& s) const {

    /*
     * Does the type require an inclusion directive for this specific
     * formatter? Some types require inclusion directives for some
     * formatters, but not for others. For example, we may need an
     * include for serialising a std::list, but in test data we make
     * use of helpers and thus do not require an include.
     */
    if (!s.inclusion_required()) {
        BOOST_LOG_SEV(lg, debug) << "Inclusion directive not required. "
                                 << "Type: " << type_name
                                 << " formatter: " << formatter_name;
        return boost::optional<std::pair<std::string, std::string> >();
    }

    /*
     * Do the settings provide a "hard-coded" inclusion directive?
     * That is, the type had an hard-coded incantation for its
     * include. This is the case for system models such as boost, std
     * etc where we can't compute the inclusion directive.
     */
    if (s.inclusion_directive()) {
        const auto id(*s.inclusion_directive());
        validate_inclusion_directive(id, formatter_name, type_name);
        return std::make_pair(formatter_name, id);
    }

    /*
     * Finally, the inclusion directive must have been computed
     * internally by us during path derivatives generation. Find the
     * corresponding derivatives and extract the directive from it.
     */
    const auto pdfn(path_derivatives_for_formatter_name(pd, formatter_name));
    const auto id(pdfn.inclusion_directive());
    validate_inclusion_directive(id, formatter_name, type_name);
    return std::make_pair(formatter_name, id);
}

boost::optional<std::unordered_map<std::string, std::string> >
inclusion_directives_factory::
make(const dynamic::object& o, const yarn::name& n) const {
    const auto id(n.id());

    /*
     * First we extract the configuration for the generation of
     * include directives for this element. Note that we generate
     * directives settings for _all elements_ even if the user did not
     * specify any meta-data.
     */
    const auto directives_settings(create_inclusion_directives_settings(o));

    /*
     * Does this element require any inclusion directives at all,
     * across all facets? Not all elements do; for example bool, int
     * and so on don't require any inclusions at all across all
     * facets. If the user did not override this, we default it to
     * true because normally elements require inclusion.
     */
    if (!directives_settings.inclusion_required()) {
        BOOST_LOG_SEV(lg, debug) << "Inclusion directive not required: " << id;
        return boost::optional<std::unordered_map<std::string, std::string> >();
    }

    /*
     * Now we obtain the path derivatives for this element, by
     * formatter name, which include information about inclusion
     * directives. Then, we loop through the directive settings, per
     * formatter, to obtain the inclusion directives for each
     * formatter - if any. Note that we generate directive settings
     * for _all formatters_ even those for which there were no
     * overrides. This means that many formatters don't make any sense
     * for this element.
     */
    const auto pd(path_derivatives_for_name(n));
    std::unordered_map<std::string, std::string> r;
    for (const auto& p : directives_settings.inclusion_directive_settings()) {
        const auto fn(p.first);
        const auto ds(p.second);

        const auto id_pair(obtain_include_directive(fn, id, pd, ds));
        if (!id_pair)
            continue;

        r.insert(*id_pair);
    }
    return r;
}

} } } }
