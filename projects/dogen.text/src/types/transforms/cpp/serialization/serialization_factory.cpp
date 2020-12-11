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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"
#include "dogen.text/types/transforms/cpp/serialization/enum_header_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/path_helper_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/class_header_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/serialization_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/builtin_header_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/primitive_header_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/class_implementation_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/type_registrar_header_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/primitive_implementation_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/class_forward_declarations_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/type_registrar_implementation_factory.hpp"
#include "dogen.text/types/transforms/cpp/serialization/primitive_forward_declarations_factory.hpp"

namespace dogen::text::transforms::cpp::serialization {
namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dogen.text.transforms.cpp.serialization"));

}

physical::entities::facet serialization_factory::make() {
    identification::helpers::physical_meta_name_builder b;
    b.meta_model("masd");
    b.backend("cpp");
    b.facet("serialization");

    physical::entities::facet r;
    r.meta_name(b.build());
    r.directory_name("serialization");
    r.postfix("ser");

    const auto lambda([&](auto& container, const auto& element) {
        const auto id(element.meta_name().id());
        const auto pair(std::make_pair(id, element));
        const auto inserted(container.insert(pair).second);
        if (!inserted) {
            using text::transforms::transformation_error;
            const std::string duplicate_archetype("Duplicate id: ");
            BOOST_LOG_SEV(lg, error) << duplicate_archetype << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_archetype + id.value()));
        }
    });

    lambda(r.archetypes(), builtin_header_factory::make());
    lambda(r.archetypes(), class_forward_declarations_factory::make());
    lambda(r.archetypes(), class_header_factory::make());
    lambda(r.archetypes(), class_implementation_factory::make());
    lambda(r.archetypes(), enum_header_factory::make());
    lambda(r.archetypes(), primitive_forward_declarations_factory::make());
    lambda(r.archetypes(), primitive_header_factory::make());
    lambda(r.archetypes(), primitive_implementation_factory::make());
    lambda(r.archetypes(), type_registrar_header_factory::make());
    lambda(r.archetypes(), type_registrar_implementation_factory::make());

    lambda(r.helpers(), path_helper_factory::make());
    return r;
}

}

