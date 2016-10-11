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
#ifndef DOGEN_ANNOTATIONS_TEST_MOCK_TYPE_REPOSITORY_FACTORY_HPP
#define DOGEN_ANNOTATIONS_TEST_MOCK_TYPE_REPOSITORY_FACTORY_HPP

#include <list>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository.hpp"

namespace dogen {
namespace annotations {
namespace test {

/**
 * @brief Generates a mock type repository with a number of types in
 * it.
 */
class mock_type_repository_factory {
private:
    /**
     * @brief Adds the type to the repository, populating all of the
     * required containers.
     */
    void add_type(const type& t, type_repository& trp) const;

public:
    /**
     * @brief Creates the repository with canned types, adding any
     * additional types the user may supply.
     */
    type_repository make(const std::list<type>& additional_types =
        std::list<type> {});
};

} } }

#endif
