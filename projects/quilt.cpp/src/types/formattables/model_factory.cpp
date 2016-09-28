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
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.model_factory"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::unordered_map<std::string, std::string> model_factory::
facet_directory_for_facet(const std::unordered_map<std::string,
    annotations::path_annotations>& pa, const formatters::container& fc) const {

    std::unordered_map<std::string, std::string> r;
    for (const auto& f : fc.file_formatters()) {
        const auto i(pa.find(f->ownership_hierarchy().formatter_name()));
        if ( i != pa.end()) {
            const auto fn(f->ownership_hierarchy().facet_name());
            r[fn] = i->second.facet_directory();
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Facet directory for facet: " << r;
    return r;
}

std::unordered_map<std::string, annotations::streaming_annotations>
model_factory::make_streaming_annotations(const dynamic::repository& drp,
    const std::list<formattable>& formattables) const {

    annotations::streaming_annotations_factory f(drp);
    std::unordered_map<std::string, annotations::streaming_annotations> r;
    for (const auto& formattable : formattables) {
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
            const auto ss(f.make(e.extensions()));
            if (!ss)
                continue;

            r[e.name().id()] = *ss;
        }
    }
    return r;
}

model model_factory::make(const dynamic::repository& drp,
    const std::unordered_map< std::string, annotations::path_annotations>& pa,
    const formatters::container& fc,
    const std::list<formattable>& formattables) const {

    model r;
    r.formattables(formattables);
    r.streaming_annotations(make_streaming_annotations(drp, formattables));
    r.facet_directory_for_facet(facet_directory_for_facet(pa, fc));

    return r;
}

} } } }
