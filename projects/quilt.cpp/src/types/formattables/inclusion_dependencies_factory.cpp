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
#include <typeindex>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formattables.inclusion_dependencies_factory"));

const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string empty_include_directive("Include directive is empty.");

const char angle_bracket('<');
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

bool include_directive_comparer(
    const std::string& lhs, const std::string& rhs) {
    if (lhs.empty() || rhs.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_include_directive;
        using dogen::quilt::cpp::formattables::building_error;
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

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inclusion_dependencies_factory::inclusion_dependencies_factory(
    const inclusion_dependencies_builder_factory& f,
    const formatters::container& fc)
    : factory_(f), formatter_container_(fc) {}

std::unordered_map<std::string, std::list<std::string>>
inclusion_dependencies_factory::make(const yarn::element& e) const {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Creating inclusion dependencies for: " << id;

    std::unordered_map<std::string, std::list<std::string> > r;
    const auto ti(std::type_index(typeid(e)));
    const auto i(formatter_container_.file_formatters_by_type_index().find(ti));
    if (i == formatter_container_.file_formatters_by_type_index().end()) {
        BOOST_LOG_SEV(lg, error) << "No formatters for type: " << ti.name();
        return r;
    }

    for (const auto fmt : i->second) {
        const auto fmtn(fmt->ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Providing for: " << fmtn;
        auto deps(fmt->inclusion_dependencies(factory_, e));

        if (deps.empty())
            continue;

        deps.sort(include_directive_comparer);
        deps.unique();
        const auto id_pair(std::make_pair(fmtn, deps));
        const bool inserted(r.insert(id_pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name << fmtn
                                     << " for type: " << id;
            BOOST_THROW_EXCEPTION(
                building_error(duplicate_formatter_name + fmtn));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies for: "
                             << id;
    return r;
}

} } } }
