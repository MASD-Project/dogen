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
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/archetype_location_repository.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/yarn/types/mapping_set_repository.hpp"

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
        const options::knitting_options& options,
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const mapping_set_repository& msrp);

public:
    /**
     * @brief System directories containing Dogen's configuration,
     * profiles, etc.
     */
    const std::vector<boost::filesystem::path>& data_directories() const;

    /**
     * @brief User supplied parameters.
     */
    const options::knitting_options& options() const;

    /**
     * @brief Repository with annotation types, used to validate and
     * access meta-data.
     */
    const annotations::type_repository& type_repository() const;

    /**
     * @brief Factory to generate annotation groups.
     */
    const annotations::annotation_groups_factory& groups_factory() const;

    /**
     * @brief
     */
    const mapping_set_repository& mapping_repository() const;

private:
    const std::vector<boost::filesystem::path> data_directories_;
    const dogen::options::knitting_options options_;
    const annotations::archetype_location_repository location_repository_;
    const dogen::annotations::type_repository type_repository_;
    const annotations::annotation_groups_factory groups_factory_;
    const mapping_set_repository mapping_repository_;
};

} } }

#endif
