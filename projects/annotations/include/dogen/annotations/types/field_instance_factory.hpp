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
#ifndef DOGEN_ANNOTATIONS_TYPES_FIELD_FACTORY_HPP
#define DOGEN_ANNOTATIONS_TYPES_FIELD_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/value.hpp"
#include "dogen/annotations/types/value_factory.hpp"
#include "dogen/annotations/types/field_instance.hpp"
#include "dogen/annotations/types/field_definition.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Builds a field from its constituent parts.
 */
class field_instance_factory {
public:
    field_instance_factory();

private:
    /**
     * @brief Throws if the collection has more than one element.
     */
    void ensure_at_most_one_element(const std::list<std::string>& v) const;

public:
    /**
     * @brief Creates a field instance given a definition, the
     * original key and zero or more values.
     *
     * @pre If values has more than one element, the field's value
     * type must be a collection.
     *
     * @pre Values must be valid according to the type in the field
     * definition.
     */
    field_instance make(const field_definition& fd,
        const std::list<std::string>& v) const;

    /**
     * @brief Creates a field instance from the default value.
     *
     * @pre fd must have a default value.
     */
    field_instance make(const field_definition& fd) const;

public:
    /**
     * @brief Makes a field instance with a text value.
     */
    field_instance make_text(const std::string& v) const;

    /**
     * @brief Makes a field instance with a text value using the
     * generic string version of the path.
     */
    field_instance make_text(const boost::filesystem::path& v) const;

    /**
     * @brief Makes a field instance with a collection of text values.
     */
    field_instance make_text_collection(const std::list<std::string>& v) const;

    /**
     * @brief Makes a field instance with a boolean value.
     */
    /**@{*/
    field_instance make_boolean(const std::string& v) const;
    field_instance make_boolean(const bool v) const;
    /**@}*/

    /**
     * @brief Makes a field instance with a number value.
     */
    /**@{*/
    field_instance make_number(const std::string& v) const;
    field_instance make_number(const bool v) const;
    /**@}*/

private:
    const value_factory value_factory_;
};

} }

#endif
