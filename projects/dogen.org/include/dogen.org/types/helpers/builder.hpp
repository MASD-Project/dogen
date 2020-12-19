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
    void ensure_stack_not_empty() const;
    void ensure_expected_headline_level(const unsigned int expected,
        const unsigned int actual) const;

private:
    void end_current_block();
    void handle_headline(const entities::headline& hl);

public:
    void add_line(const std::string& s);

private:
    entities::headline make_headline(boost::shared_ptr<node> n) const;

public:
    entities::document build();

private:
    std::ostringstream stream_;
    entities::block_type block_type_;
    boost::shared_ptr<node> root_;
    std::stack<boost::shared_ptr<node>> stack_;
};

}

#endif
