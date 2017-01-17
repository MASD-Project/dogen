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
#ifndef DOGEN_YARN_TYPES_MERGER_HPP
#define DOGEN_YARN_TYPES_MERGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Combines a number of intermediate models into a single
 * intermediate model.
 *
 * The role of the merger is to aggregate a number of intermediate
 * models into a single, coherent model called the intermediate
 * @e merged model.
 *
 * There are two kinds of intermediate models:
 *
 * @li the intermediate @e target model: the model which the user is
 * focusing on, most likely with the intention of code generating
 * it. There can only be one target model for a given merge.
 *
 * @li the intermediate @e reference models; a model is a reference
 * model if the target model refers to one or more of its types - or a
 * model referred to by the target model refers to its types and so
 * on.
 *
 * In summary, the target model cannot be evaluated without the
 * definition of all models it references, directly or
 * indirectly. Merging will fail if one or more of the referenced
 * models have not been supplied.
 */
class merger {
public:
    merger();

private:
    /**
     * @brief Target model must have been set.
     */
    void require_has_target() const;

    /**
     * @brief Target model must @e not have been set.
     */
    void require_not_has_target(const std::string& name) const;

    /**
     * @brief Merge must @e not yet have taken place.
     */
    void require_not_has_merged() const;

    /**
     * @brief Copies the associative container across.
     */
    template<typename ElementAssociativeContainer>
    void copy(const ElementAssociativeContainer& src,
        ElementAssociativeContainer& dst) {
        for (const auto& pair : src)
            dst.insert(pair);
    }

private:
    /**
     * @brief Ensure there is consistency between model name, key and
     * value.
     */
    void check_name(const name& model_name, const std::string& key,
        const name& value, const bool in_global_namespace) const;

    /**
     * @brief Update all references to external models.
     */
    void update_references();

private:
    /**
     * @brief Merge supplied model.
     */
    void merge_model(const intermediate_model& m);

    /**
     * @brief Merge all models.
     */
    void merge_models();

    /**
     * @brief Adds the target model.
     *
     * @pre Must not already have a target model.
     * @pre Merge mustn't have taken place already.
     */
    void add_target(const intermediate_model& target);

public:
    /**
     * @brief Returns true if the target model has already been added,
     * false otherwise.
     */
    bool has_target() const { return has_target_; }

    /**
     * @brief Returns true if the merge has already taken place, false
     * otherwise.
     */
    bool has_merged() const { return has_merged_; }

    /**
     * @brief Adds a partial model.
     *
     * @pre Merge mustn't have taken place already.
     */
    void add(const intermediate_model& m);

    /**
     * @brief Combines all partial models into a merged model.
     *
     * @pre Merge mustn't have taken place already.
     */
    intermediate_model merge();

private:
    std::unordered_map<name, intermediate_model> models_;
    intermediate_model merged_model_;
    bool has_target_;
    bool has_merged_;
    languages target_language_;
};

} }

#endif
