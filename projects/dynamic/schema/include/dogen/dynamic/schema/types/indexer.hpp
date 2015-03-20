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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_INDEXER_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_INDEXER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/dynamic/schema/types/field_definition.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

/**
 * @brief Indexes field definitions.
 */
class indexer {
public:
    /**
     * @brief Returns field definitions indexed by facet name.
     *
     * @pre Empty unless index has been run.
     */
    const std::unordered_map<std::string, std::list<field_definition> >&
    field_definitions_by_facet_name() const;

    /**
     * @brief Returns field definitions indexed by formatter name.
     *
     * @pre Empty unless index has been run.
     */
    const std::unordered_map<std::string, std::list<field_definition> >&
    field_definitions_by_formatter_name() const;

public:
    /**
     * @brief Setup all indices.
     */
    void index(const std::list<field_definition>& fds);

private:
    std::unordered_map<std::string, std::list<field_definition> >
    field_definitions_by_facet_name_;
    std::unordered_map<std::string, std::list<field_definition> >
    field_definitions_by_formatter_name_;

};

} } }

#endif
