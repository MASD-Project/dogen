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
#ifndef DOGEN_LOGICAL_TEST_MOCK_ENDOMODEL_FACTORY_HPP
#define DOGEN_LOGICAL_TEST_MOCK_ENDOMODEL_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <array>
#include <functional>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.logical/types/entities/model.hpp"

namespace dogen::logical::test {

/**
 * @brief Generates mock intermediate models.
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
        enumeration,
        exception
    };

    /**
     * @brief Types of attributes supported by the factory.
     */
    enum class attribute_types {
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
        explicit flags(const bool tagged = false,
            const bool merged = false,
            const bool resolved = false,
            const bool object_templates_indexed = false,
            const bool attributes_indexed = false,
            const bool associations_indexed = false,
            const bool types_parsed = false);

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
         * false, leaves attributes unresolved for all models other
         * than the target model.
         */
        /**@{*/
        bool resolved() const;
        void resolved(const bool v);
        /**@}*/

        /**
         * @brief If true, returns a model as if object templates
         * indexing was already performed.
         */
        /**@{*/
        bool object_templates_indexed() const;
        void object_templates_indexed(const bool v);
        /**@}*/

        /**
         * @brief If true, returns a model as if attribute indexing was
         * already performed.
         */
        /**@{*/
        bool attributes_indexed() const;
        void attributes_indexed(const bool v);
        /**@}*/

        /**
         * @brief If true, returns a model as if association indexing
         * was already performed.
         */
        /**@{*/
        bool associations_indexed() const;
        void associations_indexed(const bool v);
        /**@}*/

        /**
         * @brief If true, creates the name trees for attributes.
         */
        /**@{*/
        bool types_parsed() const;
        void types_parsed(const bool v);
        /**@}*/

    private:
        bool tagged_;
        bool merged_;
        bool resolved_;
        bool object_templates_indexed_;
        bool attributes_indexed_;
        bool associations_indexed_;
        bool types_parsed_;
    };

public:
    /**
     * @brief Initialises a new mock factory at a given stage in the
     * logical pipeline, as given by the flags supplied.
     */
    explicit mock_model_factory(const flags& f);

public:
    /**
     * @brief Returns the model name derived from n.
     */
    std::string simple_model_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the type name derived from n.
     */
    std::string simple_type_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the object template name derived from n.
     */
    std::string simple_object_template_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the module name derived from n.
     */
    std::string simple_module_name(const unsigned int n = 0) const;

    /**
     * @brief Returns the attribute name derived from n.
     */
    std::string simple_attribute_name(const unsigned int n = 0) const;

public:
    /**
     * @brief Returns the model name derived from n.
     */
    entities::name model_name(const unsigned int n = 0) const;

public:
    /**
     * @brief Returns true if the name matches the mock model factory
     * naming convention for model @e n.
     */
    /**@{*/
    bool is_model_n(const unsigned int n, const entities::name& name) const;
    bool is_model_n(const unsigned int n, const std::string& name) const;
    /**@}*/

    /**
     * @brief Returns true if the name matches the mock model factory
     * naming convention for type @e n.
     */
    /**@{*/
    bool is_type_name_n(const unsigned int n,
        const entities::name& name) const;
    bool is_type_name_n(const unsigned int n, const std::string& name) const;
    /**@}*/

    /**
     * @brief Returns true if the name matches the mock model factory
     * naming convention for module @e n.
     */
    bool is_object_template_name_n(const unsigned int n,
        const entities::name& name) const;

    /**
     * @brief Returns true if the name matches the mock model factory
     * naming convention for module @e n.
     */
    bool is_module_n(const unsigned int n, const std::string& name) const;

    /**
     * @brief Returns true if the name matches the mock model factory
     * naming convention for type @e n, and the logical naming convention
     * for visitors.
     */
    bool is_type_name_n_visitor(const unsigned int n,
        const entities::name& name) const;

    /**
     * @brief If required, adds a module for the model.
     */
    void handle_model_module(const bool add_model_module,
        entities::model& m) const;

public:
    /**
     * @brief Creates a built-in.
     */
    entities::structural::builtin make_builtin(const unsigned int i,
        const entities::name& model_name,
        const identification::entities::model_type mt,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create a value object.
     */
    boost::shared_ptr<entities::structural::object>
    make_object(const unsigned int i, const entities::name& model_name,
        const identification::entities::model_type mt,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create a value object with an attribute
     */
    boost::shared_ptr<entities::structural::object>
    make_object_with_attribute(const unsigned int i,
        const entities::name& model_name,
        const identification::entities::model_type mt,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create a value object with a model name based on @e i.
     */
    boost::shared_ptr<entities::structural::object> make_object(unsigned int i,
        const identification::entities::model_type mt,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create an object template.
     */
    boost::shared_ptr<entities::structural::object_template>
    make_object_template(const unsigned int i,
        const entities::name& model_name,
        const identification::entities::model_type nt) const;

    /**
     * @brief Create an enumeration.
     */
    boost::shared_ptr<entities::structural::enumeration>
    make_enumeration(const unsigned int i, const entities::name& model_name,
        const identification::entities::model_type mt,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create an exception.
     */
    boost::shared_ptr<entities::structural::exception>
    make_exception(const unsigned int i, const entities::name& model_name,
        const identification::entities::model_type mt,
        const unsigned int module_n = 0) const;

    /**
     * @brief Create a module from a name.
     */
    boost::shared_ptr<entities::structural::module> make_module(
        const entities::name& n, const identification::entities::model_type mt,
        const std::string& documentation = std::string()) const;

    /**
     * @brief Create a module from its components.
     */
    boost::shared_ptr<entities::structural::module>
    make_module(const unsigned int module_n, const entities::name& model_name,
        const identification::entities::model_type mt,
        const std::list<std::string>& internal_modules,
        const std::string& documentation) const;

public:
    /**
     * @brief Returns a name derived from the input parameters
     */
    entities::name make_name(const unsigned int model_n = 0,
        const unsigned int simple_n = 0) const;

    /**
     * @brief Builds a model with no elements.
     */
    entities::model make_empty_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0, const bool add_model_module = false) const;

    /**
     * @brief Builds a model with a name derived from n, containing a
     * single type with a name also deriving from n.
     */
    entities::model make_single_type_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const object_types objt = object_types::value_object,
        const bool add_model_module = false) const;

    /**
     * @brief Builds a model with a name derived from n, containing a
     * single type with a name also deriving from n, inside mod_n modules.
     */
    entities::model make_single_type_model_in_module(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const object_types objt = object_types::value_object,
        const unsigned int mod_n = 0,
        const bool add_model_module = false) const;

    /**
     * @brief Builds a model with a name derived from n, and a number
     * of types determined by type_n, inside mod_n module.
     */
    entities::model make_multi_type_model(
        const unsigned int n,
        const unsigned int type_n,
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const object_types objt = object_types::value_object,
        const unsigned int mod_n = 0,
        const bool add_model_module = false) const;

public:
    /**
     * @brief Builds a model with an object template, and an object
     * that instantiates it.
     */
    entities::model make_single_object_template_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const bool add_model_module = false) const;

    /**
     * @brief Builds a model with an object template that inherits
     * another object template, and two types that instantiate each
     * object template.
     */
    entities::model make_first_degree_object_templates_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0, const bool add_model_module = false) const;

    /**
     * @brief Same as first degree but with 2 levels of inheritance.
     */
    entities::model make_second_degree_object_templates_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0, const bool add_model_module = false) const;

    /**
     * @brief Builds a model with two base object templates and an
     * object template that inherits from both.
     */
    entities::model make_multiple_inheritance_object_templates_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const bool add_model_module = false) const;

    /**
     * @brief Builds a model with a base object template, two object
     * templates that inherit from it, and an object template that
     * refines both of these. Finally, an object that instantiates the
     * last object template.
     */
    entities::model make_diamond_inheritance_object_templates_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const bool add_model_module = false) const;

    /**
     * @brief Builds a model with a child object with a parent that
     * instantiates an object template.
     */
    entities::model
    make_object_with_parent_that_instantiates_object_template(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const bool add_model_module = false) const;

    /**
     * @brief Builds a model with a child object with a parent that
     * instantiates an object template, which inherits from another
     * object template.
     */
    entities::model
    make_object_with_parent_that_instantiates_a_child_object_template(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const bool add_model_module = false) const;

    /**
     * @brief Builds a model with an object template that inherits
     * from a non-existing object template.
     */
    entities::model
    make_object_template_that_inherits_missing_object_template(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const bool add_model_module = false) const;

    /**
     * @brief Builds a model with an object that instantiates a
     * non-existing object template.
     */
    entities::model make_object_that_instantiates_missing_object_template(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const bool add_model_module = false) const;

    /**
     * @brief Object that instantiates object template with missing
     * parent.
     */
    entities::model
    make_object_that_instantiates_object_template_with_missing_parent(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const unsigned int n = 0,
        const bool add_model_module = false) const;

public:
    /**
     * @brief Scenario: object that exercises both weak and regular
     * associations.
     */
    entities::model
    object_with_both_transparent_and_opaque_associations(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with single attribute of a type existent in
     * current model.
     */
    entities::model object_with_attribute(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const object_types objt = object_types::value_object,
        const attribute_types pt = attribute_types::value_object,
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with single attribute of a type existent in
     * a second model.
     */
    std::array<entities::model, 2>
    object_with_attribute_type_in_different_model(
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with attribute of missing type.
     */
    entities::model object_with_missing_attribute_type(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with parent in current model.
     */
    entities::model object_with_parent_in_the_same_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const bool has_attribute = false,
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with missing parent in current model.
     */
    entities::model object_with_missing_parent_in_the_same_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with a parent in a second model.
     */
    std::array<entities::model, 2>
    object_with_parent_in_different_models(
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with three children.
     */
    entities::model object_with_three_children_in_same_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with three levels deep in inheritance tree
     * in current model.
     */
    entities::model
    object_with_third_degree_parent_in_same_model(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const bool has_attribute = false,
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object with three levels deep in inheritance tree
     * has missing parent.
     */
    entities::model object_with_third_degree_parent_missing(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object three levels deep in inheritance tree,
     * with parents in different models.
     */
    std::array<entities::model, 4>
    object_with_third_degree_parent_in_different_models(
        const bool add_model_module = false) const;

    /**
     * @brief Scenario: object three levels deep in inheritance tree,
     * with parents in different models and a missing top-level
     * parent.
     */
    std::array<entities::model, 4>
    object_with_missing_third_degree_parent_in_different_models(
        const bool add_model_module = false) const;

public:
    /**
     * @brief Returns a model with a single object that contains one
     * or two instances of a group of attributes of different types.
     *
     * @param repeat_group if true, adds two instances of the group,
     * otherwise just one.
     */
    entities::model
    object_with_group_of_attributes_of_different_types(
        const identification::entities::model_type mt =
        identification::entities::model_type::target,
        const bool repeat_group = false,
        const bool add_model_module = false) const;

private:
    const flags flags_;
};

}

#endif
