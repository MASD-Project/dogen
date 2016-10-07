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
#ifndef DOGEN_YARN_DIA_TYPES_TRANSFORMER_HPP
#define DOGEN_YARN_DIA_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include "dogen/dia/types/object.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/processed_attribute.hpp"
#include "dogen/yarn.dia/types/repository.hpp"
#include "dogen/yarn.dia/types/profile.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Transforms Dia objects into their yarn counterpart.
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
     * @pre model in repository must be populated.
     */
    transformer(const dynamic::workflow& w, const repository& rp);

private:
    /**
     * @brief Compute the appropriate generation type for the profile.
     */
    yarn::generation_types generation_type(const profile& p) const;

    /**
     * @brief Ensure the dia object name is valid.
     */
    void validate_dia_object_name(const std::string& n) const;

private:
    /**
     * @brief Creates a name using the name provided and the package
     * ID.
     *
     * @pre n must not be empty.
     * @pre n must be a simple name, not a qualified name.
     */
    yarn::name to_name(const std::string& n) const;

    /**
     * @brief Creates a name using the name provided, which is
     * interpreted as belonging to supplied module name
     *
     * @pre n must not be empty.
     * @pre n must be a simple name, not a qualified name.
     */
    yarn::name to_name(const std::string& n,
        const yarn::name& module_name) const;

    /**
     * @brief Converts a processed attribute into an yarn attribute.
     *
     * @param p the Dia UML attribute in processed form.
     *
     * @pre name of attribute must not be empty.
     * @pre type of attribute must not be empty.
     */
    yarn::attribute to_attribute(const yarn::name& owning_element,
        const processed_attribute& a) const;

    /**
     * @brief Converts processed property into an yarn enumerator.
     *
     * @param p the Dia UML attribute in processed form.
     * @param value what value should the enumeration take.
     *
     * @pre name of property must not be empty.
     * @pre type of property must be empty.
     */
    yarn::enumerator to_enumerator(const processed_attribute& a,
        const unsigned int value) const;

private:
    /**
     * @brief Update the yarn element using the processed object and
     * the profile. Also adds element's name to the containing
     * module, if any.
     */
    void update_element(const processed_object& o, const profile& p,
        yarn::element& e);

public:
    /**
     * @brief Converts a processed object containing a UML class with
     * a stereotype of exception to a yarn exception.
     *
     * @param o the Dia UML class containing an enumeration.
     * @param p profile of the object.
     *
     * @pre profile must have the exception flag set.
     */
    yarn::exception to_exception(const processed_object& o, const profile& p);

    /**
     * @brief Converts Dia a object containing a UML class with a
     * stereotype of value object or service to a yarn object.
     *
     * @param o the Dia UML class containing a value object or service.
     * @param p profile of the object.
     *
     * @pre profile must have the value object flag set.
     */
    yarn::object to_object(const processed_object& po, const profile& p,
        const yarn::object_types ot);

    /**
     * @brief Converts a object containing a class into an enumeration.
     *
     * @param o the Dia UML class containing an enumeration.
     */
    yarn::enumeration to_enumeration(const processed_object& o,
        const profile& p);

    /**
     * @brief Converts a dia object of type large UML package into a
     * module in yarn.
     *
     * @param o Dia object which contains a UML package.
     */
    yarn::module to_module(const processed_object& o, const profile& p);

    /**
     * @brief Converts a dia object with a stereotype of concept
     * into a yarn concept.
     *
     * @param o Dia object which contains a concept.
     */
    yarn::concept to_concept(const processed_object& o, const profile& p);

private:
    const repository& repository_;
    const dynamic::workflow& dynamic_workflow_;
};

} } }

#endif
