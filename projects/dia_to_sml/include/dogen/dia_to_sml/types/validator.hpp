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
#include "dogen/dia_to_sml/types/object_profile.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Checks the profile for consistency.
 */
class validator {
public:
    validator() = default;
    validator(const validator&) = delete;
    validator(validator&&) = default;

private:
    /**
     * @brief Returns the number of stereotypes flags set that are not
     * type related.
     */
    unsigned int count_stereotypes_non_types(const object_profile& op) const;

    /**
     * @brief Returns the number of type related stereotypes flags set.
     */
    unsigned int count_stereotypes_types(const object_profile& op) const;

    /**
     * @brief Checks the stereotype flags.
     */
    void validate_stereotypes(const object_profile& op) const;

    /**
     * @brief Returns the number of type flags set.
     */
    unsigned int count_types(const object_profile& op) const;

    /**
     * @brief Check the object type flags.
     */
    void validate_type(const object_profile& op);

public:
    /**
     * @brief Throws an exception of the object profile is not
     * considered to be valid.
     */
    void validate(const object_profile& op);
};

} }

#endif
