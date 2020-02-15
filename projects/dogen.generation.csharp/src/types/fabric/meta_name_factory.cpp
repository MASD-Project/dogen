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
#include "dogen.assets/types/helpers/name_builder.hpp"
#include "dogen.generation.csharp/types/fabric/meta_name_factory.hpp"

namespace dogen::generation::csharp::fabric {

assets::meta_model::location meta_name_factory::make_location() {
    assets::meta_model::location r;
    r.external_modules().push_back("dogen");
    r.model_modules().push_back("generation");
    r.model_modules().push_back("csharp");
    r.internal_modules().push_back("fabric");
    return r;
}

assets::meta_model::name meta_name_factory::make_name(const std::string& sn) {
    static const auto l(make_location());
    assets::helpers::name_builder b;
    b.location(l);
    b.simple_name(sn);
    return b.build();
}

assets::meta_model::name meta_name_factory::make_assistant_name() {
    return make_name("assistant");
}

assets::meta_model::name meta_name_factory::make_visual_studio_project_name() {
    return make_name("visual_studio_project");
}

assets::meta_model::name meta_name_factory::make_visual_studio_solution_name() {
    return make_name("visual_studio_solution");
}

}
