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
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.generation.cpp/types/formatters/odb/features.hpp"

namespace dogen::generation::cpp::formatters::odb {

namespace {

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_directory() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("directory");
    r.name().qualified("masd.generation.cpp.odb.directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "odb" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "pragmas" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_class_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.class_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_enum_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.enum_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_primitive_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.primitive_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_common_odb_options_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.common_odb_options.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_object_odb_options_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.object_odb_options.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_master_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.master_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_pragma() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("pragma");
    r.name().qualified("masd.generation.cpp.odb.pragma");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_builtin_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.builtin_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_odb_primitive_odb_options_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.odb.primitive_odb_options.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

}


std::list<dogen::variability::meta_model::feature>
features::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_generation_cpp_odb_directory());
    r.push_back(make_masd_generation_cpp_odb_postfix());
    r.push_back(make_masd_generation_cpp_odb_class_header_postfix());
    r.push_back(make_masd_generation_cpp_odb_enum_header_postfix());
    r.push_back(make_masd_generation_cpp_odb_primitive_header_postfix());
    r.push_back(make_masd_generation_cpp_odb_common_odb_options_postfix());
    r.push_back(make_masd_generation_cpp_odb_object_odb_options_postfix());
    r.push_back(make_masd_generation_cpp_odb_master_header_postfix());
    r.push_back(make_masd_generation_cpp_odb_pragma());
    r.push_back(make_masd_generation_cpp_odb_builtin_header_postfix());
    r.push_back(make_masd_generation_cpp_odb_primitive_odb_options_postfix());
    return r;
}

}
