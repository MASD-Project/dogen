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
#include "dogen.assets/io/meta_model/technical_space_io.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.assets/types/transforms/merge_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.merge_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

/**
 * @brief Copies the associative container across.
 */
template<typename ElementAssociativeContainer>
void copy(const ElementAssociativeContainer& src,
    ElementAssociativeContainer& dst) {
    for (const auto& pair : src)
        dst.insert(pair);
}

}

namespace dogen::assets::transforms {

void
merge_transform::merge(const meta_model::model& src, meta_model::model& dst) {
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

    BOOST_LOG_SEV(lg, debug) << "Merging source model: '"
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
                             << " modeline_groups: "
                             << src.decoration_elements().modeline_groups().size()
                             << " modeline: " << src.decoration_elements().modelines().size()
                             << " generation markers: "
                             << src.decoration_elements().generation_markers().size()
                             << " licences: "
                             << src.decoration_elements().licences().size()
                             << " type registrars: "
                             << src.serialization_elements().type_registrars().size()
                             << " visual studio solutions: "
                             << src.visual_studio_elements().solutions().size()
                             << " visual studio projects: "
                             << src.visual_studio_elements().projects().size();

    copy(src.structural_elements().modules(), dst.structural_elements().modules());
    copy(src.structural_elements().object_templates(), dst.structural_elements().object_templates());
    copy(src.structural_elements().builtins(), dst.structural_elements().builtins());
    copy(src.structural_elements().enumerations(), dst.structural_elements().enumerations());
    copy(src.structural_elements().primitives(), dst.structural_elements().primitives());
    copy(src.structural_elements().objects(), dst.structural_elements().objects());
    copy(src.structural_elements().exceptions(), dst.structural_elements().exceptions());
    copy(src.structural_elements().visitors(), dst.structural_elements().visitors());
    copy(src.decoration_elements().modeline_groups(), dst.decoration_elements().modeline_groups());
    copy(src.decoration_elements().modelines(), dst.decoration_elements().modelines());
    copy(src.decoration_elements().generation_markers(), dst.decoration_elements().generation_markers());
    copy(src.decoration_elements().licences(), dst.decoration_elements().licences());
    copy(src.mapping_elements().fixed_mappables(), dst.mapping_elements().fixed_mappables());
    copy(src.mapping_elements().extensible_mappables(), dst.mapping_elements().extensible_mappables());
    copy(src.serialization_elements().type_registrars(), dst.serialization_elements().type_registrars());
    copy(src.visual_studio_elements().solutions(), dst.visual_studio_elements().solutions());
    copy(src.visual_studio_elements().projects(), dst.visual_studio_elements().projects());

    /*
     * Update the references of the merged model.
     */
    const auto p(std::make_pair(src.name(), src.origin_type()));
    dst.references().insert(p);
}

meta_model::model merge_transform::merge(const meta_model::model& target,
    const std::list<meta_model::model>& refs) {
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

meta_model::model merge_transform::apply(const context &ctx,
    const assets::meta_model::model_set &ms) {
    const auto id(ms.target().name().qualified().dot());
    tracing::scoped_transform_tracer stp(lg, "merge transform",
        transform_id, id, *ctx.tracer(), ms);

    const auto r(merge(ms.target(), ms.references()));
    stp.end_transform(r);
    return r;
}

}
