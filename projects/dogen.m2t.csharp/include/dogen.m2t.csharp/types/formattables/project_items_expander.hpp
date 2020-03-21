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
#ifndef DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_PROJECT_ITEMS_EXPANDER_HPP
#define DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_PROJECT_ITEMS_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include "dogen.m2t.csharp/types/formattables/model.hpp"

namespace dogen::m2t::csharp::formattables {

class project_items_expander final {
private:
    static std::unordered_set<std::string> meta_names_for_project_items();
    bool is_project_item(const std::string& mn) const;

public:
    void expand(model& fm) const;
};

}

#endif
