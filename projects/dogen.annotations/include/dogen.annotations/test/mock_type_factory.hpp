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
#ifndef DOGEN_ANNOTATIONS_TEST_MOCK_TYPE_FACTORY_HPP
#define DOGEN_ANNOTATIONS_TEST_MOCK_TYPE_FACTORY_HPP

#include <list>
#include "dogen.annotations/types/value_types.hpp"
#include "dogen.annotations/types/type.hpp"

namespace dogen::annotations::test {

/**
 * @brief Generates field definitions.
 */
class mock_type_factory {
private:
    /**
     * @brief Creat the containing namespaces field.
     */
    type containing_namespaces() const;

    /**
     * @brief Creat the copyright notice field.
     */
    type copyright_notice() const;

    /**
     * @brief Create the licence name field.
     */
    type licence_name() const;

    /**
     * @brief Create the comment field.
     */
    type create_comment() const;

public:
    /**
     * @brief Creates a set of canned field definitions, needed for
     * testing.
     */
    std::list<type> make_canned_types() const;

    /**
     * @brief Creates a field definition with most values set to
     * sensible defaults.
     */
    type make_type(const std::string n,
        value_types vt = value_types::text) const;
};

}

#endif
