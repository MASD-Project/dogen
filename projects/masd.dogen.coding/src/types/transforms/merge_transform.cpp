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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/technical_space_io.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/transforms/merge_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.merge_transform");

using namespace masd::dogen::utility::log;
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

namespace masd::dogen::coding::transforms {

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
                             << " modules: " << src.modules().size()
                             << " object templates: "
                             << src.object_templates().size()
                             << " builtins: " << src.builtins().size()
                             << " enumerations: " << src.enumerations().size()
                             << " primitives: " << src.primitives().size()
                             << " objects: " << src.objects().size()
                             << " exceptions: " << src.exceptions().size()
                             << " visitors: " << src.visitors().size()
                             << " modeline_groups: "
                             << src.modeline_groups().size()
                             << " modeline: " << src.modelines().size()
                             << " generation markers: "
                             << src.generation_markers().size()
                             << " licences: " << src.licences().size();

    copy(src.modules(), dst.modules());
    copy(src.object_templates(), dst.object_templates());
    copy(src.builtins(), dst.builtins());
    copy(src.enumerations(), dst.enumerations());
    copy(src.primitives(), dst.primitives());
    copy(src.objects(), dst.objects());
    copy(src.exceptions(), dst.exceptions());
    copy(src.visitors(), dst.visitors());
    copy(src.modeline_groups(), dst.modeline_groups());
    copy(src.modelines(), dst.modelines());
    copy(src.generation_markers(), dst.generation_markers());
    copy(src.licences(), dst.licences());

    /*
     * Update the references of the merged model.
     */
    const auto p(std::make_pair(src.name(), src.origin_type()));
    dst.references().insert(p);
}

meta_model::model merge_transform::apply(const context& ctx,
    const meta_model::model& target,
    const std::list<meta_model::model>& refs) {
    tracing::scoped_transform_tracer stp(lg, "merge transform",
        transform_id, target.name().qualified().dot(), *ctx.tracer());

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

    stp.end_transform(r);
    return r;
}

}
