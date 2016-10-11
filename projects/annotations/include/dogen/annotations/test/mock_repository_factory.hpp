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
#ifndef DOGEN_ANNOTATIONS_TEST_MOCK_REPOSITORY_FACTORY_HPP
#define DOGEN_ANNOTATIONS_TEST_MOCK_REPOSITORY_FACTORY_HPP

#include <list>
#include "dogen/annotations/types/field_definition.hpp"
#include "dogen/annotations/types/repository.hpp"

namespace dogen {
namespace annotations {
namespace test {

/**
 * @brief Generates a mock repository with a number of fields in it.
 */
class mock_repository_factory {
private:
    /**
     * @brief Adds the field definition to the repository, populating
     * all of the required containers.
     */
    void add_field_definition(const field_definition& fd, repository& rp) const;

public:
    /**
     * @brief Creates the repository with canned fields, adding any
     * additional fields the user may supply.
     */
    repository make(const std::list<field_definition>& additional_fields =
        std::list<field_definition> {});
};

} } }

#endif
