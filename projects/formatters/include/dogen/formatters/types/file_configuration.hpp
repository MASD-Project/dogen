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
#ifndef DOGEN_FORMATTERS_TYPES_FILE_CONFIGURATION_HPP
#define DOGEN_FORMATTERS_TYPES_FILE_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/formatters/types/decoration.hpp"
#include "dogen/formatters/serialization/file_configuration_fwd_ser.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Configuration pertaining to a file and common to all formatters.
 */
class file_configuration final {
public:
    file_configuration(const file_configuration&) = default;
    file_configuration(file_configuration&&) = default;
    ~file_configuration() = default;

public:
    file_configuration();

public:
    file_configuration(
        const bool generate_preamble,
        const dogen::formatters::decoration& decoration);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatters::file_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatters::file_configuration& v, unsigned int version);

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
    bool operator==(const file_configuration& rhs) const;
    bool operator!=(const file_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file_configuration& other) noexcept;
    file_configuration& operator=(file_configuration other);

private:
    bool generate_preamble_;
    dogen::formatters::decoration decoration_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::file_configuration& lhs,
    dogen::formatters::file_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
