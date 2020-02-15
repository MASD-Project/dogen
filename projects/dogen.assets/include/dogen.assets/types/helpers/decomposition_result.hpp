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
#ifndef DOGEN_ASSETS_TYPES_HELPERS_DECOMPOSITION_RESULT_HPP
#define DOGEN_ASSETS_TYPES_HELPERS_DECOMPOSITION_RESULT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/name_tree.hpp"

namespace dogen::assets::helpers {

class decomposition_result final {
public:
    decomposition_result() = default;
    decomposition_result(const decomposition_result&) = default;
    decomposition_result(decomposition_result&&) = default;
    ~decomposition_result() = default;

public:
    decomposition_result(
        const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& names,
        const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& meta_names,
        const std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >& name_trees);

public:
    const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& names() const;
    std::list<std::pair<std::string, dogen::assets::meta_model::name> >& names();
    void names(const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& v);
    void names(const std::list<std::pair<std::string, dogen::assets::meta_model::name> >&& v);

    const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& meta_names() const;
    std::list<std::pair<std::string, dogen::assets::meta_model::name> >& meta_names();
    void meta_names(const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& v);
    void meta_names(const std::list<std::pair<std::string, dogen::assets::meta_model::name> >&& v);

    const std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >& name_trees() const;
    std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >& name_trees();
    void name_trees(const std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >& v);
    void name_trees(const std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >&& v);

public:
    bool operator==(const decomposition_result& rhs) const;
    bool operator!=(const decomposition_result& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decomposition_result& other) noexcept;
    decomposition_result& operator=(decomposition_result other);

private:
    std::list<std::pair<std::string, dogen::assets::meta_model::name> > names_;
    std::list<std::pair<std::string, dogen::assets::meta_model::name> > meta_names_;
    std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> > name_trees_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::helpers::decomposition_result& lhs,
    dogen::assets::helpers::decomposition_result& rhs) {
    lhs.swap(rhs);
}

}

#endif
