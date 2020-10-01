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
#include "dogen.physical/types/features/path_features.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::physical::features {

namespace {

dogen::variability::entities::feature
make_masd_cpp_headers_output_directory() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("headers_output_directory");
    r.name().qualified("masd.cpp.headers_output_directory");
    r.description(R"(Override location of public c++ headers.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_source_directory_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("source_directory_name");
    r.name().qualified("masd.cpp.source_directory_name");
    r.description(R"(Directory in which to place C++ source files.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "src" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_include_directory_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("include_directory_name");
    r.name().qualified("masd.cpp.include_directory_name");
    r.description(R"(Directory in which to place include headers.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "include" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_tests_directory_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("tests_directory_name");
    r.name().qualified("masd.cpp.tests_directory_name");
    r.description(R"(Directory in which to place c++ tests.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "generated_tests" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_templates_directory_name() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("templates_directory_name");
    r.name().qualified("masd.cpp.templates_directory_name");
    r.description(R"(Directory in which to place text templates.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "templates" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_header_file_extension() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("header_file_extension");
    r.name().qualified("masd.cpp.header_file_extension");
    r.description(R"(Extension to use for C++ header files.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "hpp" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_implementation_file_extension() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("implementation_file_extension");
    r.name().qualified("masd.cpp.implementation_file_extension");
    r.description(R"(Extension to use for C++ implementation files.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "cpp" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_templates_file_extension() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("templates_file_extension");
    r.name().qualified("masd.cpp.templates_file_extension");
    r.description(R"(Extension to use for text templates.

)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "wale" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_enable_unique_file_names() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("enable_unique_file_names");
    r.name().qualified("masd.cpp.enable_unique_file_names");
    r.description(R"(If true, make all file names unique within a model.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));
    return r;
}

dogen::variability::entities::feature
make_masd_cpp_disable_facet_directories() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("disable_facet_directories");
    r.name().qualified("masd.cpp.disable_facet_directories");
    r.description(R"(If true, facet directories will not be used.

)");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "false" }));
    return r;
}

}

path_features::feature_group
path_features::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.headers_output_directory = s.get_by_name("masd.cpp.headers_output_directory");
    r.source_directory_name = s.get_by_name("masd.cpp.source_directory_name");
    r.include_directory_name = s.get_by_name("masd.cpp.include_directory_name");
    r.tests_directory_name = s.get_by_name("masd.cpp.tests_directory_name");
    r.templates_directory_name = s.get_by_name("masd.cpp.templates_directory_name");
    r.header_file_extension = s.get_by_name("masd.cpp.header_file_extension");
    r.implementation_file_extension = s.get_by_name("masd.cpp.implementation_file_extension");
    r.templates_file_extension = s.get_by_name("masd.cpp.templates_file_extension");
    r.enable_unique_file_names = s.get_by_name("masd.cpp.enable_unique_file_names");
    r.disable_facet_directories = s.get_by_name("masd.cpp.disable_facet_directories");

    return r;
}

path_features::static_configuration path_features::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.headers_output_directory))
        r.headers_output_directory = s.get_text_content(fg.headers_output_directory);
    r.source_directory_name = s.get_text_content_or_default(fg.source_directory_name);
    r.include_directory_name = s.get_text_content_or_default(fg.include_directory_name);
    r.tests_directory_name = s.get_text_content_or_default(fg.tests_directory_name);
    r.templates_directory_name = s.get_text_content_or_default(fg.templates_directory_name);
    r.header_file_extension = s.get_text_content_or_default(fg.header_file_extension);
    r.implementation_file_extension = s.get_text_content_or_default(fg.implementation_file_extension);
    r.templates_file_extension = s.get_text_content_or_default(fg.templates_file_extension);
    r.enable_unique_file_names = s.get_boolean_content_or_default(fg.enable_unique_file_names);
    r.disable_facet_directories = s.get_boolean_content_or_default(fg.disable_facet_directories);
    return r;
}

std::list<dogen::variability::entities::feature>
path_features::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_cpp_headers_output_directory());
    r.push_back(make_masd_cpp_source_directory_name());
    r.push_back(make_masd_cpp_include_directory_name());
    r.push_back(make_masd_cpp_tests_directory_name());
    r.push_back(make_masd_cpp_templates_directory_name());
    r.push_back(make_masd_cpp_header_file_extension());
    r.push_back(make_masd_cpp_implementation_file_extension());
    r.push_back(make_masd_cpp_templates_file_extension());
    r.push_back(make_masd_cpp_enable_unique_file_names());
    r.push_back(make_masd_cpp_disable_facet_directories());
    return r;
}

}
