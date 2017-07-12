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
#ifndef DOGEN_QUILT_TYPES_WORKFLOW_HPP
#define DOGEN_QUILT_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <forward_list>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/yarn/types/meta_model/model.hpp"
#include "dogen/quilt/types/kernel_output.hpp"
#include "dogen/quilt/types/kernel_registrar.hpp"
#include "dogen/quilt/types/kernel_interface.hpp"

namespace dogen {
namespace quilt {

/**
 * @brief Manages the entire kernel workflow.
 */
class workflow {
public:
    workflow(const options::knitting_options& o,
        const annotations::type_repository& atrp,
        const annotations::annotation_groups_factory& agf);

private:
    std::list<annotations::archetype_location>
    kernel_archetype_locations() const;

private:
    std::vector<boost::filesystem::path> obtain_data_directories() const;

    /**
     * @brief Creates the formatters' repository with decoration data.
     */
    dogen::formatters::repository create_formatters_decoration_repository(const
        std::vector<boost::filesystem::path>& data_directories) const;

    /**
     * @brief Create the decoration configuration factory.
     */
    dogen::formatters::decoration_properties_factory
    create_decoration_properties_factory(
        const annotations::type_repository& atrp,
        const dogen::formatters::repository& frp,
        const annotations::annotation& ra) const;

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static kernel_registrar& registrar();

    /**
     * @brief Returns all of the available archetype locations across
     * all kernels.
     */
    static std::list<annotations::archetype_location>
    archetype_locations();

public:
    /**
     * @brief Generates files for the supplied model using all
     * registered kernels.
     */
    boost::optional<kernel_output>
    execute(const yarn::meta_model::model& m) const;

private:
    static std::shared_ptr<kernel_registrar> registrar_;
    const options::knitting_options knitting_options_;
    const annotations::type_repository& repository_;
    const annotations::annotation_groups_factory& annotation_factory_;
};

} }

#endif
