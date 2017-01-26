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
#ifndef DOGEN_YARN_TYPES_DECOMPOSER_HPP
#define DOGEN_YARN_TYPES_DECOMPOSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/yarn/types/decomposition_result.hpp"

namespace dogen {
namespace yarn {

class decomposer final : public element_visitor {
private:
    void add_name(const std::string& owner, const name& n);
    void add_name_tree(const std::string& owner, const name_tree& nt);
    void add_names(const std::string& owner, const std::list<name>& names);
    void process_attributes(const std::string& owner,
        const std::list<attribute>& attrs);
    void process_element(const element& e);

public:
    using element_visitor::visit;
    void visit(const yarn::concept& c);
    void visit(const yarn::module& m);
    void visit(const yarn::enumeration& e);
    void visit(const yarn::exception& e);
    void visit(const yarn::object& o);
    void visit(const yarn::builtin& b);

public:
    const decomposition_result& result() const;

private:
    decomposition_result result_;
};

} }

#endif
