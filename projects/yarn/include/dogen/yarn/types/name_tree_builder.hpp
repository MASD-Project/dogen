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
#ifndef DOGEN_YARN_TYPES_NESTED_QNAME_BUILDER_HPP
#define DOGEN_YARN_TYPES_NESTED_QNAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/location.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/node.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Creates a name tree as directed by the external caller.
 */
class name_tree_builder {
public:
    name_tree_builder() = delete;
    name_tree_builder(const name_tree_builder&) = delete;
    ~name_tree_builder() = default;
    name_tree_builder(name_tree_builder&&) = delete;
    name_tree_builder& operator=(const name_tree_builder&) = delete;

public:
    name_tree_builder(
        const std::unordered_set<std::string>& top_level_modules,
        const location& model_location);

private:
    void finish_current_node();
    name_tree make_name_tree(const node& n);

public:
    /**
     * @brief Adds the element name to the tree.
     */
    void add_name(const std::string& n);

    /**
     * @brief Adds the primitive element name to the tree.
     */
    void add_primitive(const std::string& n);
    void start_children();
    void next_child();
    void end_children();
    name_tree build();

private:
    const std::unordered_set<std::string> top_level_modules_;
    const location model_location_;
    std::list<std::string> names_;
    boost::shared_ptr<node> root_;
    boost::shared_ptr<node> current_;
};

} }

#endif
