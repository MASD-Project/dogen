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
#ifndef DOGEN_OM_TYPES_DOXYGEN_COMMAND_HPP
#define DOGEN_OM_TYPES_DOXYGEN_COMMAND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/om/serialization/doxygen_command_fwd_ser.hpp"
#include "dogen/om/types/doxygen_command_types.hpp"

namespace dogen {
namespace om {

/**
 * @brief Models a doxygen command.
 */
class doxygen_command final {
public:
    doxygen_command(const doxygen_command&) = default;
    doxygen_command(doxygen_command&&) = default;
    ~doxygen_command() = default;

public:
    doxygen_command();

public:
    doxygen_command(
        const dogen::om::doxygen_command_types& type,
        const std::string& argument);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const doxygen_command& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, doxygen_command& v, unsigned int version);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    dogen::om::doxygen_command_types type() const;
    void type(const dogen::om::doxygen_command_types& v);
    /**@}*/

    const std::string& argument() const;
    std::string& argument();
    void argument(const std::string& v);
    void argument(const std::string&& v);

public:
    bool operator==(const doxygen_command& rhs) const;
    bool operator!=(const doxygen_command& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(doxygen_command& other) noexcept;
    doxygen_command& operator=(doxygen_command other);

private:
    dogen::om::doxygen_command_types type_;
    std::string argument_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::doxygen_command& lhs,
    dogen::om::doxygen_command& rhs) {
    lhs.swap(rhs);
}

}

#endif
