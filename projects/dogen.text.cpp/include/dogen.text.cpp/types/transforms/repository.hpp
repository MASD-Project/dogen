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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_REPOSITORY_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <string>
#include <forward_list>
#include <unordered_map>
#include "dogen.identification/types/entities/logical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/hash/entities/logical_meta_id_hash.hpp"
#include "dogen.identification/hash/entities/physical_meta_id_hash.hpp"
#include "dogen.text/types/transforms/helper_transform_fwd.hpp"
#include "dogen.text.cpp/types/transforms/model_to_text_transform_fwd.hpp"

namespace dogen::text::cpp::transforms {

class registrar;

/**
 * @brief Repository for all formatters.
 */
class repository final {
private:
    friend class registrar;

private:
    /**
     * @brief Returns all available file formatters by type indx.
     */
    std::unordered_map<
        identification::entities::logical_meta_id,
        std::forward_list<std::shared_ptr<model_to_text_transform>>
    >&
    stock_artefact_formatters_by_meta_name();

    /**
     * @brief Returns all available file formatters by archetype name.
     */
    std::unordered_map<identification::entities::physical_meta_id,
                       std::shared_ptr<model_to_text_transform>>&
    stock_artefact_formatters_by_archetype();

    /**
     * @brief Returns all available file formatters.
     */
    std::forward_list<std::shared_ptr<model_to_text_transform>>&
    stock_artefact_formatters();

    /**
     * @brief Returns all available helpers.
     */
    std::unordered_map<
        std::string,
        std::unordered_map<identification::entities::physical_meta_id,
                           std::list<
                               std::shared_ptr<
                                   text::transforms::helper_transform>>>>&
    helper_formatters();

public:
    /**
     * @brief Returns all available file formatters by type indx.
     */
    const std::unordered_map<
        identification::entities::logical_meta_id,
        std::forward_list<std::shared_ptr<model_to_text_transform>>>&
    stock_artefact_formatters_by_meta_name() const;

    /**
     * @brief Returns all available file formatters by formatter name.
     */
    const std::unordered_map<identification::entities::physical_meta_id,
                             std::shared_ptr<model_to_text_transform>>&
    stock_artefact_formatters_by_archetype() const;

    /**
     * @brief Returns all available file formatters.
     */
    const std::forward_list<std::shared_ptr<model_to_text_transform>>&
    stock_artefact_formatters() const;

    /**
     * @brief Returns all available helpers.
     */
    const std::unordered_map<
        std::string,
        std::unordered_map<identification::entities::physical_meta_id,
                       std::list<
                           std::shared_ptr<
                               text::transforms::helper_transform>>>>&
    helper_formatters() const;

private:
    std::unordered_map<
        identification::entities::logical_meta_id,
        std::forward_list<std::shared_ptr<model_to_text_transform>>>
    stock_artefact_formatters_by_meta_name_;
    std::unordered_map<identification::entities::physical_meta_id,
                       std::shared_ptr<model_to_text_transform>>
    stock_artefact_formatters_by_archetype_;
    std::forward_list<std::shared_ptr<model_to_text_transform>>
    stock_artefact_formatters_;
    std::unordered_map<
        std::string,
        std::unordered_map<identification::entities::physical_meta_id,
                           std::list<
                               std::shared_ptr<
                                   text::transforms::helper_transform>>>>
    helper_formatters_;
};

}

#endif
