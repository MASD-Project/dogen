/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/modeling/primitive_model_factory.hpp"

namespace {
const std::string model_name("primitive_model");

const std::string bool_name("bool");
const std::string char_name("char");
const std::string uchar_name("unsigned char");
const std::string int_name("int");
const std::string uint_name("unsigned int");
const std::string long_name("long");
const std::string ulong_name("unsigned long");
const std::string long_long_name("long long");
const std::string ulong_long_name("unsigned long long");
const std::string short_name("short");
const std::string ushort_name("unsigned short");

}


namespace dogen {
namespace generator {
namespace modeling {

sml::primitive primitive_model_factory::create(std::string name) {
    sml::qualified_name q;
    q.type_name(name);
    q.meta_type(sml::meta_types::primitive);
    sml::primitive r;
    r.name(q);
    return r;
}

sml::model primitive_model_factory::create() {
    using namespace sml;
    std::unordered_map<qualified_name, primitive> p;
    const auto lambda([&](std::string name){
            primitive prim(create(name));
            p.insert(std::make_pair(prim.name(), prim));
        });

    lambda(bool_name);
    lambda(char_name);
    lambda(uchar_name);
    lambda(int_name);
    lambda(uint_name);
    lambda(long_name);
    lambda(ulong_name);
    lambda(long_long_name);
    lambda(ulong_long_name);
    lambda(short_name);
    lambda(ushort_name);

    model r;
    r.name(model_name);
    r.primitives(p);
    return r;
}

} } }
