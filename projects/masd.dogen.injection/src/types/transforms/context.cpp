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
#include "masd.dogen.injection/types/transforms/context.hpp"

namespace masd::dogen::injection::transforms {

context::context(
    const std::vector<boost::filesystem::path>& data_directories,
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const tracing::tracer& tracer,
    const bool compatibility_mode) :
    data_directories_(data_directories),
    archetype_location_repository_(alrp), type_repository_(atrp),
    annotation_factory_(data_directories, archetype_location_repository_,
        type_repository_, compatibility_mode), tracer_(tracer) {}

const std::vector<boost::filesystem::path>& context::data_directories() const {
    return data_directories_;
}

const annotations::archetype_location_repository&
context::archetype_location_repository() const {
    return archetype_location_repository_;
}

const annotations::type_repository& context::type_repository() const {
    return type_repository_;
}

const annotations::annotation_factory& context::annotation_factory() const {
    return annotation_factory_;
}

const masd::dogen::tracing::tracer& context::tracer() const {
    return tracer_;
}

}
