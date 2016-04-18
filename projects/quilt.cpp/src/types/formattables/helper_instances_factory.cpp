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
#include <unordered_set>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/io/settings/helper_settings_io.hpp"
#include "dogen/quilt.cpp/types/formattables/name_builder.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_instances_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.helper_instances_factory"));

const char less_than('<');
const char greater_than('>');

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

helper_instances_factory::helper_instances_factory(
    const settings::helper_settings_repository& hsrp) : helper_settings_(hsrp) {
}

boost::optional<helper_instance_properties>
helper_instances_factory::make(const yarn::name_tree& nt,
    std::string& complete_name, std::list<helper_instance>& instances) const {

    const auto qn(nt.parent().qualified());
    BOOST_LOG_SEV(lg, debug) << "Processing type: " << qn;

    std::string my_complete_name(nt.parent().simple());
    auto lambda([&](char c) {
            if (nt.children().empty())
                return;

            /* Add a space between template markers. Not really
             * required for C++ 11 and above, but we will leave it for
             * now to avoid spurious differences.
             */
            if (my_complete_name[my_complete_name.length() - 1] == c)
                my_complete_name += " ";

            my_complete_name += c;
        });

    lambda(less_than);
    helper_instance hi;
    bool is_first(true);
    for (const auto c : nt.children()) {
        if (!is_first)
            my_complete_name += ", ";

        const auto child_properties(make(c, my_complete_name, instances));
        if (child_properties)
            hi.associated_helpers().push_back(*child_properties);

        is_first = false;
    }
    lambda(greater_than);

    const auto& hsbn(helper_settings_.helper_settings_by_name());
    const auto i(hsbn.find(qn));
    if (i == hsbn.end()) {
        BOOST_LOG_SEV(lg, debug) << "No settings for type.";
        return boost::optional<helper_instance_properties>();
    }

    const auto& hs(i->second);
    BOOST_LOG_SEV(lg, debug) << "Helper settings: " << hs;
    hi.settings(hs);

    name_builder b;
    helper_instance_properties properties;
    properties.identifiable_name(b.identifiable_name(qn));
    properties.complete_name(my_complete_name);
    properties.complete_identifiable_name(
        b.identifiable_name(my_complete_name));
    hi.properties(properties);

    instances.push_back(hi);
    complete_name += my_complete_name;

    return properties;
}

std::list<helper_instance> helper_instances_factory::
make(const std::list<yarn::property>& properties) const {

    if (properties.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No properties found.";
        return std::list<helper_instance>();
    }
    BOOST_LOG_SEV(lg, debug) << "Properties found: " << properties.size();

    std::list<helper_instance> instances;
    for (const auto p : properties) {
        std::string complete_name;
        make(p.parsed_type(), complete_name, instances);
    }

    std::list<helper_instance> r;
    std::unordered_set<std::string> done;
    for (const auto& i : instances) {
        const auto cn(i.properties().complete_name());
        if (done.find(cn) == done.end())
            continue;

        r.push_back(i);
        done.insert(cn);
    }

    return r;
}

} } } }
