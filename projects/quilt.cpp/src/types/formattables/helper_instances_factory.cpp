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
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/io/settings/helper_settings_io.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_instances_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.helper_instances_factory"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

helper_instances_factory::helper_instances_factory(
    const settings::helper_settings_repository& hsrp) : helper_settings_(hsrp) {
}

void helper_instances_factory::make(const yarn::name_tree& nt,
    std::list<helper_instance>& instances,
    std::unordered_set<std::string>& types_done) const {

    // FIXME: make types done state, as a map, of helper instance
    // properties; factory non-const
    
    BOOST_LOG_SEV(lg, debug) << "Processing type: "
                             << nt.parent().qualified();

    if (types_done.find(nt.parent().qualified()) != types_done.end()) {
        BOOST_LOG_SEV(lg, debug) << "Type already done.";
        return;
    }

    for (const auto c : nt.children())
        make(c, instances, types_done);

    const auto& hsbn(helper_settings_.helper_settings_by_name());
    const auto i(hsbn.find(nt.parent().qualified()));
    if (i == hsbn.end()) {
        BOOST_LOG_SEV(lg, debug) << "No settings for type.";
        return;
    }

    const auto& hs(i->second);
    BOOST_LOG_SEV(lg, debug) << "helper settings: " << hs;
    helper_instance hi;
    hi.settings(hs);
    instances.push_back(hi);
}

std::list<helper_instance> helper_instances_factory::
make(const std::list<yarn::property>& properties) const {    
    std::list<helper_instance> r;

    if (properties.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No properties found.";
        return r;
    }

    std::unordered_set<std::string> types_done;
    BOOST_LOG_SEV(lg, debug) << "Properties found: " << properties.size();
    for (const auto p : properties)
        make(p.parsed_type(), r, types_done);

    return r;
}

} } } }
