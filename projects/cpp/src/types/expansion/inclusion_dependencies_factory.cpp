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
#include "dogen/cpp/types/expansion/building_error.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("cpp.expansion.inclusion_dependencies_factory"));

const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string empty_formatter_name("Formatter name is empty.");
const std::string empty_include_directive("Include directive is empty.");

const char angle_bracket('<');
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

}

namespace dogen {
namespace cpp {
namespace expansion {

bool include_directive_comparer(
    const std::string& lhs, const std::string& rhs) {
    if (lhs.empty() || rhs.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_include_directive;
        BOOST_THROW_EXCEPTION(building_error(empty_include_directive));
    }

    const bool lhs_has_angle_brackets(lhs[0] == angle_bracket);
    const bool rhs_has_angle_brackets(rhs[0] == angle_bracket);

    if (lhs_has_angle_brackets && !rhs_has_angle_brackets)
        return true;

    if (!lhs_has_angle_brackets && rhs_has_angle_brackets)
        return false;

    if (lhs_has_angle_brackets && rhs_has_angle_brackets) {
        const auto npos(std::string::npos);
        const bool lhs_is_boost(lhs.find_first_of(boost_name) != npos);
        const bool rhs_is_boost(rhs.find_first_of(boost_name) != npos);
        if (!lhs_is_boost && rhs_is_boost)
            return false;

        if (lhs_is_boost && !rhs_is_boost)
            return true;

        // FIXME: hacks for headers that must be last
        const bool lhs_is_gregorian(
            lhs.find_first_of(boost_serialization_gregorian) != npos);
        const bool rhs_is_gregorian(
            rhs.find_first_of(boost_serialization_gregorian) != npos);
        if (lhs_is_gregorian && !rhs_is_gregorian)
            return true;

        if (!lhs_is_gregorian && rhs_is_gregorian)
            return false;
    }

    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    return lhs < rhs;
}

inclusion_dependencies_factory::
inclusion_dependencies_factory(const dynamic::schema::repository& rp,
    const container& c, const std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, std::string>
    >& inclusion_directives)
  : repository_(rp), container_(c),
    inclusion_directives_(inclusion_directives) { }

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const dogen::sml::object& o) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    for (const auto p : container_.object_providers()) {
        auto idf(p->provide(repository_, inclusion_directives_, o));

        if (!idf)
            continue;

        if (idf->formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        auto id(idf->inclusion_dependencies());
        id.sort(include_directive_comparer);

        const auto result(r.insert(std::make_pair(idf->formatter_name(), id)));
        if (!result.second) {
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name
                                     << idf->formatter_name()
                                     << " for type: " << n;
            BOOST_THROW_EXCEPTION(building_error(duplicate_formatter_name +
                    idf->formatter_name()));
        }
    }
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::
make(const dogen::sml::enumeration& /*e*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const dogen::sml::primitive& /*p*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const dogen::sml::module& /*m*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const dogen::sml::concept& /*c*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

} } }
