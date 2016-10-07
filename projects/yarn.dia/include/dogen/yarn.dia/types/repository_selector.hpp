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
#ifndef DOGEN_YARN_DIA_TYPES_REPOSITORY_SELECTOR_HPP
#define DOGEN_YARN_DIA_TYPES_REPOSITORY_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn.dia/types/repository.hpp"

namespace dogen {
namespace yarn {
namespace dia {

class const_repository_selector {
public:
    explicit const_repository_selector(const repository& rp);

private:
    void validate_id(const std::string& id) const;

public:
    /**
     * @brief Returns the module associated with a name.
     *
     * @pre module must exist in repository.
     */
    const yarn::module& module_for_name(const yarn::name& n) const;

    /**
     * @brief Returns the module associated with a dia package id.
     *
     * @pre id must be a valid package ID in the diagram.
     * @pre corresponding module must have already been generated.
     */
    const yarn::module& module_for_id(const std::string& id) const;

    /**
     * @brief Returns a list of all parent names for a given child dia
     * object id.
     *
     * @pre id must exist in repository.
     */
    std::list<yarn::name> parent_names_for_id(const std::string& id) const;

    yarn::name name_for_id(const std::string& id) const;

private:
    const repository& repository_;
};

class repository_selector {
public:
    explicit repository_selector(repository& rp);

public:
    /**
     * @brief Returns the module associated with a name.
     *
     * @pre module must exist in repository.
     */
    yarn::module& module_for_name(const yarn::name& n);

    /**
     * @brief Returns the module associated with a dia package id.
     *
     * @pre id must be a valid package ID in the diagram.
     * @pre corresponding module must have already been generated.
     */
    yarn::module& module_for_id(const std::string& id);

private:
    repository& repository_;
};

} } }

#endif
