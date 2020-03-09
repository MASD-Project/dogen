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
#include "dogen.generation.cpp/types/formatters/visual_studio/features.hpp"

namespace dogen::generation::cpp::formatters::visual_studio {

namespace {

dogen::variability::meta_model::feature
make_masd_generation_cpp_visual_studio_directory() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("directory");
    r.name().qualified("masd.generation.cpp.visual_studio.directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_visual_studio_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.visual_studio.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_visual_studio_solution_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.visual_studio.solution.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_visual_studio_project_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.visual_studio.project.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

dogen::variability::meta_model::feature
make_masd_generation_cpp_visual_studio_msbuild_targets_postfix() {
    using namespace dogen::variability::meta_model;
    feature r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.visual_studio.msbuild_targets.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

    r.location(al);
    return r;
}

}


std::list<dogen::variability::meta_model::feature>
features::make_features() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature> r;
    r.push_back(make_masd_generation_cpp_visual_studio_directory());
    r.push_back(make_masd_generation_cpp_visual_studio_postfix());
    r.push_back(make_masd_generation_cpp_visual_studio_solution_postfix());
    r.push_back(make_masd_generation_cpp_visual_studio_project_postfix());
    r.push_back(make_masd_generation_cpp_visual_studio_msbuild_targets_postfix());
    return r;
}

}
