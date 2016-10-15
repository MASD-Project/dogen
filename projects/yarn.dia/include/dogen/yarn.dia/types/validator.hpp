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
#ifndef DOGEN_YARN_DIA_TYPES_VALIDATOR_HPP
#define DOGEN_YARN_DIA_TYPES_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn.dia/types/processed_object.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Validates the consistency of the processed object.
 *
 * The following are the rules a profile is expected to follow:
 *
 * @li have exactly one UML type, such as class, generalisation, etc.
 *
 * @li have zero or one stereotype with Yarn type information, such as
 * enumeration, value object, etc. The Yarn type must be compatible
 * with the UML type.
 *
 * @li have any number of known stereotypes that are options dependent
 * on the Yarn type.
 *
 * Unknown stereotypes are largely ignored by the validator, other
 * than making sure that they belong to Yarn types which support them.
 */
class validator {
public:
    validator() = default;
    validator(const validator&) = delete;
    validator(validator&&) = default;

private:
    /**
     * @brief Checks all data related to Yarn.
     */
    void validate_yarn(const processed_object& p) const;

    /**
     * @brief Checks all data related to UML.
     */
    void validate_uml(const processed_object& p) const;

public:
    /**
     * @brief Validates a processed object.
     *
     */
    void validate(const processed_object& p) const;

    /**
     * @brief Throws an exception if any of the processed objects are
     * not considered to be valid.
     */
    void validate(const std::list<processed_object>& pos) const;
};

} } }

#endif
