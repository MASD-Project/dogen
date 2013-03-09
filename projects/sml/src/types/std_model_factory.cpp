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
#include "dogen/sml/types/std_model_factory.hpp"

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
const std::string pair_name("pair");

const std::string shared_ptr_name("shared_ptr");
const std::string unique_ptr_name("unique_ptr");
const std::string weak_ptr_name("weak_ptr");

const std::string function_name("function");

const std::string int8_t_name("int8_t");
const std::string int16_t_name("int16_t");
const std::string int32_t_name("int32_t");
const std::string int64_t_name("int64_t");
const std::string uint8_t_name("uint8_t");
const std::string uint16_t_name("uint16_t");
const std::string uint32_t_name("uint32_t");
const std::string uint64_t_name("uint64_t");

}

namespace dogen {
namespace sml {

primitive std_model_factory::create_primitive(const std::string& name) {
    qname q;
    q.type_name(name);
    q.meta_type(meta_types::primitive);
    q.model_name(model_name);
    primitive r;
    r.name(q);
    r.generation_type(generation_types::no_generation);
    return r;
}

pod std_model_factory::
create_pod(const std::string& name, pod_types pt) {
    qname q;
    q.type_name(name);
    q.meta_type(meta_types::pod);
    q.model_name(model_name);
    pod r;
    r.name(q);
    r.generation_type(generation_types::no_generation);
    if (pt == pod_types::sequence_container)
        r.number_of_type_arguments(1);
    else if (pt == pod_types::associative_container)
        r.number_of_type_arguments(2);

    r.pod_type(pt);
    return r;
}

model std_model_factory::create() {
    using namespace sml;
    std::unordered_map<qname, primitive> primitives;
    std::unordered_map<qname, pod> pods;

    const auto lambda([&](std::string name){
            primitive p(create_primitive(name));
            primitives.insert(std::make_pair(p.name(), p));
        });

    const auto pi([&](std::string name, pod_types pt) {
            pod p(create_pod(name, pt));
            pods.insert(std::make_pair(p.name(), p));
        });

    lambda(int8_t_name);
    lambda(int16_t_name);
    lambda(int32_t_name);
    lambda(int64_t_name);
    lambda(uint8_t_name);
    lambda(uint16_t_name);
    lambda(uint32_t_name);
    lambda(uint64_t_name);

    pi(string_name, pod_types::value);
    pi(vector_name, pod_types::sequence_container);
    pi(deque_name, pod_types::sequence_container);
    pi(array_name, pod_types::sequence_container);
    pi(list_name, pod_types::sequence_container);
    pi(forward_list_name, pod_types::sequence_container);

    pi(set_name, pod_types::associative_container);
    pi(multiset_name, pod_types::associative_container);
    pi(unordered_set_name, pod_types::associative_container);
    pi(unordered_multiset_name, pod_types::associative_container);
    pi(map_name, pod_types::associative_container);
    pi(multimap_name, pod_types::associative_container);
    pi(unordered_map_name, pod_types::associative_container);
    pi(pair_name, pod_types::value);

    pi(shared_ptr_name, pod_types::smart_pointer);
    pi(weak_ptr_name, pod_types::smart_pointer);
    pi(unique_ptr_name, pod_types::smart_pointer);

    pi(function_name, pod_types::value);

    model r;
    r.name(model_name);
    r.primitives(primitives);
    r.pods(pods);
    r.is_system(true);
    return r;
}

} }
