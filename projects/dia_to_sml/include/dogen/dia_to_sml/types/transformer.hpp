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
#ifndef DOGEN_DIA_TO_SML_TYPES_TRANSFORMER_HPP
#define DOGEN_DIA_TO_SML_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include "dogen/dia/types/object.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/meta_types.hpp"
#include "dogen/sml/types/enumerator.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"
#include "dogen/dia_to_sml/types/processed_property.hpp"
#include "dogen/dia_to_sml/types/identifier_parser.hpp"
#include "dogen/dia_to_sml/types/comments_parser.hpp"
#include "dogen/dia_to_sml/types/context.hpp"
#include "dogen/dia_to_sml/types/object_profile.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Transforms dia objects
 */
class transformer {
public:
    transformer() = delete;
    transformer(const transformer&) = delete;
    transformer(transformer&&) = default;
    ~transformer() noexcept = default;

public:
    explicit transformer(context& c);

private:
    /**
     * @brief Compute all the model dependencies implied by a given
     * nested qname
     */
    void compute_model_dependencies(const sml::nested_qname& nqn);

    /**
     * @brief Checks that the type of the object is a processable
     * type.
     */
    void ensure_type_is_processable(const object_profile& op,
        const processed_object& po) const;

private:
    /**
     * @brief Converts the Dia attribute into a qname.
     */
    sml::qname transform_qname(const std::string& n,
        sml::meta_types meta_type, const std::string& pkg_id) const;

    /**
     * @brief Converts a Dia composite storing the UML attribute into
     * an SML property
     *
     * @param uml_attribute the Dia UML attribute
     */
    sml::property transform_property(const processed_property& p);

    /**
     * @brief Transforms the attribute into a SML enumerator.
     */
    sml::enumerator transform_enumerator(const processed_property& p,
        const unsigned int position) const;

    /**
     * @brief Converts a object containing a class into an pod.
     */
    void transform_pod(const object_profile& op, const processed_object& po);

    /**
     * @brief Converts a object containing a class into a service.
     *
     * @param o the Dia UML class containing a service.
     */
    void transform_service(const processed_object& o);

    /**
     * @brief Converts a object containing a class into an enumeration.
     *
     * @param o the Dia UML class containing an enumeration.
     */
    void transform_enumeration(const processed_object& o);

    /**
     * @brief Converts a dia object of type large UML package into a
     * module in SML.
     *
     * @param o Dia object which contains a UML package.
     */
    void transform_module(const processed_object& o);

    /**
     * @brief Converts a dia object of type UML note into
     * documentation, if the appropriate dogen tags are found.
     *
     * @param o Dia object which contains a UML note.
     */
    void transform_note(const processed_object& o);

    /**
     * @brief Converts a dia object with a stereotype of exception
     * into a SML exception.
     *
     * @param o Dia object which contains an exception.
     */
    void transform_exception(const processed_object& o);

public:
    /**
     * @brief Transform a dia object.
     */
    void transform(const processed_object& o, const object_profile& op);

private:
    context& context_;
    std::shared_ptr<identifier_parser> identifier_parser_;
    std::shared_ptr<comments_parser> comments_parser_;
};

} }

#endif
