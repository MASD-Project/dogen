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
#ifndef DOGEN_YARN_TYPES_GENERALIZATION_EXPANDER_HPP
#define DOGEN_YARN_TYPES_GENERALIZATION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include "dogen/annotations/types/repository.hpp"
#include "dogen/annotations/types/field_definition.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/name.hpp"

namespace dogen {
namespace yarn {

class generalization_expander {
private:
    struct field_definitions {
        annotations::field_definition is_final;
    };

    field_definitions
    make_field_definitions(const annotations::repository& drp) const;

    boost::optional<bool> make_is_final(const field_definitions& fds,
        const annotations::annotation& o) const;

private:
    std::unordered_set<std::string>
    update_and_collect_parent_ids(intermediate_model& im) const;

    void populate_properties_up_the_generalization_tree(
        const field_definitions& fds, const yarn::name& leaf,
        intermediate_model& im, yarn::object& o) const;

    void populate_generalizable_properties(const field_definitions& fds,
        const std::unordered_set<std::string>& parent_ids,
        intermediate_model& im) const;

    void sort_leaves(intermediate_model& im) const;

public:
    void expand(const annotations::repository& rp, intermediate_model& im) const;
};

} }

#endif
