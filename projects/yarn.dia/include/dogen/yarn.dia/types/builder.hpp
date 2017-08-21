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
#ifndef DOGEN_YARN_DIA_TYPES_BUILDER_HPP
#define DOGEN_YARN_DIA_TYPES_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/scribble.hpp"
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/exomodel.hpp"
#include "dogen/yarn.dia/types/context.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Builds a yarn exogenous model from dia processed objects.
 *
 * Expects the objects to have been supplied in dependency order.
 */
class builder {
public:
    explicit builder(
        const std::unordered_map<std::string, std::list<std::string>>&
        parent_id_to_child_ids);

private:
    /**
     * @brief Adds the supplied module into the context, slotting it
     * against its dia ID.
     */
    void add_module_to_context(const std::string& dia_id,
        boost::shared_ptr<meta_model::module> m);

    /**
     * @brief Updates the parenting information for the given object
     * identified by the dia ID.
     */
    void update_parentage(const std::string& dia_id, const meta_model::name& n);

    /**
     * @brief Updates the module documentation and scribbles, given
     * the processed object.
     *
     * @pre po must be a UML note.
     */
    void update_module(const processed_object& po);

public:
    void add(const processed_object& po);
    meta_model::exomodel build();

private:
    const std::unordered_map<std::string, std::list<std::string>>&
    parent_id_to_child_ids_;
    meta_model::exomodel model_;
    context context_;
};

} } }

#endif
