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
#ifndef DOGEN_SML_TYPES_WORKFLOW_HPP
#define DOGEN_SML_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/merger.hpp"

namespace dogen {
namespace sml {

class workflow {
public:
    workflow(const workflow&) = default;
    ~workflow() = default;
    workflow(workflow&&) = default;
    workflow& operator=(const workflow&) = default;

public:
    workflow();
    explicit workflow(const bool add_system_models);

private:
    void add_system_models();
    void add_references(const std::list<model>& references);
    void add_target(const model& target);

    /**
     * @brief Returns true if there are any types that require code
     * generation, false otherwise.
     */
    bool has_generatable_types(const sml::model& m) const;

public:
    std::pair<bool, model>
    execute(const model& target, const std::list<model>& references);

private:
    const bool add_system_models_;
    merger merger_;
};

} }

#endif
