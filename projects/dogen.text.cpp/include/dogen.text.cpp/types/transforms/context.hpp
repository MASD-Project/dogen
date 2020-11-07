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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.identification/types/entities/technical_space_version.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.logical/types/entities/streaming_properties.hpp"
#include "dogen.text.cpp/types/formattables/model.hpp"
#include "dogen.text.cpp/types/transforms/helper_transform.hpp"

namespace dogen::text::cpp::transforms {

/**
 * @brief Supplies additional information required for formatting.
 */
class context final {
public:
    context(const physical::entities::model& pm,
        const formattables::model& fm,
        const std::unordered_map<std::string,
        std::unordered_map<identification::entities::physical_meta_id,
        std::list<std::shared_ptr<
        helper_transform>>>>& helpers,
        const std::unordered_map<identification::entities::logical_id,
        logical::entities::streaming_properties>& streaming_properties,
        const identification::entities::technical_space_version tsv,
        boost::shared_ptr<tracing::tracer> tracer);

public:
    const formattables::model& model() const;

    const std::unordered_map<std::string,
        std::unordered_map<identification::entities::physical_meta_id,
            std::list<std::shared_ptr<helper_transform>>>>&
    helpers() const;

    const physical::entities::model& physical_model() const;

    const std::unordered_map<identification::entities::logical_id,
                             logical::entities::streaming_properties>&
    streaming_properties() const;

    identification::entities::technical_space_version
    technical_space_version() const;

    boost::shared_ptr<tracing::tracer> tracer() const;

private:
    const physical::entities::model& physical_model_;
    const formattables::model& model_;
    const std::unordered_map<std::string,
        std::unordered_map<identification::entities::physical_meta_id,
                           std::list<std::shared_ptr<helper_transform>>>>&
    helpers_;
    const std::unordered_map<identification::entities::logical_id,
                             logical::entities::streaming_properties>&
    streaming_properties_;
    const identification::entities::technical_space_version
    technical_space_version_;
    boost::shared_ptr<tracing::tracer> tracer_;
};

}

#endif
