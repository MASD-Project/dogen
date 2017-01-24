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
#ifndef DOGEN_YARN_TYPES_MAPPING_SET_REPOSITORY_FACTORY_HPP
#define DOGEN_YARN_TYPES_MAPPING_SET_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/mapping.hpp"
#include "dogen/yarn/types/mapping_set.hpp"
#include "dogen/yarn/types/mapping_value.hpp"
#include "dogen/yarn/types/mapping_set_repository.hpp"

namespace dogen {
namespace yarn {

class mapping_set_repository_factory final {
private:
    void insert(const std::string& upsilon_id, const std::string& lam_id,
        std::unordered_map<std::string, std::string>& map) const;

    void insert(const std::string& lam_id, const name& n,
        const languages l, std::unordered_map<languages,
        std::unordered_map<std::string, name>>& map) const;

    void populate_upsilon_data(const std::string& lam_id,
        const mapping& mapping, const mapping_value& upsilon_mv,
        mapping_set& ms) const;

    void populate_mapping_set(const std::list<mapping>& mappings,
        mapping_set& ms) const;

public:
    mapping_set_repository make(const std::unordered_map<std::string,
        std::list<mapping>>& mappings_by_set_name) const;
};

} }

#endif
