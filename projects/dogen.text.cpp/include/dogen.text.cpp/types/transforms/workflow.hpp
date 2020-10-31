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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_WORKFLOW_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.variability/types/helpers/configuration_factory.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.text.cpp/types/formattables/model.hpp"
#include "dogen.text.cpp/types/transforms/registrar.hpp"

namespace dogen::text::cpp::transforms {

/**
 * @brief Generates all files for the supplied entity.
 */
class workflow final {
public:
    workflow(const physical::entities::model& pm,
        const variability::entities::feature_model& fm,
        const variability::helpers::configuration_factory& cf);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::transforms::registrar& registrar();

private:
    boost::shared_ptr<physical::entities::artefact>
    get_artefact(const std::unordered_map<
        identification::entities::physical_meta_id,
        boost::shared_ptr<physical::entities::artefact>>& artefacts,
        const identification::entities::physical_meta_id& archetype) const;

private:
    void execute(boost::shared_ptr<tracing::tracer> tracer,
        const formattables::model& fm, formattables::formattable& fbl) const;

public:
    void execute(boost::shared_ptr<tracing::tracer> tracer,
        formattables::model& fm) const;

private:
    static std::shared_ptr<cpp::transforms::registrar> registrar_;
    const physical::entities::model& physical_model_;
    const variability::entities::feature_model& feature_model_;
    const variability::helpers::configuration_factory& configuration_factory_;
};

}

#endif
