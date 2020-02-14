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
#include "dogen.generation.cpp/types/formatters/global_features.hpp"

namespace dogen::generation::cpp::formatters {

namespace {

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_headers_output_directory() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("cpp_headers_output_directory");
    r.name().qualified("masd.generation.cpp_headers_output_directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_directory() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("directory");
    r.name().qualified("masd.generation.cpp.directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "cpp" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_inclusion_required() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("inclusion_required");
    r.name().qualified("masd.generation.cpp.inclusion_required");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_source_directory_name() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("source_directory_name");
    r.name().qualified("masd.generation.cpp.source_directory_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "src" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_include_directory_name() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("include_directory_name");
    r.name().qualified("masd.generation.cpp.include_directory_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "include" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_tests_directory_name() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("tests_directory_name");
    r.name().qualified("masd.generation.cpp.tests_directory_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "generated_tests" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_templates_directory_name() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("templates_directory_name");
    r.name().qualified("masd.generation.cpp.templates_directory_name");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "templates" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_header_file_extension() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("header_file_extension");
    r.name().qualified("masd.generation.cpp.header_file_extension");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "hpp" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_implementation_file_extension() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("implementation_file_extension");
    r.name().qualified("masd.generation.cpp.implementation_file_extension");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "cpp" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_templates_file_extension() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("templates_file_extension");
    r.name().qualified("masd.generation.cpp.templates_file_extension");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "wale" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_enable_unique_file_names() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("enable_unique_file_names");
    r.name().qualified("masd.generation.cpp.enable_unique_file_names");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_aspect_requires_manual_default_constructor() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("requires_manual_default_constructor");
    r.name().qualified("masd.generation.cpp.aspect.requires_manual_default_constructor");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_aspect_requires_manual_move_constructor() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("requires_manual_move_constructor");
    r.name().qualified("masd.generation.cpp.aspect.requires_manual_move_constructor");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_aspect_requires_stream_manipulators() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("requires_stream_manipulators");
    r.name().qualified("masd.generation.cpp.aspect.requires_stream_manipulators");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_disable_facet_directories() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("disable_facet_directories");
    r.name().qualified("masd.generation.cpp.disable_facet_directories");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_standard() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("standard");
    r.name().qualified("masd.generation.cpp.standard");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "c++-14" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_helper_family() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("family");
    r.name().qualified("masd.generation.cpp.helper.family");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "Default" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_streaming_string_conversion_method() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("string_conversion_method");
    r.name().qualified("masd.generation.cpp.streaming.string_conversion_method");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_streaming_requires_quoting() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("requires_quoting");
    r.name().qualified("masd.generation.cpp.streaming.requires_quoting");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_streaming_remove_unprintable_characters() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("remove_unprintable_characters");
    r.name().qualified("masd.generation.cpp.streaming.remove_unprintable_characters");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::element);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_cmake_source_cmakelists_postfix() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.cmake.source_cmakelists.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature_template
make_masd_generation_cpp_cmake_include_cmakelists_postfix() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.cmake.include_cmakelists.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

}


std::list<dogen::variability::meta_model::feature_template>
global_features::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature_template> r;
    r.push_back(make_masd_generation_cpp_headers_output_directory());
    r.push_back(make_masd_generation_cpp_directory());
    r.push_back(make_masd_generation_cpp_inclusion_required());
    r.push_back(make_masd_generation_cpp_source_directory_name());
    r.push_back(make_masd_generation_cpp_include_directory_name());
    r.push_back(make_masd_generation_cpp_tests_directory_name());
    r.push_back(make_masd_generation_cpp_templates_directory_name());
    r.push_back(make_masd_generation_cpp_header_file_extension());
    r.push_back(make_masd_generation_cpp_implementation_file_extension());
    r.push_back(make_masd_generation_cpp_templates_file_extension());
    r.push_back(make_masd_generation_cpp_enable_unique_file_names());
    r.push_back(make_masd_generation_cpp_aspect_requires_manual_default_constructor());
    r.push_back(make_masd_generation_cpp_aspect_requires_manual_move_constructor());
    r.push_back(make_masd_generation_cpp_aspect_requires_stream_manipulators());
    r.push_back(make_masd_generation_cpp_disable_facet_directories());
    r.push_back(make_masd_generation_cpp_standard());
    r.push_back(make_masd_generation_cpp_helper_family());
    r.push_back(make_masd_generation_cpp_streaming_string_conversion_method());
    r.push_back(make_masd_generation_cpp_streaming_requires_quoting());
    r.push_back(make_masd_generation_cpp_streaming_remove_unprintable_characters());
    r.push_back(make_masd_generation_cpp_cmake_source_cmakelists_postfix());
    r.push_back(make_masd_generation_cpp_cmake_include_cmakelists_postfix());
    return r;
}

}
