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
#include <ostream>
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.codec/types/transforms/meta_data_transform.hpp"

namespace {

const std::string transform_id("codec.transforms.meta_data_transform");

using namespace dogen::utility::log;
logger lg(logger_factory(transform_id));

}

namespace dogen::codec::transforms {

void meta_data_transform::
apply(const features::meta_data::feature_group& fg, entities::element& e) {
    using features::meta_data;
    using identification::entities::stereotype;

    const auto scfg(meta_data::make_static_configuration(fg, e));
    for (const auto& s : scfg.stereotypes)
        e.stereotypes().emplace_back(s);

    for (const auto& t : scfg.templates)
        e.templates().emplace_back(t);

    for (const auto& c : scfg.configurations)
        e.stereotypes().emplace_back(c);

    for (const auto& p : scfg.parent)
        e.parents().push_back(p);

    if (scfg.can_be_primitive_underlier)
        e.can_be_primitive_underlier(*scfg.can_be_primitive_underlier);

    if (scfg.in_global_module)
        e.in_global_module(*scfg.in_global_module);

    if (scfg.can_be_enumeration_underlier)
        e.can_be_enumeration_underlier(*scfg.can_be_enumeration_underlier);

    if (scfg.is_default_enumeration_type)
        e.is_default_enumeration_type(*scfg.is_default_enumeration_type);

    if (scfg.is_associative_container)
        e.is_associative_container(*scfg.is_associative_container);

    if (scfg.is_floating_point)
        e.is_floating_point(*scfg.is_floating_point);
}

void meta_data_transform::
apply(const features::meta_data::feature_group& fg, entities::attribute& attr) {
    using features::meta_data;

    const auto scfg(meta_data::make_static_configuration(fg, attr));
    if (!scfg.value.empty())
        attr.value(scfg.value);

    if (!scfg.type.empty())
        attr.type(scfg.type);
}

void meta_data_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "meta-data",
        transform_id, m.name().simple(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto fg(features::meta_data::make_feature_group(fm));

    for (auto& e : m.elements()) {
        apply(fg, e);

        for (auto& attr : e.attributes())
            apply(fg, attr);
    }

    stp.end_transform(m);
}

}
