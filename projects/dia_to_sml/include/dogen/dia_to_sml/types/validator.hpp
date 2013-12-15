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
#ifndef DOGEN_DIA_TO_SML_TYPES_VALIDATOR_HPP
#define DOGEN_DIA_TO_SML_TYPES_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia_to_sml/types/profile.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Validates the consistency of the profile.
 *
 * The following are the rules a profile is expected to follow:
 *
 * @li have exactly one UML type, such as class, generalisation, etc.
 *
 * @li have zero or one stereotype with SML type information, such as
 * enumeration, value object, etc. The SML type must be compatible
 * with the UML type.
 *
 * @li have any number of known stereotypes that are options dependent
 * on the SML type.
 *
 * Unknown stereotypes are largely ignored by the validator, other
 * than making sure that they belong to SML types which support them.
 */
class validator {
public:
    validator() = default;
    validator(const validator&) = delete;
    validator(validator&&) = default;

private:
    /**
     * @brief Returns true if the SML flags with type information
     * describe a type which is a descendant of @ref abstract_entity.
     */
    bool is_entity(const profile& p) const;

    /**
     * @brief Returns true if the SML flags with type information
     * describe a type which can support versioning.
     */
    bool is_versionable(const profile& p) const;

    /**
     * @brief Returns true if the SML flags with type information
     * describe a type which is a descendant of @ref object.
     *
     * @pre flags must have been validated for consistency.
     */
    bool is_object(const profile& p) const;

private:
    /**
     * @brief Returns the number of flags that are related to
     * versioning.
     */
    unsigned int count_sml_versioning_flags(const profile& p) const;

    /**
     * @brief Returns the number of flags that are options on SML
     * entity objects.
     */
    unsigned int count_sml_entity_flags(const profile& p) const;

    /**
     * @brief Returns the number of flags that are options on SML
     * objects.
     *
     * By @e object we mean any descendent of @ref object.
     */
    unsigned int count_sml_object_flags(const profile& p) const;

    /**
     * @brief Returns the number of flags that convey type information
     * on SML modeling elements.
     */
    unsigned int count_sml_types(const profile& p) const;

    /**
     * @brief Returns the number of flags set that convey UML type
     * information.
     */
    unsigned int count_uml_types(const profile& p) const;

private:
    /**
     * @brief Checks all flags that are related to SML.
     */
    void validate_sml(const profile& p) const;

    /**
     * @brief Check the UML related flags.
     */
    void validate_uml(const profile& p);

public:
    /**
     * @brief Throws an exception of the object profile is not
     * considered to be valid.
     */
    void validate(const profile& p);
};

} }

#endif
