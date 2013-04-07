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
#ifndef DOGEN_DIA_TO_SML_TYPES_OBJECT_TRANSFORMER_HPP
#define DOGEN_DIA_TO_SML_TYPES_OBJECT_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include "dogen/dia/types/composite.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/dia/types/object.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/package.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/dia/types/stereotypes.hpp"
#include "dogen/sml/types/meta_types.hpp"
#include "dogen/sml/types/enumerator.hpp"
#include "dogen/sml/types/identifier_parser.hpp"
#include "dogen/sml/types/comments_parser.hpp"
#include "dogen/dia/types/object_fwd.hpp"
#include "dogen/dia/types/object_types.hpp"
#include "dogen/dia_to_sml/types/context.hpp"
#include "dogen/dia_to_sml/types/object_transformer_interface.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Transforms dia objects
 */
class object_transformer : public object_transformer_interface {
public:
    object_transformer(const object_transformer&) = delete;
    object_transformer(object_transformer&&) = default;

public:
    explicit object_transformer(context& c);
    virtual ~object_transformer() noexcept;

private:
    /**
     * @brief Given a dia object type as a string, returns the
     * appropriate enumeration for it.
     */
    dia::object_types parse_object_types(const std::string type) const;

    /**
     * @brief Compute all the model dependencies implied by a given
     * nested qname
     */
    void compute_model_dependencies(const sml::nested_qname& nqn);

    /**
     * @brief Parses a Dia string attribute, removing any invalid formatting.
     */
    std::string
    transform_string_attribute(const dia::attribute& attribute) const;

    /**
     * @brief Converts the Dia attribute into a qname.
     *
     * @param attribute Name Dia attribute.
     */
    sml::qname transform_qname(const dia::attribute& attribute,
        sml::meta_types meta_type, const std::string& pkg_id) const;

    /**
     * @brief Converts a Dia composite storing the UML attribute into
     * an SML property
     *
     * @param uml_attribute the Dia UML attribute
     */
    sml::property transform_property(const dia::composite& uml_attribute);

    /**
     * @brief Transforms the attribute into a SML enumerator.
     */
    sml::enumerator transform_enumerator(const dia::composite& uml_attribute,
        const unsigned int position) const;

    /**
     * @brief Ensure the type of the object is a dia UML class.
     */
    void ensure_object_is_uml_class(const dia::object_types ot) const;

    /**
     * @brief Returns the stereotype for the object.
     */
    dia::stereotypes stereotype_for_object(const dia::object& o) const;

    /**
     * @brief Converts a object containing a class into an pod.
     *
     * @param o the Dia UML class
     */
    void transform_pod(const dia::object& o);

    /**
     * @brief Converts a object containing a class into an enumeration.
     *
     * @param o the Dia UML class
     */
    void transform_enumeration(const dia::object& o);

    /**
     * @brief Converts a dia object of type large UML package into a
     * package in SML.
     *
     * @param o Dia object which contains a UML package.
     */
    void transform_package(const dogen::dia::object& o);

    /**
     * @brief Converts a dia object with a stereotype of exception
     * into a SML exception.
     *
     * @param o Dia object which contains an exception.
     */
    void transform_exception(const dogen::dia::object& o);

public:
    virtual void transform(const dia::object& o) override;

private:
    context& context_;
    std::shared_ptr<sml::identifier_parser> identifier_parser_;
    std::shared_ptr<sml::comments_parser> comments_parser_;
};

} }

#endif
