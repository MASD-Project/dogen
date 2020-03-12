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
#include "dogen.generation.cpp/types/formatters/types/features.hpp"

namespace dogen::generation::cpp::formatters::types {

namespace {

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_directory() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("directory");
    r.name().qualified("masd.generation.cpp.types.directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "types" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_class_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.class_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_class_implementation_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.class_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_enum_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.enum_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_enum_implementation_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.enum_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_primitive_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.primitive_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_primitive_implementation_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.primitive_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_exception_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.exception_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_namespace_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.namespace_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_visitor_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.visitor_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_class_forward_declarations_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.class_forward_declarations.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "fwd" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_visitor_forward_declarations_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.visitor_forward_declarations.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "fwd" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_primitive_forward_declarations_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.primitive_forward_declarations.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "fwd" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_master_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.master_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_builtin_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.builtin_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_feature_template_bundle_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.feature_template_bundle_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_feature_template_bundle_implementation_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.feature_template_bundle_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_feature_bundle_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.feature_bundle_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_feature_bundle_implementation_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.feature_bundle_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_variability_initializer_header_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.variability_initializer_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_variability_initializer_implementation_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.variability_initializer_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_types_main_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.types.main.postfix");
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
    r.push_back(make_masd_generation_cpp_types_directory());
    r.push_back(make_masd_generation_cpp_types_postfix());
    r.push_back(make_masd_generation_cpp_types_class_header_postfix());
    r.push_back(make_masd_generation_cpp_types_class_implementation_postfix());
    r.push_back(make_masd_generation_cpp_types_enum_header_postfix());
    r.push_back(make_masd_generation_cpp_types_enum_implementation_postfix());
    r.push_back(make_masd_generation_cpp_types_primitive_header_postfix());
    r.push_back(make_masd_generation_cpp_types_primitive_implementation_postfix());
    r.push_back(make_masd_generation_cpp_types_exception_header_postfix());
    r.push_back(make_masd_generation_cpp_types_namespace_header_postfix());
    r.push_back(make_masd_generation_cpp_types_visitor_header_postfix());
    r.push_back(make_masd_generation_cpp_types_class_forward_declarations_postfix());
    r.push_back(make_masd_generation_cpp_types_visitor_forward_declarations_postfix());
    r.push_back(make_masd_generation_cpp_types_primitive_forward_declarations_postfix());
    r.push_back(make_masd_generation_cpp_types_master_header_postfix());
    r.push_back(make_masd_generation_cpp_types_builtin_header_postfix());
    r.push_back(make_masd_generation_cpp_types_feature_template_bundle_header_postfix());
    r.push_back(make_masd_generation_cpp_types_feature_template_bundle_implementation_postfix());
    r.push_back(make_masd_generation_cpp_types_feature_bundle_header_postfix());
    r.push_back(make_masd_generation_cpp_types_feature_bundle_implementation_postfix());
    r.push_back(make_masd_generation_cpp_types_variability_initializer_header_postfix());
    r.push_back(make_masd_generation_cpp_types_variability_initializer_implementation_postfix());
    r.push_back(make_masd_generation_cpp_types_main_postfix());
    return r;
}

}
