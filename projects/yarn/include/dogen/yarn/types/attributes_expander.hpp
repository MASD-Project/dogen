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
#ifndef DOGEN_YARN_TYPES_ATTRIBUTES_EXPANDER_HPP
#define DOGEN_YARN_TYPES_ATTRIBUTES_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/name_tree_parser.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Performs the expansion of all attributes in the supplied
 * model.
 */
class attributes_expander {
private:
    /**
     * @brief Returns true if the supplied name tree would result in a
     * circular reference back to @e owner.
     */
    bool is_circular_dependency(const name& owner, const name_tree& nt) const;

    /**
     * @brief Update all attributes in the supplied element.
     */
    template<typename NameableAndStateful>
    void update_attributes(const name_tree_parser& ntp,
        NameableAndStateful& nas) const {
        for (auto& p : nas.local_attributes()) {
            auto nt(ntp.parse(p.unparsed_type()));
            nt.is_circular_dependency(is_circular_dependency(nas.name(), nt));
            p.parsed_type(nt);
        }
    }

private:
    /**
     * @brief Returns all of the top-level modules in the supplied
     * model.
     */
    std::unordered_set<std::string>
    obtain_top_level_module_names(const intermediate_model& m) const;

public:
    /**
     * Execute the property expansion against the model.
     */
    void expand(intermediate_model& m) const;
};

} }

#endif
