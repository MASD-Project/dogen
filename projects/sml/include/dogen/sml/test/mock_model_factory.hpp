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
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
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
     * @brief Types of objects supported by the factory.
     */
    enum class object_types {
        invalid = 0,
        value_object,
        service,
        repository,
        factory,
        entity,
        keyed_entity,
        enumeration,
        exception
    };

    /**
     * @brief Types of properties supported by the factory.
     */
    enum class property_types {
        invalid = 0,
        unsigned_int,
        boolean,
        entity,
        value_object,
        boost_variant,
        std_string,
        std_pair,
        boost_shared_ptr
    };

public:
    /**
     * @brief Configuration flags for the mock factory.
     */
    class flags {
    public:
        flags(const bool tagged = false,
            const bool merged = false,
            const bool resolved = false,
            const bool concepts_indexed = false,
            const bool properties_indexed = false,
            const bool associations_indexed = false);

    public:
        /**
         * @brief If true, add meta-data tags to the model.
         */
        /**@{*/
        bool tagged() const;
        void tagged(const bool v);
        /**@}*/

        /**
         * @brief For methods that return more than one model, if
         * true, merges all of them into a single merged model.
         */
        /**@{*/
        bool merged() const;
        void merged(const bool v);
        /**@}*/

        /**
         * @brief For methods that return more than one model, when
         * false, leaves properties unresolved for all models other
         * than the target model.
         */
        /**@{*/
        bool resolved() const;
        void resolved(const bool v);
        /**@}*/

        /**
         * @brief If true, returns a model as if concept indexing was
         * already performed.
         */
        /**@{*/
        bool concepts_indexed() const;
        void concepts_indexed(const bool v);
        /**@}*/

        /**
         * @brief If true, returns a model as if property indexing was
         * already performed.
         */
        /**@{*/
        bool properties_indexed() const;
        void properties_indexed(const bool v);
        /**@}*/

        /**
         * @brief If true, returns a model as if association indexing
         * was already performed.
         */
        /**@{*/
        bool associations_indexed() const;
        void associations_indexed(const bool v);
        /**@}*/

    private:
        bool tagged_;
        bool merged_;
        bool resolved_;
        bool concepts_indexed_;
        bool properties_indexed_;
        bool associations_indexed_;
    };

public:
    /**
     * @brief Initialises a new mock factory at a given stage in the
     * SML pipeline, as given by the flags supplied.
     */
    explicit mock_model_factory(const flags& f);

public:
    /**
     * @brief Returns the model name derived from n.
     */
    std::string model_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the type name derived from n.
     */
    std::string type_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the concept name derived from n.
     */
    std::string concept_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the module name derived from n.
     */
    std::string module_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the property name derived from n.
     */
    std::string property_name(const unsigned int n = 0) const;

public:
    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for model @e n.
     */
    /**@{*/
    bool is_model_n(const unsigned int n, const qname& qn) const;
    bool is_model_n(const unsigned int n, const std::string& s) const;
    /**@}*/

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for type @e n.
     */
    /**@{*/
    bool is_type_name_n(const unsigned int n, const qname& qn) const;
    bool is_type_name_n(const unsigned int n, const std::string& qn) const;
    /**@}*/

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for module @e n.
     */
    bool is_concept_name_n(const unsigned int n, const qname& qn) const;

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for module @e n.
     */
    bool is_module_n(const unsigned int n, const std::string& s) const;

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for type @e n, and the SML naming convention
     * for unversioned keys.
     */
    bool is_type_name_n_unversioned(const unsigned int n,
        const qname& qn) const;

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for type @e n, and the SML naming convention
     * for versioned keys.
     */
    bool is_type_name_n_versioned(const unsigned int n, const qname& qn) const;

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for type @e n, and the SML naming convention
     * for visitors.
     */
    bool is_type_name_n_visitor(const unsigned int n, const qname& qn) const;


    /**
     * @brief Returns true if the file name matches the expected
     * file name for the given qname.
     */
    bool is_file_for_qname(const boost::filesystem::path& p,
        const qname& qn) const;

private:
    /**
     * @brief Create a value object.
     */
    object build_value_object(const unsigned int i, const qname& model_qn,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create a value object with a model name based on @e i.
     */
    object build_value_object(unsigned int i,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create a concept.
     */
    concept build_concept(const unsigned int i, const qname& model_qname) const;

    /**
     * @brief Create an entity.
     */
    object build_entity(const property& prop, const bool keyed,
        const unsigned int i, const qname& model_qname,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create an enumeration.
     */
    enumeration build_enumeration(const unsigned int i,
        const qname& model_qname,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create an exception.
     */
    object build_exception(const unsigned int i, const qname& model_qname,
        const unsigned int module_n = 0) const;

public:
    /**
     * @brief Returns a qname derived from the input parameters
     */
    qname build_qname(const unsigned int model_n = 0,
        const unsigned int simple_n = 0) const;

    /**
     * @brief Builds a model with no types, concepts or modules.
     */
    model build_empty_model(const unsigned int n = 0) const;

    /**
     * @brief Builds a model with a name derived from n, containing a
     * single type with a name also deriving from n.
     */
    model build_single_type_model(const unsigned int n = 0,
        const object_types ot = object_types::value_object) const;

    /**
     * @brief Builds a model with a name derived from n, containing a
     * single type with a name also deriving from n, inside mod_n modules.
     */
    model build_single_type_model_in_module(const unsigned int n = 0,
        const object_types ot = object_types::value_object,
        const unsigned int mod_n = 0) const;

    /**
     * @brief Builds a model with a name derived from n, and a number
     * of types determined by type_n, inside mod_n module.
     */
    model build_multi_type_model(const unsigned int n,
        const unsigned int type_n,
        const object_types ot = object_types::value_object,
        const unsigned int mod_n = 0) const;

public:
    /**
     * @brief Builds a model with a concept, and a type that models
     * it.
     */
    model build_single_concept_model(const unsigned int n = 0) const;

    /**
     * @brief Builds a model with a concept that refines another
     * concept, and two types that model each concept.
     */
    model build_first_degree_concepts_model(const unsigned int n = 0) const;

    /**
     * @brief Same as first degree but with 2 levels of inheritance.
     */
    model build_second_degree_concepts_model(const unsigned int n = 0) const;

    /**
     * @brief Builds a model with two base concepts and a concept that
     * refines both.
     */
    model build_multiple_inheritance_concepts_model(
        const unsigned int n = 0) const;

    /**
     * @brief Builds a model with a base concept, two concepts that
     * refine it, and a concept that refines both of these. Finally a
     * type last concept.
     */
    model build_diamond_inheritance_concepts_model(
        const unsigned int n = 0) const;

    /**
     * @brief Builds a model with a child object with a parent that
     * models a concept.
     */
    model build_object_with_parent_that_models_concept(
        const unsigned int n = 0) const;

    /**
     * @brief Builds a model with a child object with a parent that
     * models a concept that refines a concept.
     */
    model build_object_with_parent_that_models_a_refined_concept(
        const unsigned int n = 0) const;

    /**
     * @brief Builds a model with a concept that refines a
     * non-existing concept.
     */
    model build_concept_that_refines_missing_concept(
        const unsigned int n = 0) const;

    /**
     * @brief Builds a model with a concept that refines a
     * non-existing concept.
     */
    model build_object_that_models_missing_concept(
        const unsigned int n = 0) const;

    /**
     * @brief object that models concept with missing parent.
     */
    model build_object_that_models_concept_with_missing_parent(
        const unsigned int n = 0) const;

public:
    /**
     * @brief Scenario: object that exercises both weak and regular
     * associations.
     */
    model object_with_both_regular_and_weak_associations() const;

    /**
     * @brief Scenario: object with single property of a type existent in
     * current model.
     */
    model object_with_property(
        const object_types ot = object_types::value_object,
        const property_types pt = property_types::value_object) const;

    /**
     * @brief Scenario: object with single property of a type existent in
     * a second model.
     */
    std::array<model, 2>
    object_with_property_type_in_different_model() const;

    /**
     * @brief Scenario: object with property of missing type.
     */
    model object_with_missing_property_type() const;

    /**
     * @brief Scenario: object with parent in current model.
     */
    model
    object_with_parent_in_the_same_model(const bool has_property = false) const;

    /**
     * @brief Scenario: object with missing parent in current model.
     */
    model object_with_missing_parent_in_the_same_model() const;

    /**
     * @brief Scenario: object with a parent in a second model.
     */
    std::array<model, 2>
    object_with_parent_in_different_models() const;

    /**
     * @brief Scenario: object with three children.
     */
    model object_with_three_children_in_same_model() const;

    /**
     * @brief Scenario: object with three levels deep in inheritance tree
     * in current model.
     */
    model object_with_third_degree_parent_in_same_model(
        const bool has_property = false) const;

    /**
     * @brief Scenario: object with three levels deep in inheritance tree
     * has missing parent.
     */
    model object_with_third_degree_parent_missing() const;

    /**
     * @brief Scenario: object three levels deep in inheritance tree,
     * with parents in different models.
     */
    std::array<model, 4>
    object_with_third_degree_parent_in_different_models() const;

    /**
     * @brief Scenario: object three levels deep in inheritance tree,
     * with parents in different models and a missing top-level
     * parent.
     */
    std::array<model, 4>
    object_with_missing_third_degree_parent_in_different_models() const;

public:
    /**
     * @brief Returns a model with a single object that contains one
     * or two instances of a group of properties of different types.
     *
     * @param repeat_group if true, adds two instances of the group,
     * otherwise just one.
     */
    model object_with_group_of_properties_of_different_types(
        const bool repeat_group = false) const;

    /**
     * @brief Returns a model with a single object that contains one
     * operation with a single parameter.
     */
    model object_with_operation_with_single_parameter() const;

    /**
     * @brief Returns a model with a single object that contains one
     * operation with a several parameters.
     */
    model object_with_operation_with_multiple_parameters() const;

    /**
     * @brief Returns a model with a single object that contains one
     * operation with a return type.
     */
    model object_with_operation_with_return_type() const;

private:
    const flags flags_;
};

} } }

#endif
