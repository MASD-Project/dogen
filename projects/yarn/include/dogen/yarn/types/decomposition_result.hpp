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
#ifndef DOGEN_YARN_TYPES_DECOMPOSITION_RESULT_HPP
#define DOGEN_YARN_TYPES_DECOMPOSITION_RESULT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/serialization/decomposition_result_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class decomposition_result final {
public:
    decomposition_result() = default;
    decomposition_result(const decomposition_result&) = default;
    decomposition_result(decomposition_result&&) = default;
    ~decomposition_result() = default;

public:
    decomposition_result(
        const std::list<dogen::yarn::name>& names,
        const std::list<dogen::yarn::name_tree>& name_trees);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::decomposition_result& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::decomposition_result& v, unsigned int version);

public:
    const std::list<dogen::yarn::name>& names() const;
    std::list<dogen::yarn::name>& names();
    void names(const std::list<dogen::yarn::name>& v);
    void names(const std::list<dogen::yarn::name>&& v);

    const std::list<dogen::yarn::name_tree>& name_trees() const;
    std::list<dogen::yarn::name_tree>& name_trees();
    void name_trees(const std::list<dogen::yarn::name_tree>& v);
    void name_trees(const std::list<dogen::yarn::name_tree>&& v);

public:
    bool operator==(const decomposition_result& rhs) const;
    bool operator!=(const decomposition_result& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decomposition_result& other) noexcept;
    decomposition_result& operator=(decomposition_result other);

private:
    std::list<dogen::yarn::name> names_;
    std::list<dogen::yarn::name_tree> name_trees_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::decomposition_result& lhs,
    dogen::yarn::decomposition_result& rhs) {
    lhs.swap(rhs);
}

}

#endif
