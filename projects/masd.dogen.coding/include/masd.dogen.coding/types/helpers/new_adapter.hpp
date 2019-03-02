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
#ifndef MASD_DOGEN_CODING_TYPES_HELPERS_NEW_ADAPTER_HPP
#define MASD_DOGEN_CODING_TYPES_HELPERS_NEW_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.annotations/types/annotation_expander.hpp"
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
#include "masd.dogen.coding/types/helpers/stereotypes_conversion_result.hpp"

namespace masd::dogen::coding::helpers {

class new_adapter final {
public:
    explicit new_adapter(const annotations::annotation_expander& e);

private:
    /**
     * @brief Ensure the name is not empty.
     */
    void ensure_not_empty(const std::string& n) const;

private:
    /**
     * @brief Creates a coding name using the element name provided, and
     * places it in the location provided.
     *
     * n may be a simple name or a qualified name.
     *
     * @pre n must not be empty.
     */
    meta_model::name to_name(const meta_model::location& l,
        const std::string& n) const;

    /**
     * @brief Converts an injection attribute to an coding attribute.
     *
     * @pre name and type of the injector attribute must not be empty.
     */
    meta_model::attribute to_attribute(const meta_model::location& l,
        const injection::meta_model::attribute& ia) const;

    /**
     * @brief Converts an injector attribute to an coding enumerator.
     *
     * @pre name and type of the injector attribute must not be empty.
     */
    meta_model::enumerator to_enumerator(const meta_model::location& l,
        const injection::meta_model::attribute& ia) const;

private:
    /**
     * @brief Populates the meta-model element attributes using the
     * injection element.
     */
    void populate_element(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie, meta_model::element& e) const;

public:
    /**
     * @brief Converts an exoelement with a stereotype of coding::object
     * to a coding object.
     */
    boost::shared_ptr<meta_model::object>
    to_object(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * coding::object_template to a coding object template.
     */
    boost::shared_ptr<meta_model::object_template>
    to_object_template(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * coding::exception to a coding exception.
     */
    boost::shared_ptr<meta_model::exception>
    to_exception(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * coding::primitive to a coding primitive.
     */
    boost::shared_ptr<meta_model::primitive>
    to_primitive(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * coding::enumeration to a coding enumeration.
     */
    boost::shared_ptr<meta_model::enumeration>
    to_enumeration(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * coding::module to a coding module.
     */
    boost::shared_ptr<meta_model::module>
    to_module(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * coding::module to a coding module.
     */
    boost::shared_ptr<meta_model::builtin>
    to_builtin(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const injection::meta_model::element& ie) const;

private:
    const annotations::annotation_expander& annotation_expander_;
};

}

#endif
