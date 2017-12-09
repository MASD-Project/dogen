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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation_factory.hpp"
#include "dogen/annotations/types/archetype_location_repository.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/probing/types/prober.hpp"
#include "dogen/yarn/types/meta_model/intra_backend_segment_properties.hpp"
#include "dogen/yarn/types/transforms/options.hpp"
#include "dogen/yarn/types/helpers/transform_prober.hpp"
#include "dogen/yarn/types/helpers/mapping_set_repository.hpp"
#include "dogen/yarn/types/helpers/artefact_writer_interface.hpp"


namespace dogen {
namespace yarn {
namespace transforms {

/**
 * @brief Context for all transformations.
 *
 * Contains all of the external data required for the transformations
 * to execute. It's not ideal to have a huge "global" class, with lots
 * of unrelated state; however, over time, we found that a number of
 * arguments were being supplied across the call graph, resulting in a
 * lot of repetitive code. The context gathers together all of these.
 *
 * Note that this class needs to be handcrafted because we have some
 * factories in the state - not just data objects.
 */
class context final {
public:
    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const options& options,
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const helpers::mapping_set_repository& msrp,
        const dogen::formatters::repository& frp,
        const helpers::transform_prober& prober,
        const probing::prober& new_prober,
        const std::unordered_map<std::string,
        meta_model::intra_backend_segment_properties>&
        intra_backend_segment_properties,
        const boost::shared_ptr<helpers::artefact_writer_interface> writer);
    ~context();

public:
    /**
     * @brief System directories containing Dogen's configuration,
     * profiles, etc.
     */
    const std::vector<boost::filesystem::path>& data_directories() const;

    /**
     * @brief User supplied parameters.
     *
     * @note Added prefix "transform_" to keep gcc happy.
     */
    const options& transform_options() const;

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
     * @brief Data to perform language mapping.
     */
    const helpers::mapping_set_repository& mapping_repository() const;

    /**
     * @brief Repository with formatter data.
     */
    const dogen::formatters::repository& formatters_repository() const;

    /*
     * @brief Returns the transform probe.
     */
    const helpers::transform_prober& prober() const;

    /*
     * @brief Returns the transform probe.
     */
    const probing::prober& new_prober() const;

    /**
     * @brief Returns all intra-backend segment properties.
     */
    const std::unordered_map<std::string,
                             meta_model::intra_backend_segment_properties>&
    intra_backend_segment_properties() const;

    /**
     * @brief Writer for artefacts.
     */
    const helpers::artefact_writer_interface& artefact_writer() const;

private:
    const std::vector<boost::filesystem::path> data_directories_;
    const transforms::options options_;
    const annotations::archetype_location_repository
    archetype_location_repository_;
    const annotations::type_repository type_repository_;
        const annotations::annotation_factory annotation_factory_;
    const helpers::mapping_set_repository mapping_repository_;
    const dogen::formatters::repository formatters_repository_;
    const helpers::transform_prober prober_;
    const probing::prober new_prober_;
    const std::unordered_map<std::string,
                             meta_model::intra_backend_segment_properties>
    intra_backend_segment_properties_;
    const boost::shared_ptr<helpers::artefact_writer_interface> writer_;
};

} } }

#endif
