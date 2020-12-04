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

context::context(const text::entities::model& m,
    const identification::entities::technical_space_version tsv,
    boost::shared_ptr<tracing::tracer> tracer)
    : model_(m), technical_space_version_(tsv),
      tracer_(tracer) { }

const text::entities::model& context::model() const {
    return model_;
}

identification::entities::technical_space_version context::
technical_space_version() const {
    return technical_space_version_;
}

boost::shared_ptr<tracing::tracer> context::tracer() const {
    return tracer_;
}

}
