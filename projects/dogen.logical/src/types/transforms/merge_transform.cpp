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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/io/entities/input_model_set_io.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/merge_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.merge_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate ID: ");

}

namespace dogen::logical::transforms {

namespace {

/**
 * @brief Copies the associative container across.
 */
template<typename ElementAssociativeContainer>
inline void copy(const ElementAssociativeContainer& src,
    ElementAssociativeContainer& dst) {
    for (const auto& pair : src) {
        const auto id(pair.first);
        const auto inserted(dst.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_id << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_id + id.value()));
        }
    }
}

}

void merge_transform::merge(const entities::model& src, entities::model& dst) {
    /*
     * Skip any reference models for which the input technical_space
     * does not match.
     *
     * FIXME: we should just throw.
     */
    const auto& id(src.name().qualified().dot());
    if (src.input_technical_space() != dst.input_technical_space()) {
        BOOST_LOG_SEV(lg, warn) << "Skipping model as technical space does "
                                << " not match the target's. Model: "
                                << id << " Input technical_space: "
                                << src.input_technical_space();
        return;
    }

    BOOST_LOG_SEV(lg, debug)
        << "Merging source model: '"
        << src.name().qualified().dot()
        << "'. modules: " << src.structural_elements().modules().size()
        << " object templates: "
        << src.structural_elements().object_templates().size()
        << " builtins: " << src.structural_elements().builtins().size()
        << " enumerations: " << src.structural_elements().enumerations().size()
        << " primitives: " << src.structural_elements().primitives().size()
        << " objects: " << src.structural_elements().objects().size()
        << " exceptions: " << src.structural_elements().exceptions().size()
        << " visitors: " << src.structural_elements().visitors().size()
        << " entry points: " << src.structural_elements().entry_points().size()
        << " assistants: " << src.structural_elements().assistants().size()
        << " modeline_groups: "
        << src.decoration_elements().modeline_groups().size()
        << " modeline: " << src.decoration_elements().modelines().size()
        << " generation markers: "
        << src.decoration_elements().generation_markers().size()
        << " licences: " << src.decoration_elements().licences().size()
        << " type registrars: "
        << src.serialization_elements().type_registrars().size()
        << " visual studio solutions: "
        << src.visual_studio_elements().solutions().size()
        << " visual studio projects: "
        << src.visual_studio_elements().projects().size()
        << " visual studio projects: "
        << src.visual_studio_elements().msbuild_targets().size()
        << " ORM common ODB options: "
        << src.orm_elements().common_odb_options().size()
        << " build cmakelists: "
        << src.build_elements().cmakelists().size()
        << " physical backends: "
        << src.physical_elements().backends().size()
        << " physical facets: "
        << src.physical_elements().facets().size()
        << " physical archetypes: "
        << src.physical_elements().archetypes().size()
        << " physical archetype kinds: "
        << src.physical_elements().archetype_kinds().size()
        << " physical parts: "
        << src.physical_elements().parts().size()
        << " logic-less templates: "
        << src.templating_elements().logic_less_templates().size()
        << " streaming properties: "
        << src.streaming_properties().size()
        << " aspect properties: "
        << src.aspect_properties().size()
        << " assistant properties: "
        << src.aspect_properties().size();

    /*
     * Note that we are ignoring some elements, which do not require
     * merging. These are mainly variability related items.
     */
    copy(src.structural_elements().modules(),
        dst.structural_elements().modules());
    copy(src.structural_elements().object_templates(),
        dst.structural_elements().object_templates());
    copy(src.structural_elements().builtins(),
        dst.structural_elements().builtins());
    copy(src.structural_elements().enumerations(),
        dst.structural_elements().enumerations());
    copy(src.structural_elements().primitives(),
        dst.structural_elements().primitives());
    copy(src.structural_elements().objects(),
        dst.structural_elements().objects());
    copy(src.structural_elements().exceptions(),
        dst.structural_elements().exceptions());
    copy(src.structural_elements().visitors(),
        dst.structural_elements().visitors());
    copy(src.structural_elements().entry_points(),
        dst.structural_elements().entry_points());
    copy(src.structural_elements().assistants(),
        dst.structural_elements().assistants());
    copy(src.decoration_elements().modeline_groups(),
        dst.decoration_elements().modeline_groups());
    copy(src.decoration_elements().modelines(),
        dst.decoration_elements().modelines());
    copy(src.decoration_elements().generation_markers(),
        dst.decoration_elements().generation_markers());
    copy(src.decoration_elements().licences(),
        dst.decoration_elements().licences());
    copy(src.mapping_elements().fixed_mappables(),
        dst.mapping_elements().fixed_mappables());
    copy(src.mapping_elements().extensible_mappables(),
        dst.mapping_elements().extensible_mappables());
    copy(src.serialization_elements().type_registrars(),
        dst.serialization_elements().type_registrars());
    copy(src.visual_studio_elements().solutions(),
        dst.visual_studio_elements().solutions());
    copy(src.visual_studio_elements().projects(),
        dst.visual_studio_elements().projects());
    copy(src.visual_studio_elements().msbuild_targets(),
        dst.visual_studio_elements().msbuild_targets());
    copy(src.orm_elements().common_odb_options(),
        dst.orm_elements().common_odb_options());
    copy(src.build_elements().cmakelists(),
        dst.build_elements().cmakelists());
    copy(src.physical_elements().backends(),
        dst.physical_elements().backends());
    copy(src.physical_elements().facets(),
        dst.physical_elements().facets());
    copy(src.physical_elements().archetypes(),
        dst.physical_elements().archetypes());
    copy(src.physical_elements().archetype_kinds(),
        dst.physical_elements().archetype_kinds());
    copy(src.physical_elements().parts(),
        dst.physical_elements().parts());
    copy(src.physical_elements().helpers(),
        dst.physical_elements().helpers());
    copy(src.templating_elements().logic_less_templates(),
        dst.templating_elements().logic_less_templates());
    copy(src.streaming_properties(), dst.streaming_properties());
    copy(src.aspect_properties(), dst.aspect_properties());
    copy(src.assistant_properties(), dst.assistant_properties());

    /*
     * Update the references of the merged model.
     */
    const auto p(std::make_pair(src.name(), src.provenance().model_type()));
    dst.references().insert(p);
}

entities::model merge_transform::merge(const entities::model& target,
    const std::list<entities::model>& refs) {
    /*
     * We start by making a complete copy of the target model, which
     * initialises all of the relevant parts of the merged model such
     * as leaves etc as well as all of the element containers.
     */
    auto r(target);

    /*
     * Now we push all of the references into the merged model.
     */
    for (const auto& ref : refs)
        merge(ref, r);

    return r;
}

entities::model merge_transform::apply(const context &ctx,
    const logical::entities::input_model_set &ms) {
    const auto id(ms.target().name().qualified().dot());
    tracing::scoped_transform_tracer stp(lg, "merge",
        transform_id, id, *ctx.tracer(), ms);

    const auto r(merge(ms.target(), ms.references()));
    stp.end_transform(r);
    return r;
}

}
