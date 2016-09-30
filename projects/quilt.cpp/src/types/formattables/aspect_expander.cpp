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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/io/annotations/aspect_annotations_io.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.aspect_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

aspect_expander::aspect_annotations_type
aspect_expander::obtain_aspect_annotations(const dynamic::repository& drp,
    const std::unordered_map<std::string, formattable>& formattables) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating aspect annotations.";

    annotations::aspect_annotations_factory f(drp);
    aspect_annotations_type r;
    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        const auto& segment(*formattable.master_segment());
        const auto aspect_annotation(f.make(segment.extensions()));
        if (aspect_annotation)
            r[id] = *aspect_annotation;
    }
    BOOST_LOG_SEV(lg, debug) << "Finished creating aspect annotations. Result: "
                             << r;
    return r;
}

void aspect_expander::walk_name_tree(const yarn::name_tree& nt,
    const bool is_top_level, const aspect_annotations_type& aa,
    aspect_configuration& ac) const {

    for (const auto& c : nt.children())
        walk_name_tree(c, false/*is_top_level*/, aa, ac);

    if (is_top_level && nt.is_current_simple_type())
        ac.requires_manual_default_constructor(true);

    const auto i(aa.find(nt.current().id()));
    if (i == aa.end())
        return;

    const auto as(i->second);
    if (as.requires_stream_manipulators())
        ac.requires_stream_manipulators(true);

    if (!is_top_level)
        return;

    if (as.requires_manual_default_constructor())
        ac.requires_manual_default_constructor(true);

    if (as.requires_manual_move_constructor())
        ac.requires_manual_move_constructor(true);
}

aspect_configuration
aspect_expander::compute_aspect_configuration(const aspect_annotations_type& aa,
    const std::list<yarn::attribute>& attr) const {

    aspect_configuration r;
    for (const auto a : attr) {
        const auto& nt(a.parsed_type());
        walk_name_tree(nt, true/*is_top_level*/, aa, r);
    }
    return r;
}

void aspect_expander::populate_aspect_configuration(
    const aspect_annotations_type& aa,
    std::unordered_map<std::string, formattable>& formattables) const {

    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& cfg(formattable.configuration());

        /*
         * We only want to process the master segment; the
         * extensions can be ignored.
         */
        auto segment(formattable.master_segment());

        /*
         * We are only interested in yarn objects; all other
         * element types do not need helpers.
         */
        const auto ptr(dynamic_cast<const yarn::object*>(segment.get()));
        if (ptr == nullptr)
            continue;

        /*
         * We only need to generate the aspect configuration for
         * elements of the target model. However, we can't perform
         * this after reduction because the aspectq annotations
         * must be build prior to reduction or else we will not
         * get aspects for referenced models.
         */
        if (ptr->generation_type() == yarn::generation_types::no_generation)
            continue;

        /*
         * Update the aspect configuration.
         */
        const auto& attr(ptr->local_attributes());
        const auto ac(compute_aspect_configuration(aa, attr));
        cfg.aspect_configuration(ac);
    }
}

void aspect_expander::
expand(const dynamic::repository& drp,
    std::unordered_map<std::string, formattable>& formattables) const {

    const auto aspect_annotations(obtain_aspect_annotations(drp, formattables));
    populate_aspect_configuration(aspect_annotations, formattables);
}

} } } }
