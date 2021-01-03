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
#ifndef DOGEN_ORG_TYPES_HELPERS_BUILDER_HPP
#define DOGEN_ORG_TYPES_HELPERS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <stack>
#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include "dogen.org/types/entities/document.hpp"
#include "dogen.org/types/entities/headline.hpp"
#include "dogen.org/types/helpers/node_fwd.hpp"

namespace dogen::org::helpers {

/**
 * @brief Builds org documents.
 */
class builder final {
public:
    builder();

private:
    /**
     * @brief Throws if the stack is empty.
     */
    void ensure_stack_not_empty() const;

private:
    /**
     * @brief Returns the node at the top of the stack.
     *
     * @pre stack must not be empty.
     */
    node& top() const;

    /**
     * @brief Flushes all the content accumulated into a text block.
     */
    void end_text_block();

    /**
     * @brief Processes the headline, adding it to the current node.
     */
    void handle_headline(const entities::headline& hl);

private:
    /**
     * @brief Creates an headline structure from the supplied node, by
     * recursing it.
     */
    entities::headline make_headline(boost::shared_ptr<node> n) const;

public:
    /**
     * @brief Adds line to the builder.
     */
    void add_line(const std::string& s);

    /**
     * @brief Adds a final new line to the content.
     */
    void add_final_new_line();

public:
    /**
     * @brief Builds an org mode document from the data supplied so far.
     */
    entities::document build();

private:
    std::ostringstream stream_;
    boost::shared_ptr<node> root_;
    std::stack<boost::shared_ptr<node>> stack_;
    bool in_drawer_;
    bool in_greater_block_;
    bool is_first_line_;
    unsigned int line_number_;
};

}

#endif
