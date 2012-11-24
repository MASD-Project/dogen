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
#include "dogen/generator/modeling/std_model_factory.hpp"

namespace {
const std::string model_name("std");
const std::string string_name("string");
const std::string vector_name("vector");
const std::string deque_name("deque");
const std::string array_name("array");
const std::string list_name("list");
const std::string forward_list_name("forward_list");
const std::string set_name("set");
const std::string multiset_name("multiset");
const std::string unordered_set_name("unordered_set");
const std::string unordered_multiset_name("unordered_multiset");
const std::string map_name("map");
const std::string multimap_name("multimap");
const std::string unordered_map_name("unordered_map");
const std::string unordered_multimap_name("unordered_multimap");

}


namespace dogen {
namespace generator {
namespace modeling {

sml::primitive std_model_factory::create_primitive(const std::string& name) {
    sml::qualified_name q;
    q.type_name(name);
    q.meta_type(sml::meta_types::primitive);
    q.model_name(model_name);
    sml::primitive r;
    r.name(q);
    r.generation_type(sml::generation_types::no_generation);
    return r;
}

sml::pod std_model_factory::
create_pod(const std::string& name, sml::pod_types pt) {
    sml::qualified_name q;
    q.type_name(name);
    q.meta_type(sml::meta_types::pod);
    q.model_name(model_name);
    sml::pod r;
    r.name(q);
    r.generation_type(sml::generation_types::no_generation);
    if (pt == sml::pod_types::sequence_container)
        r.number_of_type_arguments(1);
    else if (pt == sml::pod_types::associative_container)
        r.number_of_type_arguments(2);

    r.pod_type(pt);
    return r;
}

sml::model std_model_factory::create() {
    using namespace sml;
    std::unordered_map<qualified_name, primitive> primitives;
    std::unordered_map<qualified_name, pod> pods;

    // const auto lambda([&](std::string name){
    //         primitive p(create_primitive(name));
    //         primitives.insert(std::make_pair(p.name(), p));
    //     });

    const auto pi([&](std::string name, sml::pod_types pt) {
            pod p(create_pod(name, pt));
            pods.insert(std::make_pair(p.name(), p));
        });

    pi(string_name, sml::pod_types::value);
    pi(vector_name, sml::pod_types::sequence_container);
    pi(deque_name, sml::pod_types::sequence_container);
    pi(array_name, sml::pod_types::sequence_container);
    pi(list_name, sml::pod_types::sequence_container);
    pi(forward_list_name, sml::pod_types::sequence_container);

    pi(set_name, sml::pod_types::associative_container);
    pi(multiset_name, sml::pod_types::associative_container);
    pi(unordered_set_name, sml::pod_types::associative_container);
    pi(unordered_multiset_name, sml::pod_types::associative_container);
    pi(map_name, sml::pod_types::associative_container);
    pi(multimap_name, sml::pod_types::associative_container);
    pi(unordered_map_name, sml::pod_types::associative_container);

    model r;
    r.name(model_name);
    r.primitives(primitives);
    r.pods(pods);
    r.is_system(true);
    return r;
}

} } }
