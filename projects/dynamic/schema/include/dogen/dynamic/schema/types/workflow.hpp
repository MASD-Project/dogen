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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_WORKFLOW_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/registrar.hpp"
#include "dogen/dynamic/schema/types/scope_types.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

/**
 * @brief Produces a dynamic object from raw data.
 */
class workflow {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static dynamic::schema::registrar& registrar();

public:
    /**
     * @brief Initialise the dynamic object factory.
     *
     * @param throw_on_missing_field_definition If true, any dynamic
     * extensions for which a field definition does not exist will
     * result in an exception. If false, they will be ignored.
     */
    explicit workflow(
        const bool throw_on_missing_field_definition = true);

private:
    /**
     * @brief Organises field definitions by complete field name.
     */
    std::unordered_map<std::string, field_definition>
    create_field_definitions_by_complete_name() const;

    /**
     * @brief Returns the field definition for the complete
     * name, if one exists.
     *
     * @pre Current scope must be valid according to the field
     * definition's scope.
     */
    boost::optional<field_definition>
    obtain_field_definition(const std::string& complete_name,
        const scope_types current_scope) const;

private:
    /**
     * @brief Aggregate raw data by key.
     */
    std::unordered_map<std::string, std::list<std::string> >
    aggregate_raw_data_activity(
        const std::list<std::pair<std::string, std::string> >&
        raw_data) const;

    /**
     * @brief Converts the raw data into a set of field instances.
     */
    std::unordered_map<std::string, field_instance> create_fields_activity(
        const std::unordered_map<std::string, std::list<std::string> >&
        aggregated_data, const scope_types current_scope) const;

public:
    /**
     * @brief Produce a dynamic object.
     */
    object execute(const scope_types scope,
        const std::list<std::pair<std::string, std::string>>&
        raw_data) const;

private:
    const bool throw_on_missing_field_definition_;
    static std::shared_ptr<dynamic::schema::registrar> registrar_;
    const std::unordered_map<std::string, field_definition>
    field_definitions_by_complete_name_;
};

} } }

#endif
