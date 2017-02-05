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
#ifndef DOGEN_YARN_TYPES_SECOND_STAGE_VALIDATOR_HPP
#define DOGEN_YARN_TYPES_SECOND_STAGE_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_set>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/decomposition_result.hpp"

namespace dogen {
namespace yarn {

class second_stage_validator final {
private:
    bool allow_spaces_in_built_in_types(const languages l) const;
    decomposition_result decompose_model(const model& m) const;

private:
    void validate_string(const std::string& s,
        bool check_not_builtin = true) const;
    void validate_strings(const std::list<std::string>& strings) const;
    void validate_name(const name& n,
        const bool allow_spaces_in_built_in_types) const;
    void validate_names(const std::list<std::pair<std::string, name>>& names,
        const languages l) const;

    void validate_name_tree(const std::unordered_set<std::string>&
        abstract_elements, const languages l, const name_tree& nt,
        const bool inherit_opaqueness_from_parent = false) const;
    void validate_name_trees(
        const std::unordered_set<std::string>& abstract_elements,
        const languages l,
        const std::list<std::pair<std::string, name_tree>>& nts) const;

public:
    void validate(const model& m) const;
};

} }

#endif
