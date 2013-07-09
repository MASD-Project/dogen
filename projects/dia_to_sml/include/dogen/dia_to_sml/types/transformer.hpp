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
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/abstract_entity.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"
#include "dogen/dia_to_sml/types/processed_property.hpp"
#include "dogen/dia_to_sml/types/identifier_parser.hpp"
#include "dogen/dia_to_sml/types/comments_parser.hpp"
#include "dogen/dia_to_sml/types/context.hpp"
#include "dogen/dia_to_sml/types/profile.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Transforms Dia objects into their SML counterpart.
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
    explicit transformer(context& c);

private:
    /**
     * @brief Update the model references with those which are implied
     * by the given nested qname.
     */
    void update_model_references(const sml::nested_qname& nqn);

    /**
     * @brief Ensure that the processed object implies an SML type
     * which is supported by the transformer.
     */
    void require_is_transformable(const processed_object& o) const;

private:
    /**
     * @brief Compute the appropriate generation type for the profile.
     */
    sml::generation_types generation_type(const profile& p) const;

private:
    /**
     * @brief Creates a qname using the name provided and the package
     * ID.
     *
     * @pre n must not be empty.
     * @pre n must be a simple name, not a qualified name.
     * @pre if supplied pkg_id must be the object ID of a package.
     */
    sml::qname to_qname(const std::string& n,
        const std::string& pkg_id = std::string()) const;

    /**
     * @brief Creates a nested qname from a string representation of a
     * qualified name.
     *
     * @pre n must not be empty.
     */
    sml::nested_qname to_nested_qname(const std::string& n) const;

    /**
     * @brief Converts processed property into an SML property.
     *
     * @param p the Dia UML attribute in processed form.
     *
     * @pre name of property must not be empty.
     * @pre type of property must not be empty.
     */
    sml::property to_property(const processed_property& p) const;

    /**
     * @brief Converts processed property into an SML enumerator.
     *
     * @param p the Dia UML attribute in processed form.
     * @param value what value should the enumeration take.
     *
     * @pre name of property must not be empty.
     * @pre type of property must be empty.
     */
    sml::enumerator to_enumerator(const processed_property& p,
        const unsigned int value) const;

private:
    /**
     * @brief Update the SML element using the processed object and the
     * profile.
     */
    template<typename Element>
    void update_element(Element& e, const processed_object& o,
        const profile& p) {
        e.generation_type(generation_type(p));
        e.origin_type(sml::origin_types::user);
        e.name(to_qname(o.name(), o.child_node_id()));
        context_.id_to_qname().insert(std::make_pair(o.id(), e.name()));

        const auto pair(comments_parser_->parse(o.comment()));
        e.documentation(pair.first);
        e.implementation_specific_parameters(pair.second);
    }

    /**
     * @brief Update the SML abstract object using the processed
     * object and the profile.
     */
    void update_abstract_object(sml::abstract_object& ao,
        const processed_object& o, const profile& p);

    /**
     * @brief Update the SML abstract entity using the processed
     * object and the profile.
     */
    void update_abstract_entity(sml::abstract_entity& ae,
        const processed_object& o, const profile& p);

private:
    /**
     * @brief Converts a processed object containing a UML class with
     * a stereotype of keyed entity to an SML keyed entity.
     *
     * @param o the processed object containing a keyed entity.
     * @param p profile of the object.
     *
     * @pre profile must have the keyed entity flag set.
     */
    void to_keyed_entity(const processed_object& o, const profile& p);

    /**
     * @brief Converts a processed object containing a UML class with a
     * stereotype of entity to an SML entity.
     *
     * @param o the processed object containing an entity.
     * @param p profile of the object.
     *
     * @pre profile must have the entity flag set.
     */
    void to_entity(const processed_object& o, const profile& p);

    /**
     * @brief Converts a processed object containing a UML class with
     * a stereotype of exception to a SML exception.
     *
     * @param o the Dia UML class containing an enumeration.
     * @param p profile of the object.
     *
     * @pre profile must have the exception flag set.
     */
    void to_exception(const processed_object& o, const profile& p);

    /**
     * @brief Converts Dia a object containing a UML class with a
     * stereotype of service to a SML service.
     *
     * @param o the Dia UML class containing an enumeration.
     * @param p profile of the object.
     *
     * @pre profile must have the service flag set.
     */
    void to_service(const processed_object& o, const profile& p);

    /**
     * @brief Converts Dia a object containing a UML class with a
     * stereotype of factory to a SML service.
     *
     * @param o the Dia UML class containing an enumeration.
     * @param p profile of the object.
     *
     * @pre profile must have the factory flag set.
     */
    void to_factory(const processed_object& o, const profile& p);

    /**
     * @brief Converts Dia a object containing a UML class with a
     * stereotype of repository to a SML service.
     *
     * @param o the Dia UML class containing an repository.
     * @param p profile of the object.
     *
     * @pre profile must have the repository flag set.
     */
    void to_repository(const processed_object& o, const profile& p);

    /**
     * @brief Converts Dia a object containing a UML class with a
     * stereotype of value object to a SML service.
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
     * module in SML.
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
     * into a SML concept.
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
     * @brief Checks if the processed object implies an SML type which
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
    std::shared_ptr<identifier_parser> identifier_parser_;
    std::shared_ptr<comments_parser> comments_parser_;
};

} }

#endif
