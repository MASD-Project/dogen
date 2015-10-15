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
#ifndef DOGEN_YARN_TYPES_NESTED_NAME_HPP
#define DOGEN_YARN_TYPES_NESTED_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/nested_name.hpp"
#include "dogen/yarn/serialization/nested_name_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief A composite name.
 */
class nested_name final {
public:
    nested_name(const nested_name&) = default;
    nested_name(nested_name&&) = default;
    ~nested_name() = default;

public:
    nested_name();

public:
    nested_name(
<<<<<<< 24090da86c0fe4a597dfa9c7b5e3ed377e4b57f4:projects/tack/include/dogen/tack/types/nested_name.hpp
        const dogen::tack::name& type,
        const std::list<dogen::tack::nested_name>& children,
        const bool is_pointer);
=======
        const dogen::yarn::name& type,
        const std::list<dogen::yarn::nested_name>& children,
        const bool is_pointer,
        const std::string& unparsed_name);
>>>>>>> rename tack to yarn:projects/yarn/include/dogen/yarn/types/nested_name.hpp

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const nested_name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, nested_name& v, unsigned int version);

public:
    /**
     * @brief Top-level, containing type.
     */
    /**@{*/
    const dogen::yarn::name& type() const;
    dogen::yarn::name& type();
    void type(const dogen::yarn::name& v);
    void type(const dogen::yarn::name&& v);
    /**@}*/

    /**
     * @brief Child types.
     */
    /**@{*/
    const std::list<dogen::yarn::nested_name>& children() const;
    std::list<dogen::yarn::nested_name>& children();
    void children(const std::list<dogen::yarn::nested_name>& v);
    void children(const std::list<dogen::yarn::nested_name>&& v);
    /**@}*/

    /**
     * @brief If true, the top-level type is a pointer. If false, its a stack variable.
     */
    /**@{*/
    bool is_pointer() const;
    void is_pointer(const bool v);
    /**@}*/

public:
    bool operator==(const nested_name& rhs) const;
    bool operator!=(const nested_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(nested_name& other) noexcept;
    nested_name& operator=(nested_name other);

private:
    dogen::yarn::name type_;
    std::list<dogen::yarn::nested_name> children_;
    bool is_pointer_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::nested_name& lhs,
    dogen::yarn::nested_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
