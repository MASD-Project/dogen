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
#ifndef DOGEN_YARN_TYPES_ASSEMBLER_HPP
#define DOGEN_YARN_TYPES_ASSEMBLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/element.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Responsible for performing the assembly of an intermediate
 * yarn model.
 */
class assembler {
public:
    assembler() = default;
    assembler(const assembler&) = default;
    ~assembler() = default;
    assembler(assembler&&) = default;
    assembler& operator=(const assembler&) = default;

private:
    /**
     * @brief Returns true if the element is generatable, false
     * otherwise.
     */
    bool is_generatable(const element& e) const;

private:
    /**
     * @brief Create the intermediate merged model.
     */
    intermediate_model create_merged_model_activity(
        const std::list<intermediate_model>& models) const;

    /**
     * @brief Index all generalizations.
     */
    void index_generalizations_activity(intermediate_model& merged_model) const;

    /**
     * @brief Injects system types.
     */
    void inject_system_types_activity(intermediate_model& merged_model) const;

    /**
     * @brief Resolve all types.
     */
    void resolve_types_activity(intermediate_model& merged_model) const;

    /**
     * @brief Index all concepts.
     */
    void index_concepts_activity(intermediate_model& merged_model) const;

    /**
     * @brief Index all properties.
     */
    void index_properties_activity(intermediate_model& merged_model) const;

    /**
     * @brief Index all associations.
     */
    void index_associations_activity(intermediate_model& merged_model) const;

    /**
     * @brief Determines if the type has generatable types or not and
     * updates the flag accordingly.
     */
    void update_model_generability_activity(
        intermediate_model& merged_model) const;

private:
    /**
     * @brief Returns true if there are any types that require code
     * generation, false otherwise.
     */
    bool has_generatable_types(const intermediate_model& m) const;

public:
    /**
     * @brief Executes the assembler.
     */
    intermediate_model assemble(const std::list<intermediate_model>& m) const;
};

} }

#endif
