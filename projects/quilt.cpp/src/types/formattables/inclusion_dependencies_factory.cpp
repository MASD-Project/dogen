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

template<typename YarnEntity>
std::unordered_map<std::string, std::list<std::string> >
generate(const inclusion_dependencies_builder_factory& f,
    const std::forward_list<boost::shared_ptr<provider_interface<YarnEntity>>>&
    providers, const YarnEntity& e) {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Creating inclusion dependencies for: " << id;

    std::unordered_map<std::string, std::list<std::string> > r;
    for (const auto p : providers) {
        BOOST_LOG_SEV(lg, debug) << "Providing for: " << p->formatter_name();
        auto deps(p->provide_inclusion_dependencies(f, e));

        if (deps.empty())
            continue;

        deps.sort(include_directive_comparer);
        deps.unique();
        const auto id_pair(std::make_pair(p->formatter_name(), deps));
        const bool inserted(r.insert(id_pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name
                                     << p->formatter_name()
                                     << " for type: " << id;
            BOOST_THROW_EXCEPTION(
                building_error(duplicate_formatter_name + p->formatter_name()));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies for: "
                             << id;

    return r;
}

inclusion_dependencies_factory::inclusion_dependencies_factory(
    const inclusion_dependencies_builder_factory& f, const container& c)
    : factory_(f), container_(c) {}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const yarn::module& /*m*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const yarn::concept& /*c*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const yarn::primitive& /*p*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const yarn::enumeration& e) const {
    return generate(factory_, container_.enumeration_providers(), e);
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const yarn::object& o) const {
    return generate(factory_, container_.object_providers(), o);
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const yarn::exception& e) const {
    return generate(factory_, container_.exception_providers(), e);
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const yarn::visitor& v) const {
    return generate(factory_, container_.visitor_providers(), v);
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const fabric::registrar& rg) const {
    return generate(factory_, container_.registrar_providers(), rg);
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const fabric::master_header& mh) const {
    return generate(factory_, container_.master_header_providers(), mh);
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::
make(const fabric::forward_declarations& fd) const {
    return generate(factory_, container_.forward_declarations_providers(), fd);
}

} } } }
