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
#ifndef DOGEN_SML_TEST_MOCK_MODEL_FACTORY_HPP
#define DOGEN_SML_TEST_MOCK_MODEL_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <array>
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {
namespace test {

/**
 * @brief Generates mock sml models.
 */
class mock_model_factory {
public:
    /**
     * @brief Returns the model name derived from n.
     */
    static std::string model_name(const unsigned int n = 0);

    /**
     * @brief Returns the pod name derived from n.
     */
    static std::string pod_name(const unsigned int n = 0);

public:
    /**
     * @brief Builds a model with a name derived from n, containing a
     * single pod with a name also deriving from n.
     */
    static model build_single_pod_model(const unsigned int n = 0);

    /**
     * @brief Builds a model with a name derived from n, and a number
     * of pods determined by pod_n.
     */
    static model build_multi_pod_model(const unsigned int n,
        const unsigned int pod_n);

public:
    enum class property_types : unsigned int {
        invalid = 0,
        unsigned_int,
        boolean,
        other_pod,
        boost_variant,
        std_string,
        std_pair,
        boost_shared_ptr
    };

public:
    /**
     * @brief Scenario: pod with single property of a type existent in
     * current model.
     */
    static model
    pod_with_property(const property_types pt = property_types::other_pod);

    /**
     * @brief Scenario: pod with single property of a type existent in
     * a second model.
     */
    static std::array<model, 2>
    pod_with_property_type_in_different_model();

    /**
     * @brief Scenario: pod with property of missing type.
     */
    static model pod_with_missing_property_type();

    /**
     * @brief Scenario: pod with parent in current model.
     */
    static model pod_with_parent_in_the_same_model();

    /**
     * @brief Scenario: pod with missing parent in current model.
     */
    static model pod_with_missing_child_in_the_same_model();

    /**
     * @brief Scenario: pod with a parent in a second model.
     */
    static std::array<model, 2>
    pod_with_parent_in_different_models();

    /**
     * @brief Scenario: pod with three children.
     */
    static model pod_with_three_children_in_same_model();

    /**
     * @brief Scenario: pod with three levels deep in inheritance tree
     * in current model.
     */
    static model pod_with_third_degree_parent_in_same_model();

    /**
     * @brief Scenario: pod with three levels deep in inheritance tree
     * has missing parent.
     */
    static model pod_with_third_degree_parent_missing();

    /**
     * @brief Scenario: pod three levels deep in inheritance tree,
     * with parents in different models.
     */
    static std::array<model, 4>
    pod_with_third_degree_parent_in_different_models();

    /**
     * @brief Scenario: pod three levels deep in inheritance tree,
     * with parents in different models and a missing top-level
     * parent.
     */
    static std::array<model, 4>
    pod_with_missing_third_degree_parent_in_different_models();
};

} } }

#endif
