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
#ifndef DOGEN_FORMATTERS_TYPES_FILE_PROPERTIES_HPP
#define DOGEN_FORMATTERS_TYPES_FILE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/formatters/types/decoration.hpp"
#include "dogen/formatters/serialization/file_properties_fwd_ser.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Properties pertaining to a file and common to all formatters.
 */
class file_properties final {
public:
    file_properties(const file_properties&) = default;
    file_properties(file_properties&&) = default;
    ~file_properties() = default;

public:
    file_properties();

public:
    file_properties(
        const bool generate_preamble,
        const dogen::formatters::decoration& decoration);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatters::file_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatters::file_properties& v, unsigned int version);

public:
    /**
     * @brief If set to true, the preamble will be generated.
     */
    /**@{*/
    bool generate_preamble() const;
    void generate_preamble(const bool v);
    /**@}*/

    /**
     * @brief Decoration information for formatter.
     */
    /**@{*/
    const dogen::formatters::decoration& decoration() const;
    dogen::formatters::decoration& decoration();
    void decoration(const dogen::formatters::decoration& v);
    void decoration(const dogen::formatters::decoration&& v);
    /**@}*/

public:
    bool operator==(const file_properties& rhs) const;
    bool operator!=(const file_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file_properties& other) noexcept;
    file_properties& operator=(file_properties other);

private:
    bool generate_preamble_;
    dogen::formatters::decoration decoration_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::file_properties& lhs,
    dogen::formatters::file_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
