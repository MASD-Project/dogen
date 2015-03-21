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
#ifndef DOGEN_DYNAMIC_EXPANSION_TYPES_WORKFLOW_HPP
#define DOGEN_DYNAMIC_EXPANSION_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/dynamic/expansion/types/registrar.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

/**
 * @brief Orchestrator for the expansion workflow.
 */
class workflow {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static expansion::registrar& registrar();

private:
    /**
     * @brief Ensures the workflow is in a valid state.
     */
    void validate() const;

public:
    /**
     * @brief Expands the dynamic fields in the object.
     *
     * @param fds all field definitions.
     * @param m model one wishes to expand.
     */
    sml::model execute(
        const config::cpp_options& options,
        const std::list<schema::field_definition>& fds,
        const sml::model& m) const;

private:
    static std::shared_ptr<expansion::registrar> registrar_;
};

} } }

#endif
