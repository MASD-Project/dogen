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
#include "dogen.text.cpp/types/transforms/context.hpp"

namespace dogen::text::cpp::transforms {

context::context(const formattables::element_properties& element_properties,
    const physical::entities::model& pm, const formattables::model& fm,
    const std::unordered_map<std::string,
    std::unordered_map<identification::entities::physical_meta_id,
    std::list<std::shared_ptr<helper_transform>>>>& helpers,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::streaming_properties>& streaming_properties,
    boost::shared_ptr<tracing::tracer> tracer)
    : element_properties_(element_properties), physical_model_(pm),
      model_(fm), helpers_(helpers),
      streaming_properties_(streaming_properties), tracer_(tracer) { }

const formattables::element_properties&
context::element_properties() const {
    return element_properties_;
}

const formattables::model& context::model() const {
    return model_;
}

const std::unordered_map<std::string,
    std::unordered_map<identification::entities::physical_meta_id,
                       std::list<std::shared_ptr<helper_transform>>>>&
context::helpers() const {
    return helpers_;
}

const physical::entities::model& context::physical_model() const {
    return physical_model_;
}

const std::unordered_map<identification::entities::logical_id,
                         logical::entities::streaming_properties>&
context::streaming_properties() const {
    return streaming_properties_;
}

boost::shared_ptr<tracing::tracer> context::tracer() const {
    return tracer_;
}

}
