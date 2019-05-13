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
#ifndef DOGEN_ENGINE_TYPES_HELPERS_ADAPTER_HPP
#define DOGEN_ENGINE_TYPES_HELPERS_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include "dogen.variability/types/meta_model/potential_binding.hpp"
#include "dogen.injection/types/meta_model/attribute.hpp"
#include "dogen.injection/types/meta_model/element.hpp"
#include "dogen.coding/types/meta_model/location.hpp"
#include "dogen.coding/types/meta_model/element.hpp"
#include "dogen.coding/types/meta_model/structural/enumerator.hpp"
#include "dogen.coding/types/meta_model/attribute.hpp"
#include "dogen.coding/types/meta_model/structural/enumeration.hpp"
#include "dogen.coding/types/meta_model/structural/primitive.hpp"
#include "dogen.coding/types/meta_model/structural/exception.hpp"
#include "dogen.coding/types/meta_model/element.hpp"
#include "dogen.coding/types/meta_model/structural/object.hpp"
#include "dogen.coding/types/meta_model/structural/module.hpp"
#include "dogen.coding/types/meta_model/structural/builtin.hpp"
#include "dogen.coding/types/meta_model/structural/object_template.hpp"
#include "dogen.coding/types/meta_model/decoration/licence.hpp"
#include "dogen.coding/types/meta_model/decoration/modeline.hpp"
#include "dogen.coding/types/meta_model/decoration/modeline_group.hpp"
#include "dogen.coding/types/meta_model/decoration/generation_marker.hpp"
#include "dogen.coding/types/meta_model/variability/profile_template.hpp"
#include "dogen.coding/types/meta_model/variability/feature_bundle.hpp"
#include "dogen.coding/types/meta_model/variability/feature_template_initializer.hpp"
#include "dogen.engine/types/helpers/stereotypes_conversion_result.hpp"

namespace dogen::engine::helpers {

/**
 * @brief Adapts types from the injection model into the coding model.
 */
class adapter final {
private:
    /**
     * @brief Ensure the string is not empty.
     */
    void ensure_not_empty(const std::string& s) const;

    /**
     * @brief Ensure the string is empty.
     */
    void ensure_empty(const std::string& s) const;

private:
    /**
     * @brief Creates a list of potential bindings from a list of stereotypes.
     */
    std::list<variability::meta_model::potential_binding>
    to_potential_binding(const std::list<std::string>& stereotypes) const;

private:
    /**
     * @brief Creates a coding name using the element name provided, and
     * places it in the location provided.
     *
     * @param l location for the name.
     * @param n may be a simple name or a qualified name, via a scope
     * operator.
     *
     * @pre n must not be empty.
     */
    coding::meta_model::name to_name(const coding::meta_model::location& l,
        const std::string& n) const;

    /**
     * @brief Converts an injection attribute to a modeline field.
     *
     * @pre name and value of the injector attribute must not be empty.
     * @pre value of the injector attribute must be empty.
     */
    coding::meta_model::decoration::modeline_field
    to_modeline_field(const injection::meta_model::attribute& ia) const;

    /**
     * @brief Converts an injection attribute to an coding attribute.
     *
     * @pre name of the injector attribute must not be empty.
     */
    coding::meta_model::attribute
    to_attribute(const coding::meta_model::name& owner,
        const injection::meta_model::attribute& ia) const;

    /**
     * @brief Converts an injector attribute to an coding enumerator.
     *
     * @pre name of the injector attribute must not be empty.
     * @pre type and value of the injector attribute must be empty.
     */
    coding::meta_model::structural::enumerator
    to_enumerator(const coding::meta_model::name& owner,
        const injection::meta_model::attribute& ia) const;

private:
    /**
     * @brief Populates the meta-model element attributes using the
     * injection element.
     */
    void populate_element(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie,
        coding::meta_model::element& e) const;

public:
    /**
     * @brief Converts an injection element with a stereotype of
     * masd::object to a coding object.
     */
    boost::shared_ptr<coding::meta_model::structural::object>
    to_object(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::object_template to a coding object template.
     */
    boost::shared_ptr<coding::meta_model::structural::object_template>
    to_object_template(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::exception to a coding exception.
     */
    boost::shared_ptr<coding::meta_model::structural::exception>
    to_exception(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::primitive to a coding primitive.
     */
    boost::shared_ptr<coding::meta_model::structural::primitive>
    to_primitive(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::enumeration to a coding enumeration.
     */
    boost::shared_ptr<coding::meta_model::structural::enumeration>
    to_enumeration(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::module to a coding module.
     */
    boost::shared_ptr<coding::meta_model::structural::module>
    to_module(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::builtin to a coding builtin.
     */
    boost::shared_ptr<coding::meta_model::structural::builtin>
    to_builtin(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::modeline_group to a coding modeline group.
     */
    boost::shared_ptr<coding::meta_model::decoration::modeline_group>
    to_modeline_group(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::modeline to a coding modeline.
     */
    boost::shared_ptr<coding::meta_model::decoration::modeline>
    to_modeline(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::generation_marker to a coding generation marker.
     */
    boost::shared_ptr<coding::meta_model::decoration::generation_marker>
    to_generation_marker(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::licence to a coding licence.
     */
    boost::shared_ptr<coding::meta_model::decoration::licence>
    to_licence(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::to_variability_profile_template to a variability feature
     * template group.
     */
    boost::shared_ptr<coding::meta_model::variability::profile_template>
    to_variability_profile_template(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::variability_feature_bundle to a coding
     * variability feature template group
     */
    boost::shared_ptr<coding::meta_model::variability::feature_bundle>
    to_variability_feature_bundle(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::variability_feature_template_initializer to a coding
     * variability feature template group registrar.
     */
    boost::shared_ptr<
        coding::meta_model::variability::feature_template_initializer
        >
    to_variability_feature_template_initializer(
        const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;
};

}

#endif
