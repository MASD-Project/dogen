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
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.logical/io/helpers/indices_io.hpp"
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/types/meta_model/structural/builtin.hpp"
#include "dogen.logical/types/helpers/indexer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("assets.helpers.indexer"));

}

namespace dogen::logical::helpers {

indices indexer::index(meta_model::model& m) {
    indices r;

    for (const auto& pair : m.structural_elements().builtins()) {
        const auto id(pair.first);
        r.elements_referable_by_attributes().insert(id);

        const auto& b(*pair.second);
        if (b.can_be_enumeration_underlier())
            r.enumeration_underliers().insert(id);

        if (b.can_be_primitive_underlier())
            r.primitive_underliers().insert(id);
    }

    for (const auto& pair : m.structural_elements().primitives()) {
        const auto id(pair.first);
        r.elements_referable_by_attributes().insert(id);
    }

    for (const auto& pair : m.structural_elements().enumerations())
        r.elements_referable_by_attributes().insert(pair.first);

    for (const auto& pair : m.structural_elements().objects()) {
        const auto id(pair.first);
        r.elements_referable_by_attributes().insert(id);

        const auto& o(*pair.second);
        if (o.type_parameters().always_in_heap())
            r.objects_always_in_heap().insert(id);

        if (o.is_abstract())
            r.abstract_elements().insert(id);

        if (o.can_be_primitive_underlier())
            r.primitive_underliers().insert(id);
    }

    BOOST_LOG_SEV(lg, debug) << "Indices: " << r;
    return r;
}

}
