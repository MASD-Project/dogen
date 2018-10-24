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
#ifndef MASD_DOGEN_ANNOTATIONS_TYPES_TYPE_REPOSITORY_SELECTOR_HPP
#define MASD_DOGEN_ANNOTATIONS_TYPES_TYPE_REPOSITORY_SELECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include "masd.dogen.annotations/types/type.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"

namespace masd::dogen::annotations {

/**
 * @brief Performs a set of canned queries over a repository.
 */
class type_repository_selector {
public:
    explicit type_repository_selector(const type_repository& rp);

private:
    /**
     * @brief Returns a qualified field name.
     */
    std::string qualify(const std::string& prefix,
        const std::string& field_name) const;

public:
    /**
     * @brief Tries to get the field definition corresponding to the supplied
     * qualified field definition name.
     *
     * @return if one exists, returns it. Returns Null otherwise.
     */
    boost::optional<const type&>
    try_select_type_by_name(const std::string& n) const;

    /**
     * @brief Tries to get the field definition corresponding to the
     * qualified field definition name made up of the prefix and the
     * simple field name.
     *
     * Prefixes are expected to be formatter and facet names.
     *
     * @return if one exists, returns it. Returns Null otherwise.
     */
    boost::optional<const type&>
    try_type_field_by_name(const std::string& prefix,
        const std::string& simple_field_name) const;

public:
    /**
     * @brief Returns the field definition corresponding to the supplied
     * qualified field definition name.
     *
     * @pre name must exist.
     */
    const type& select_type_by_name(const std::string& n) const;

    /**
     * @brief Returns the field definition corresponding to the
     * qualified field definition name made up of the prefix and the
     * simple field name.
     *
     * Prefixes are expected to be formatter and facet names.
     *
     * @pre qualified field name must exist.
     */
    const type& select_type_by_name(
        const std::string& prefix,
        const std::string& simple_field_name) const;

    /**
     * @brief Returns the field definitions corresponding to the
     * supplied formatter name.
     *
     * @pre formatter name must exist.
     */
    const std::list<type>&
    select_type_by_formatter_name(const std::string& n) const;

    /**
     * @brief Returns the field definitions corresponding to the
     * supplied facet name.
     *
     * @pre facet name must exist.
     */
    const std::list<type>&
    select_type_by_facet_name(const std::string& n) const;

    /**
     * @brief Returns the field definitions corresponding to the
     * supplied backend name.
     *
     * @pre backend name must exist.
     */
    const std::list<type>&
    select_type_by_backend_name(const std::string& n) const;

private:
    const type_repository& repository_;
};

}

#endif
