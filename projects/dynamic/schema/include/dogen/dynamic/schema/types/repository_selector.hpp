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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_REPOSITORY_SELECTOR_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_REPOSITORY_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

/**
 * @brief Performs a set of canned queries over a repository.
 */
class repository_selector {
public:
    explicit repository_selector(const repository& rp);

public:
    /**
     * @brief Returns the field definition corresponding to the supplied
     * qualified field definition name.
     *
     * @pre name must exist.
     */
    const field_definition& select_field_by_name(const std::string& n) const;

    /**
     * @brief Returns the field definitions corresponding to the
     * supplied formatter name.
     *
     * @pre formatter name must exist.
     */
    const std::list<field_definition>&
    select_fields_by_formatter_name(const std::string& n) const;

    /**
     * @brief Returns the field definitions corresponding to the
     * supplied facet name.
     *
     * @pre facet name must exist.
     */
    const std::list<field_definition>&
    select_fields_by_facet_name(const std::string& n) const;

private:
    const repository& repository_;
};

} } }

#endif
