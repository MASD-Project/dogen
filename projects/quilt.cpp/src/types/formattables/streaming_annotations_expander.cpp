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
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/streaming_annotations_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.streaming_annotations_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void streaming_annotations_expander::expand(const dynamic::repository& drp,
    std::unordered_map<std::string, formattable>& formattables) const {

    annotations::streaming_annotations_factory f(drp);
    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& cfg(formattable.configuration());
        for (const auto& segment : formattable.element_segments()) {
            /*
             * We only want to process the master segment; the
             * extensions can be ignored.
             */
            if (segment->is_element_extension())
                continue;

            /*
             * We are only interested in yarn objects; all other
             * element types do not need helpers.
             */
            const auto ptr(dynamic_cast<const yarn::object*>(segment.get()));
            if (ptr == nullptr)
                continue;

            const auto& e(*ptr);
            cfg.streaming_annotations(f.make(e.extensions()));
        }
    }
}

} } } }
