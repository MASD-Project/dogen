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
#include "dogen/quilt.cpp/types/formattables/transformer.hpp"
#include "dogen/quilt.cpp/types/formattables/post_reduction_workflow.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::forward_list<formattable>
post_reduction_workflow::transform(
    const std::unordered_map<std::string, formattable>& formattables) const {
    transformer t;
    return t.transform(formattables);
}

std::forward_list<formattable> post_reduction_workflow::
execute(const formatters::container& /*fc*/,
    const std::unordered_map<std::string, formattable>& formattables) const {
    const auto r(transform(formattables));
    return r;
}

} } } }
