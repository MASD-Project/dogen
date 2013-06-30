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
#include <memory>
#include "dogen/sml/types/value_object.hpp"
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
    q.simple_name(name);
    q.model_name(model_name);

    primitive r;
    r.name(q);
    r.generation_type(generation_types::no_generation);
    return r;
}

boost::shared_ptr<abstract_object> std_model_factory::create_value_object(
    const std::string& name, value_object_types t) {

    qname q;
    q.simple_name(name);
    q.model_name(model_name);

    std::unique_ptr<value_object> r(new value_object());
    r->name(q);
    r->generation_type(generation_types::no_generation);
    r->type(t);
    if (t == value_object_types::sequence_container)
        r->number_of_type_arguments(1);
    else if (t == value_object_types::associative_container)
        r->number_of_type_arguments(2);

    return boost::shared_ptr<abstract_object>(r.release());
}

model std_model_factory::create() {
    qname qn;
    qn.model_name(model_name);

    model r;
    r.name(qn);
    r.is_system(true);

    const auto lambda([&](const std::string& name){
            const auto p(create_primitive(name));
            r.primitives().insert(std::make_pair(p.name(), p));
        });

    const auto pi([&](const std::string& name, value_object_types vot) {
            const auto vo(create_value_object(name, vot));
            r.objects().insert(std::make_pair(vo->name(), vo));
        });

    lambda(int8_t_name);
    lambda(int16_t_name);
    lambda(int32_t_name);
    lambda(int64_t_name);
    lambda(uint8_t_name);
    lambda(uint16_t_name);
    lambda(uint32_t_name);
    lambda(uint64_t_name);

    pi(string_name, value_object_types::plain);
    pi(vector_name, value_object_types::sequence_container);
    pi(deque_name, value_object_types::sequence_container);
    pi(array_name, value_object_types::sequence_container);
    pi(list_name, value_object_types::sequence_container);
    pi(forward_list_name, value_object_types::sequence_container);

    pi(set_name, value_object_types::associative_container);
    pi(multiset_name, value_object_types::associative_container);
    pi(unordered_set_name, value_object_types::associative_container);
    pi(unordered_multiset_name, value_object_types::associative_container);
    pi(map_name, value_object_types::associative_container);
    pi(multimap_name, value_object_types::associative_container);
    pi(unordered_map_name, value_object_types::associative_container);
    pi(pair_name, value_object_types::plain);

    pi(shared_ptr_name, value_object_types::smart_pointer);
    pi(weak_ptr_name, value_object_types::smart_pointer);
    pi(unique_ptr_name, value_object_types::smart_pointer);

    pi(function_name, value_object_types::plain);

    return r;
}

} }
