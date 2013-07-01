/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_TYPES_MODELING_MERGER_HPP
#define DOGEN_SML_TYPES_MODELING_MERGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Combines a number of models into a single model.
 *
 * The role of the merger is to aggregate a number of models into a
 * single, coherent model called the @e merged model. There are two
 * types of models that contribute to the aggregation:
 *
 * @li the @e target model: the model which the user is focusing on, most
 * likely with the intention of code generating it. There can only be
 * one target model for a given merge.
 *
 * @lie the @e reference models; a model is a reference model if the
 * target model refers to one or more of its types, and thus is not
 * evaluatable without their definition. Merging will fail if one or
 * more of the referenced models have not been supplied.
 */
class merger {
private:
    typedef std::unordered_map<qname, model> models_type;

public:
    merger(const merger&) = default;
    ~merger() = default;
    merger(merger&&) = default;
    merger& operator=(const merger&) = default;

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
     * @brief Merge must not yet have taken place.
     */
    void require_not_has_merged() const;

private:
    /**
     * @brief Ensure the qualified name is consistent.
     *
     * @note should be moved to validator.
     */
    void check_qname(const std::string& model_name, const qname& key,
        const qname& value) const;

    /**
     * @brief Update all references to external models.
     */
    void update_references();

private:
    /**
     * @brief Merge supplied model.
     */
    void merge_model(const model& m);

    /**
     * @brief Merge all models.
     */
    void merge_models();

public:
    /**
     * @brief Returns true if the target model has already been added,
     * false otherwise.
     */
    bool has_target() const { return has_target_; }

    /**
     * @brief Returns true if the target model has already been added,
     * false otherwise.
     */
    bool has_merged() const { return has_merged_; }

    /**
     * @brief Adds the target model.
     *
     * @pre Must not already have a target model.
     * @pre Merge mustn't have taken place already.
     */
    void add_target(const model& target);

    /**
     * @brief Adds a reference model.
     *
     * @pre Merge mustn't have taken place already.
     */
    void add(const model& m);

    /**
     * @brief Combines all models into a merged model.
     *
     * @pre Merge mustn't have taken place already.
     */
    model merge();

private:
    models_type models_;
    model merged_model_;
    bool has_target_;
    bool has_merged_;
};

} }

#endif
