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
#ifndef DOGEN_DYNAMIC_TYPES_WORKFLOW_HPP
#define DOGEN_DYNAMIC_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/registrar.hpp"
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/dynamic/types/field_definition.hpp"

namespace dogen {
namespace dynamic {

/**
 * @brief Produces a dynamic object from raw data.
 */
class workflow {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static dynamic::registrar& registrar();

public:
    workflow();

private:
    /**
     * @brief Organises field definitions by complete field name.
     */
    std::unordered_map<std::string, field_definition>
    obtain_field_definitions_by_complete_name_activity() const;

    /**
     * @brief Aggregate raw data by key.
     */
    std::list<std::pair<std::string, std::list<std::string> > >
    aggregate_activity(
        const std::list<std::pair<std::string, std::string>>& raw_data) const;

    /**
     * @brief Converts the raw data into a set of fields.
     */
    std::list<field> build_fields_activity(
        const std::list<std::pair<std::string, std::list<std::string> > >&
        raw_data) const;

public:
    /**
     * @brief Produce a dynamic object.
     */
    object execute(const scope_types scope,
        const std::list<std::pair<std::string, std::string>>& raw_data) const;

private:
    static std::shared_ptr<dynamic::registrar> registrar_;
    const std::unordered_map<std::string, field_definition>
    field_definitions_by_complete_name_;
};

} }

#endif
