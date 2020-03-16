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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_NAME_TREE_BUILDER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_NAME_TREE_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/meta_model/name.hpp"
#include "dogen.logical/types/meta_model/location.hpp"
#include "dogen.logical/types/meta_model/name_tree.hpp"
#include "dogen.logical/types/helpers/node.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Creates a name tree as directed by the external caller.
 *
 * Starts by producing an intermediate representation using @e nodes,
 * and then transforms that intermediate representation into a name
 * tree. The generation of the intermediate representation is done via
 * a notification mechanism, with the client being responsible for
 * providing the notifications into the builder.
 */
class name_tree_builder {
public:
    name_tree_builder(const name_tree_builder&) = delete;
    ~name_tree_builder() = default;
    name_tree_builder(name_tree_builder&&) = delete;
    name_tree_builder& operator=(const name_tree_builder&) = delete;

public:
    name_tree_builder();

private:
    /**
     * Notify the end of the current node, allowing for any required
     * post-processing.
     */
    void finish_current_node();

public:
    /**
     * @brief Adds the name to the tree.
     */
    void add_name(const std::string& n);

    /**
     * @brief Adds the built-in element name to the tree.
     */
    void add_builtin(const std::string& n);

    /**
     * @brief Notify the start of children.
     */
    void start_children();

    /**
     * @brief Notify the presence of an additional child name.
     */
    void next_child();

    /**
     * @brief Notify the end of children.
     */
    void end_children();

private:
    /**
     * @brief Generate the name tree for the given node
     * representation.
     */
    meta_model::name_tree make_name_tree(const node& n);

public:
    /**
     * @brief Generate the name tree representation for the current
     * node representation.
     */
    meta_model::name_tree build();

private:
    std::list<std::string> names_;
    boost::shared_ptr<node> root_;
    boost::shared_ptr<node> current_;
};

}

#endif
