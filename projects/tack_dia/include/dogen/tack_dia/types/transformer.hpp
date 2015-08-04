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
#ifndef DOGEN_TACK_DIA_TYPES_TRANSFORMER_HPP
#define DOGEN_TACK_DIA_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include "dogen/dia/types/object.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/tack/types/nested_qname.hpp"
#include "dogen/tack/types/object.hpp"
#include "dogen/tack/types/identifier_parser.hpp"
#include "dogen/tack_dia/types/processed_object.hpp"
#include "dogen/tack_dia/types/processed_property.hpp"
#include "dogen/tack_dia/types/context.hpp"
#include "dogen/tack_dia/types/profile.hpp"

namespace dogen {
namespace tack_dia {

/**
 * @brief Transforms Dia objects into their TACK counterpart.
 */
class transformer {
public:
    transformer() = delete;
    transformer(const transformer&) = delete;
    transformer(transformer&&) = default;
    ~transformer() noexcept = default;

public:
    /**
     * @brief Initialises the transformer.
     *
     * @pre model in context must be populated.
     */
    transformer(const dynamic::workflow& w, context& c);

private:
    /**
     * @brief Update the model references with those which are implied
     * by the given nested qname.
     */
    void update_model_references(const tack::nested_qname& nqn);

    /**
     * @brief Ensure that the processed object implies an TACK type
     * which is supported by the transformer.
     */
    void require_is_transformable(const processed_object& o) const;

private:
    /**
     * @brief Compute the appropriate generation type for the profile.
     */
    tack::generation_types generation_type(const profile& p) const;

private:
    /**
     * @brief Creates a qname using the name provided and the package
     * ID.
     *
     * @pre n must not be empty.
     * @pre n must be a simple name, not a qualified name.
     */
    tack::qname to_qname(const std::string& n) const;

    /**
     * @brief Creates a qname using the name provided, which is
     * interpreted as belonging to supplied module qname
     *
     * @pre n must not be empty.
     * @pre n must be a simple name, not a qualified name.
     */
    tack::qname to_qname(const std::string& n,
        const tack::qname& module_qn) const;

    /**
     * @brief Creates a nested qname from a string representation of a
     * qualified name.
     *
     * @pre n must not be empty.
     */
    tack::nested_qname to_nested_qname(const std::string& n) const;

    /**
     * @brief Converts processed property into an TACK property.
     *
     * @param p the Dia UML attribute in processed form.
     *
     * @pre name of property must not be empty.
     * @pre type of property must not be empty.
     */
    tack::property to_property(const processed_property& p) const;

    /**
     * @brief Converts processed property into an TACK enumerator.
     *
     * @param p the Dia UML attribute in processed form.
     * @param value what value should the enumeration take.
     *
     * @pre name of property must not be empty.
     * @pre type of property must be empty.
     */
    tack::enumerator to_enumerator(const processed_property& p,
        const unsigned int value) const;

private:
    /**
     * @brief Returns the module associated with a qname.
     *
     * @pre module must exist in context.
     */
    tack::module& module_for_qname(const tack::qname& qn);

    /**
     * @brief Returns the module associated with a dia package id.
     *
     * @pre pkg_id must be a valid package ID in the diagram.
     * @pre corresponding module must have already been generated.
     */
    tack::module& module_for_id(const std::string& id);

    /**
     * @brief Update the TACK element using the processed object and
     * the profile. Also adds element's qname to the containing
     * module, if any.
     */
    template<typename Element>
    void update_element(Element& e, const processed_object& o,
        const profile& p) {
        e.generation_type(generation_type(p));
        e.origin_type(tack::origin_types::user);

        const auto pkg_id(o.child_node_id());
        if (!pkg_id.empty()) {
            auto& module(module_for_id(pkg_id));
            e.name(to_qname(o.name(), module.name()));
            module.members().push_back(e.name());
            e.containing_module(module.name());
        } else {
            // type belongs to the synthetic module for the model;
            // do not add it to the qname.
            e.name(to_qname(o.name()));
            auto& module(module_for_qname(context_.model().name()));
            module.members().push_back(e.name());
            e.containing_module(module.name());
        }

        context_.id_to_qname().insert(std::make_pair(o.id(), e.name()));

        e.documentation(o.comment().documentation());

        const auto& kvps(o.comment().key_value_pairs());
        const auto scope(dynamic::scope_types::entity);
        e.extensions(dynamic_workflow_.execute(scope, kvps));
    }

    /**
     * @brief Update the TACK abstract object using the processed
     * object and the profile.
     */
    void update_object(tack::object& ao, const processed_object& o,
        const profile& p);

private:
    /**
     * @brief Converts a processed object containing a UML class with
     * a stereotype of exception to a TACK exception.
     *
     * @param o the Dia UML class containing an enumeration.
     * @param p profile of the object.
     *
     * @pre profile must have the exception flag set.
     */
    void to_exception(const processed_object& o, const profile& p);

    /**
     * @brief Converts Dia a object containing a UML class with a
     * stereotype of service to a TACK service.
     *
     * @param o the Dia UML class containing an enumeration.
     * @param p profile of the object.
     *
     * @pre profile must have the service flag set.
     */
    void to_service(const processed_object& o, const profile& p);

    /**
     * @brief Converts Dia a object containing a UML class with a
     * stereotype of value object to a TACK service.
     *
     * @param o the Dia UML class containing a value object.
     * @param p profile of the object.
     *
     * @pre profile must have the value object flag set.
     */
    void to_value_object(const processed_object& o, const profile& p);

    /**
     * @brief Converts a object containing a class into an enumeration.
     *
     * @param o the Dia UML class containing an enumeration.
     */
    void to_enumeration(const processed_object& o, const profile& p);

    /**
     * @brief Converts a dia object of type large UML package into a
     * module in TACK.
     *
     * @param o Dia object which contains a UML package.
     */
    void to_module(const processed_object& o, const profile& p);

    /**
     * @brief Converts a dia object of type UML note into
     * documentation, if the appropriate dogen tags are found.
     *
     * @param o Dia object which contains a UML note.
     */
    void from_note(const processed_object& o);

    /**
     * @brief Converts a dia object with a stereotype of concept
     * into a TACK concept.
     *
     * @param o Dia object which contains a concept.
     */
    void to_concept(const processed_object& o, const profile& p);

private:
    /**
     * @brief Dispatches the objects to the correct transformation.
     *
     * @pre Object must be transformable.
     */
    void dispatch(const processed_object& o, const profile& p);

public:
    /**
     * @brief Checks if the processed object implies an TACK type which
     * is supported by the transformer.
     */
    bool is_transformable(const processed_object& o) const;

    /**
     * @brief Transform a dia object.
     *
     * @pre Object must be transformable.
     */
    void transform(const processed_object& o, const profile& p);

private:
    context& context_;
    std::shared_ptr<tack::identifier_parser> identifier_parser_;
    const dynamic::workflow& dynamic_workflow_;
};

} }

#endif
