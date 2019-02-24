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
#ifndef MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_CONTEXT_HPP
#define MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.annotations/types/annotation_factory.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository.hpp"
#include "masd.dogen.extraction/types/repository.hpp"
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.generation/types/meta_model/intra_backend_segment_properties.hpp"

namespace masd::dogen::generation::transforms {

/**
 * @brief Context for transformations.
 */
class context final {
    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const masd::dogen::extraction::repository& frp,
        const tracing::tracer& tracer,
        const std::unordered_map<std::string,
        meta_model::intra_backend_segment_properties>&
        intra_backend_segment_properties);
    ~context();

public:
    /**
     * @brief All of the available archetype locations.
     */
    const annotations::archetype_location_repository&
    archetype_location_repository() const;

    /**
     * @brief Repository with annotation types, used to validate and
     * access meta-data.
     */
    const annotations::type_repository& type_repository() const;

    /**
     * @brief Factory to generate annotations.
     */
    const annotations::annotation_factory& annotation_factory() const;

    /**
     * @brief Repository with formatter data.
     */
    const masd::dogen::extraction::repository& formatting_repository() const;

    /*
     * @brief Returns the transform probe.
     */
    const tracing::tracer& tracer() const;

    /**
     * @brief Returns all intra-backend segment properties.
     */
    const std::unordered_map<std::string,
                             meta_model::intra_backend_segment_properties>&
    intra_backend_segment_properties() const;

private:
    const annotations::archetype_location_repository
    archetype_location_repository_;
    const annotations::type_repository type_repository_;
        const annotations::annotation_factory annotation_factory_;
    const masd::dogen::extraction::repository formatting_repository_;
    const tracing::tracer tracer_;
    const std::unordered_map<std::string,
                             meta_model::intra_backend_segment_properties>
    intra_backend_segment_properties_;
};

}

#endif
