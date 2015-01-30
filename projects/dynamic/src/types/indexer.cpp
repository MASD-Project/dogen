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
#include "dogen/dynamic/types/indexer.hpp"

namespace dogen {
namespace dynamic {

const std::unordered_map<std::string, std::forward_list<field_definition> >&
indexer::field_definitions_by_facet_name() const {
    return field_definitions_by_facet_name_;
}

const std::unordered_map<std::string, std::forward_list<field_definition> >&
indexer::field_definitions_by_formatter_name() const {
    return field_definitions_by_formatter_name_;
}

void indexer::index(const std::forward_list<field_definition>& fds) {
    for (const auto& fd : fds) {
        const auto fct(fd.ownership_hierarchy().facet_name());
        if (!fct.empty())
            field_definitions_by_facet_name_[fct].push_front(fd);

        const auto fmt(fd.ownership_hierarchy().formatter_name());
        if (!fmt.empty())
            field_definitions_by_formatter_name_[fmt].push_front(fd);
    }
}

} }
