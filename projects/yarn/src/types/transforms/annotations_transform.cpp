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
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/scope_types_io.hpp"
#include "dogen/annotations/io/scribble_group_io.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/annotations_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.annotations_transform"));

}

namespace dogen {
namespace yarn {
namespace transforms {

annotations::annotation_group
annotations_transform::obtain_annotation_group(const context& ctx,
    annotations::scribble_group sg, const meta_model::element& e) {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

    if (!e.stereotypes().empty()) {
        /*
         * Note that we are ignoring children here on purpose;
         * candidate labels are not used by children at present.
         */
        sg.parent().candidate_labels(e.stereotypes());
    }

    return ctx.groups_factory().make(sg);
}

void annotations_transform::process_attributes(
    const annotations::annotation_group& ag,
    std::list<meta_model::attribute>& attrs) {

    for (auto& attr : attrs) {
        /*
         * Note that we use the simple name because the frontends are
         * expected to insert by simple name, since the insertion
         * preceeds the naming transform.
         */
        const auto sn(attr.name().simple());
        const auto j(ag.children().find(sn));
        if (j == ag.children().end()) {
            BOOST_LOG_SEV(lg, debug) << "Attribute has no annotation: " << sn;
            continue;
        }

        attr.annotation(j->second);
        BOOST_LOG_SEV(lg, debug) << "Created annotations for attribute: " << sn;
    }
}

void annotations_transform::process(const annotations::annotation_group& ag,
    meta_model::element& e) {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;
    e.annotation(ag.parent());
}

void annotations_transform::process(const annotations::annotation_group& ag,
    meta_model::object_template& ot) {
    const auto id(ot.name().id());
    BOOST_LOG_SEV(lg, debug) << "Processing object template: " << id;
    ot.annotation(ag.parent());
    process_attributes(ag, ot.local_attributes());
}

void annotations_transform::process(const annotations::annotation_group& ag,
    meta_model::object& o) {
    const auto id(o.name().id());
    BOOST_LOG_SEV(lg, debug) << "Processing object: " << id;
    o.annotation(ag.parent());
    process_attributes(ag, o.local_attributes());
}

void annotations_transform::process(const annotations::annotation_group& ag,
    meta_model::enumeration& e) {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

    e.annotation(ag.parent());
    for (auto& en : e.enumerators()) {
        const auto sn(en.name().simple());
        const auto i(ag.children().find(sn));
        if (i == ag.children().end()) {
            BOOST_LOG_SEV(lg, debug) << "Enumerator has no annotation: " << sn
                                     << ". Element: " << e.name().id();
            continue;
        }

        en.annotation(i->second);
        BOOST_LOG_SEV(lg, debug) << "Created annotations for attribute: " << sn;
    }
}

void annotations_transform::
transform(const context& ctx, meta_model::exomodel& em) {
    process(ctx, em.modules());
    process(ctx, em.object_templates());
    process(ctx, em.builtins());
    process(ctx, em.enumerations());
    process(ctx, em.primitives());
    process(ctx, em.objects());
    process(ctx, em.exceptions());
    process(ctx, em.root_module());
}

} } }
