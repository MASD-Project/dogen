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
#ifndef DOGEN_OM_TYPES_LICENCE_HPP
#define DOGEN_OM_TYPES_LICENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/om/serialization/licence_fwd_ser.hpp"

namespace dogen {
namespace om {

/**
 * @brief Licence which the file is released under.
 */
class licence final {
public:
    licence() = default;
    licence(const licence&) = default;
    licence(licence&&) = default;
    ~licence() = default;

public:
    licence(
        const std::list<std::string>& copyright_holders,
        const std::string& licence_text);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const licence& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, licence& v, unsigned int version);

public:
    /**
     * @brief All holders of copyright for the current file and associated period.
     *
     * A Copyright holder is a pair of name and email address.
     */
    /**@{*/
    const std::list<std::string>& copyright_holders() const;
    std::list<std::string>& copyright_holders();
    void copyright_holders(const std::list<std::string>& v);
    void copyright_holders(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Complete legal text for the licence.
     */
    /**@{*/
    const std::string& licence_text() const;
    std::string& licence_text();
    void licence_text(const std::string& v);
    void licence_text(const std::string&& v);
    /**@}*/

public:
    bool operator==(const licence& rhs) const;
    bool operator!=(const licence& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(licence& other) noexcept;
    licence& operator=(licence other);

private:
    std::list<std::string> copyright_holders_;
    std::string licence_text_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::licence& lhs,
    dogen::om::licence& rhs) {
    lhs.swap(rhs);
}

}

#endif
