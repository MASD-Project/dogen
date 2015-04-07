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

}

namespace dogen {
namespace cpp {
namespace expansion {

inclusion_dependencies_factory::
inclusion_dependencies_factory(const dynamic::schema::repository& rp,
    const container& c, const std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, expansion::path_derivatives>
    >& pd)
    : repository_(rp), container_(c), path_derivatives_(pd) { }

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const dogen::sml::object& o) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    for (const auto p : container_.object_providers()) {
        const auto pair(p->provide(repository_, path_derivatives_, o));

        if (pair.first.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        const auto result(r.insert(pair));
        if (!result.second) {
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name << pair.first
                                     << " for type: " << n;
            BOOST_THROW_EXCEPTION(
                building_error(duplicate_formatter_name + pair.first));
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
