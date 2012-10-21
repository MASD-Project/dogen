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

sml::pod std_model_factory::create_pod(const std::string& name) {
    sml::qualified_name q;
    q.type_name(name);
    q.meta_type(sml::meta_types::pod);
    q.model_name(model_name);
    sml::pod r;
    r.name(q);
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

    const auto pi([&](std::string name){
            pod p(create_pod(name));
            pods.insert(std::make_pair(p.name(), p));
        });

    pi(string_name);

    model r;
    r.name(model_name);
    r.primitives(primitives);
    r.pods(pods);
    return r;
}

} } }
