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
#ifndef MASD_DOGEN_ORCHESTRATION_TYPES_HELPERS_ADAPTER_HPP
#define MASD_DOGEN_ORCHESTRATION_TYPES_HELPERS_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.injection/types/meta_model/attribute.hpp"
#include "masd.dogen.injection/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/location.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/enumerator.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.coding/types/meta_model/modeline.hpp"
#include "masd.dogen.coding/types/meta_model/generation_marker.hpp"
#include "masd.dogen.coding/types/meta_model/licence.hpp"
#include "masd.dogen.coding/types/meta_model/configuration.hpp"
#include "masd.dogen.orchestration/types/helpers/stereotypes_conversion_result.hpp"

namespace masd::dogen::orchestration::helpers {

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
    coding::meta_model::modeline_field
    to_modeline_field(const injection::meta_model::attribute& ia) const;

    /**
     * @brief Converts an injection attribute to an coding attribute.
     *
     * @pre name of the injector attribute must not be empty.
     */
    coding::meta_model::attribute
    to_attribute(const injection::meta_model::attribute& ia) const;

    /**
     * @brief Converts an injector attribute to an coding enumerator.
     *
     * @pre name of the injector attribute must not be empty.
     * @pre type and value of the injector attribute must be empty.
     */
    coding::meta_model::enumerator
    to_enumerator(const injection::meta_model::attribute& ia) const;

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
    boost::shared_ptr<coding::meta_model::object>
    to_object(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * masd::object_template to a coding object template.
     */
    boost::shared_ptr<coding::meta_model::object_template>
    to_object_template(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::exception to a coding exception.
     */
    boost::shared_ptr<coding::meta_model::exception>
    to_exception(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::primitive to a coding primitive.
     */
    boost::shared_ptr<coding::meta_model::primitive>
    to_primitive(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::enumeration to a coding enumeration.
     */
    boost::shared_ptr<coding::meta_model::enumeration>
    to_enumeration(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::module to a coding module.
     */
    boost::shared_ptr<coding::meta_model::module>
    to_module(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::module to a coding module.
     */
    boost::shared_ptr<coding::meta_model::builtin>
    to_builtin(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::modeline_group to a coding module.
     */
    boost::shared_ptr<coding::meta_model::modeline_group>
    to_modeline_group(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::modeline to a coding module.
     */
    boost::shared_ptr<coding::meta_model::modeline>
    to_modeline(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::generation_marker to a coding module.
     */
    boost::shared_ptr<coding::meta_model::generation_marker>
    to_generation_marker(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::licence to a coding module.
     */
    boost::shared_ptr<coding::meta_model::licence>
    to_licence(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an injection element with a stereotype of
     * coding::configuration to a configuration.
     */
    boost::shared_ptr<coding::meta_model::configuration>
    to_configuration(const coding::meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;
};

}

#endif
