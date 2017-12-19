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
#ifndef DOGEN_FORMATTING_TYPES_LICENCE_HPP
#define DOGEN_FORMATTING_TYPES_LICENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.formatting/serialization/licence_fwd_ser.hpp"

namespace dogen {
namespace formatting {

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
        const std::list<std::string>& copyright_notices,
        const std::string& text);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatting::licence& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatting::licence& v, unsigned int version);

public:
    /**
     * @brief All copyright notices for the current file.
     */
    /**@{*/
    const std::list<std::string>& copyright_notices() const;
    std::list<std::string>& copyright_notices();
    void copyright_notices(const std::list<std::string>& v);
    void copyright_notices(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Complete legal text for the licence.
     */
    /**@{*/
    const std::string& text() const;
    std::string& text();
    void text(const std::string& v);
    void text(const std::string&& v);
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
    std::list<std::string> copyright_notices_;
    std::string text_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatting::licence& lhs,
    dogen::formatting::licence& rhs) {
    lhs.swap(rhs);
}

}

#endif
