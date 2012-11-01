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
    return r;
}

sml::pod std_model_factory::
create_pod(const std::string& name, bool is_sequence, bool is_associative) {
    sml::qualified_name q;
    q.type_name(name);
    q.meta_type(sml::meta_types::pod);
    q.model_name(model_name);
    sml::pod r;
    r.name(q);
    if (is_sequence)
        r.number_of_type_arguments(1);
    else if (is_associative)
        r.number_of_type_arguments(2);

    r.is_sequence_container(is_sequence);
    r.is_associative_container(is_associative);
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

    const auto pi([&](std::string name, bool is_sequence, bool is_associative) {
            pod p(create_pod(name, is_sequence, is_associative));
            pods.insert(std::make_pair(p.name(), p));
        });

    pi(string_name, false, false);
    pi(vector_name, true, false);
    pi(deque_name, true, false);
    pi(array_name, true, false);
    pi(list_name, true, false);
    pi(forward_list_name, true, false);

    pi(set_name, false, true);
    pi(multiset_name, false, true);
    pi(unordered_set_name, false, true);
    pi(unordered_multiset_name, false, true);
    pi(map_name, false, true);
    pi(multimap_name, false, true);
    pi(unordered_map_name, false, true);

    model r;
    r.name(model_name);
    r.primitives(primitives);
    r.pods(pods);
    return r;
}

} } }
