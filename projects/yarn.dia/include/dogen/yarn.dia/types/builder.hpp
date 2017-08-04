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
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/yarn.dia/types/context.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Builds a yarn intermediate model from dia processed
 * objects.
 *
 * Expects the objects to have been supplied in dependency order.
 */
class builder {
public:
    builder(const std::string& model_name, const std::string& external_modules,
        const std::unordered_map<std::string, std::list<std::string>>&
        parent_id_to_child_ids);

private:
    /**
     * @brief Returns the module associated with a name.
     *
     * @pre module must exist in repository.
     */
    meta_model::module& module_for_name(const meta_model::name& n);

private:
    boost::shared_ptr<meta_model::module>
    create_module_for_model(const meta_model::name& n) const;

    void setup_model(const std::string& model_name,
        const std::string& external_modules);

    void update_scribble_group(const meta_model::name& n,
        const processed_object& po);

    void update_parentage(const std::string& dia_id, const meta_model::name& n);
    void update_module(const std::string& dia_id,
        boost::shared_ptr<meta_model::module> m);
    void update_documentation(const processed_object& po);

public:
    void add(const processed_object& po);
    meta_model::intermediate_model build();

private:
    const std::unordered_map<std::string, std::list<std::string>>&
    parent_id_to_child_ids_;
    meta_model::intermediate_model model_;
    context context_;
};

} } }

#endif
