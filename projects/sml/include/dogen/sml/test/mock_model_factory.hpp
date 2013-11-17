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
     * @brief Initialises a new mock factory at a given stage in the
     * SML pipeline, as given by the flags supplied.
     */
    mock_model_factory(const bool tagged = true, const bool indexed = true);

public:
    /**
     * @brief Returns the model name derived from n.
     */
    std::string model_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the type name derived from n.
     */
    std::string simple_name(const unsigned int n = 0) const;

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
    bool is_model_n(const unsigned int n, const dogen::sml::qname& qn) const;
    bool is_model_n(const unsigned int n, const std::string& s) const;
    /**@}*/

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for type @e n.
     */
    /**@{*/
    bool is_type_n(const unsigned int n, const dogen::sml::qname& qn) const;
    bool is_type_n(const unsigned int n, const std::string& qn) const;
    /**@}*/

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
    bool is_type_n_unversioned(const unsigned int n,
        const dogen::sml::qname& qn) const;

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for type @e n, and the SML naming convention
     * for versioned keys.
     */
    bool is_type_n_versioned(const unsigned int n,
        const dogen::sml::qname& qn) const;

    /**
     * @brief Returns true if the qname matches the mock model factory
     * naming convention for type @e n, and the SML naming convention
     * for visitors.
     */
    bool is_type_n_visitor(const unsigned int n,
        const dogen::sml::qname& qn) const;


    /**
     * @brief Returns true if the file name matches the expected
     * file name for the given qname.
     */
    bool is_file_for_qname(const boost::filesystem::path& p,
        const dogen::sml::qname& qn) const;

private:
    /**
     * @brief Create a value object.
     */
    boost::shared_ptr<dogen::sml::abstract_object>
    build_value_object(const unsigned int i, const dogen::sml::qname& model_qn,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create a value object with a model name based on @e i.
     */
    boost::shared_ptr<dogen::sml::abstract_object>
    build_value_object(unsigned int i, const unsigned int module_n = 0) const;

    /**
     * @brief Create a concept.
     */
    dogen::sml::concept
    build_concept(const unsigned int i, const dogen::sml::qname& model_qname)
        const;

    /**
     * @brief Create an entity.
     */
    boost::shared_ptr<dogen::sml::abstract_object>
    build_entity(const dogen::sml::property& prop, const bool keyed,
        const unsigned int i, const dogen::sml::qname& model_qname,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create an enumeration.
     */
    dogen::sml::enumeration build_enumeration(const unsigned int i,
        const dogen::sml::qname& model_qname,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create an exception.
     */
    boost::shared_ptr<dogen::sml::abstract_object>
    build_exception(const unsigned int i, const dogen::sml::qname& model_qname,
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
     * refines both const;
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

public:
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
    model object_with_missing_child_in_the_same_model() const;

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

private:
    const bool tagged_;
    const bool indexed_;
};

} } }

#endif
