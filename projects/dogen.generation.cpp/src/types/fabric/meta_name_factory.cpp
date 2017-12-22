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
#include "dogen.modeling/types/helpers/name_builder.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"

namespace dogen {
namespace generation {
namespace cpp {
namespace fabric {

modeling::meta_model::location meta_name_factory::make_location() {
    modeling::meta_model::location r;
    r.external_modules().push_back("dogen");
    r.model_modules().push_back("generation");
    r.model_modules().push_back("cpp");
    r.internal_modules().push_back("fabric");
    return r;
}

modeling::meta_model::name meta_name_factory::make_name(const std::string& sn) {
    static const auto l(make_location());
    modeling::helpers::name_builder b;
    b.location(l);
    b.simple_name(sn);
    return b.build();
}

modeling::meta_model::name meta_name_factory::make_cmakelists_name() {
    static const auto r(make_name("cmakelists"));
    return r;
}

modeling::meta_model::name meta_name_factory::make_master_header_name() {
    static const auto r(make_name("maste_header"));
    return r;
}

modeling::meta_model::name meta_name_factory::make_msbuild_targets_name() {
    static const auto r(make_name("msbuild_targets"));
    return r;
}

modeling::meta_model::name meta_name_factory::make_visual_studio_project_name() {
    static const auto r(make_name("visual_studio_project"));
    return r;
}

modeling::meta_model::name meta_name_factory::make_visual_studio_solution_name() {
    static const auto r(make_name("visual_studio_solution"));
    return r;
}

modeling::meta_model::name meta_name_factory::make_common_odb_options_name() {
    static const auto r(make_name("common_odb_options"));
    return r;
}

modeling::meta_model::name meta_name_factory::make_object_odb_options_name() {
    static const auto r(make_name("object_odb_options"));
    return r;
}

modeling::meta_model::name meta_name_factory::make_registrar_name() {
    static const auto r(make_name("registrar"));
    return r;
}

modeling::meta_model::name meta_name_factory::make_forward_declarations_name() {
    static const auto r(make_name("forward_declarations"));
    return r;
}

} } } }
