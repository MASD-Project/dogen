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
#ifndef DOGEN_CPP_TYPES_SETTINGS_WORKFLOW_HPP
#define DOGEN_CPP_TYPES_SETTINGS_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_map>
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/cpp/types/settings/bundle.hpp"
#include "dogen/cpp/types/settings/bundle_factory.hpp"
#include "dogen/cpp/types/settings/registrar.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Orchestrator for the settings workflow.
 */
class workflow {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::settings::registrar& registrar();

public:
    /**
     * @brief Initialises the bundle factory.
     *
     * @param field_definitions_by_formatter_name All fields by formatter name.
     */
    explicit workflow(const std::unordered_map<
            std::string, std::list<dynamic::schema::field_definition>
            >&
        field_definitions_by_formatter_name);

public:
    /**
     * @brief Ensures the workflow is in a valid state.
     */
    void validate() const;

public:
    /**
     * @brief Generates the settings bundle.
     */
    bundle execute(const dynamic::schema::object& o) const;

private:
    static std::shared_ptr<cpp::settings::registrar> registrar_;
    const bundle_factory factory_;
};

} } }

#endif
