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
#ifndef DOGEN_YARN_TYPES_HELPERS_NEW_ADAPTER_HPP
#define DOGEN_YARN_TYPES_HELPERS_NEW_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include "dogen.annotations/types/scope_types.hpp"
#include "dogen.annotations/types/annotation_factory.hpp"
#include "dogen.external/types/meta_model/attribute.hpp"
#include "dogen.external/types/meta_model/element.hpp"
#include "dogen.modeling/types/meta_model/location.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.modeling/types/meta_model/enumerator.hpp"
#include "dogen.modeling/types/meta_model/attribute.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/types/meta_model/primitive.hpp"
#include "dogen.modeling/types/meta_model/exception.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/module.hpp"
#include "dogen.modeling/types/meta_model/builtin.hpp"
#include "dogen.modeling/types/meta_model/object_template.hpp"
#include "dogen.modeling/types/helpers/stereotypes_conversion_result.hpp"

namespace dogen {
namespace modeling {
namespace helpers {

class new_adapter final {
public:
    explicit new_adapter(const annotations::annotation_factory& f);

private:
    /**
     * @brief Ensure the name is not empty.
     */
    void ensure_not_empty(const std::string& n) const;

private:
    /**
     * @brief Creates a yarn name using the element name provided, and
     * places it in the location provided.
     *
     * n may be a simple name or a qualified name.
     *
     * @pre n must not be empty.
     */
    meta_model::name to_name(const meta_model::location& l,
        const std::string& n) const;

    /**
     * @brief Converts an external attribute to an yarn attribute.
     *
     * @pre name and type of the external attribute must not be empty.
     */
    meta_model::attribute to_attribute(const meta_model::location& l,
        const external::meta_model::attribute& a) const;

    /**
     * @brief Converts an external attribute to an yarn enumerator.
     *
     * @pre name and type of the external attribute must not be empty.
     */
    meta_model::enumerator to_enumerator(const meta_model::location& l,
        const external::meta_model::attribute& a) const;

private:
    /**
     * @brief Populates the meta-model element attributes using the
     * external element.
     */
    void populate_element(const annotations::scope_types scope,
        const meta_model::location& l, const stereotypes_conversion_result& scr,
        const external::meta_model::element& ee, meta_model::element& e) const;

public:
    /**
     * @brief Converts an exoelement with a stereotype of modeling::object
     * to a yarn object.
     */
    boost::shared_ptr<meta_model::object>
    to_object(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const external::meta_model::element& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * modeling::object_template to a yarn object template.
     */
    boost::shared_ptr<meta_model::object_template>
    to_object_template(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const external::meta_model::element& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * modeling::exception to a yarn exception.
     */
    boost::shared_ptr<meta_model::exception>
    to_exception(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const external::meta_model::element& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * modeling::primitive to a yarn primitive.
     */
    boost::shared_ptr<meta_model::primitive>
    to_primitive(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const external::meta_model::element& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * modeling::enumeration to a yarn enumeration.
     */
    boost::shared_ptr<meta_model::enumeration>
    to_enumeration(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const external::meta_model::element& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * modeling::module to a yarn module.
     */
    boost::shared_ptr<meta_model::module>
    to_module(const bool is_root_module, const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const external::meta_model::element& ee) const;

    /**
     * @brief Converts an exoelement with a stereotype of
     * modeling::module to a yarn module.
     */
    boost::shared_ptr<meta_model::builtin>
    to_builtin(const meta_model::location& l,
        const stereotypes_conversion_result& scr,
        const external::meta_model::element& ee) const;

private:
    const annotations::annotation_factory& annotation_factory_;
};

} } }

#endif
