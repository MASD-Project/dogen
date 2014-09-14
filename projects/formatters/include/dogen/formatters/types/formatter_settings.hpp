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
#ifndef DOGEN_FORMATTERS_TYPES_FORMATTER_SETTINGS_HPP
#define DOGEN_FORMATTERS_TYPES_FORMATTER_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/formatters/serialization/formatter_settings_fwd_ser.hpp"
#include "dogen/formatters/types/annotation.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Collection of generic settings used by all formatters.
 */
class formatter_settings final {
public:
    formatter_settings(const formatter_settings&) = default;
    formatter_settings(formatter_settings&&) = default;
    ~formatter_settings() = default;

public:
    formatter_settings();

public:
    formatter_settings(
        const bool generate_preamble,
        const dogen::formatters::annotation& annotation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const formatter_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, formatter_settings& v, unsigned int version);

public:
    /**
     * @brief If set to true, the preamble will be generated.
     */
    /**@{*/
    bool generate_preamble() const;
    void generate_preamble(const bool v);
    /**@}*/

    /**
     * @brief Annotation information for formatter.
     */
    /**@{*/
    const dogen::formatters::annotation& annotation() const;
    dogen::formatters::annotation& annotation();
    void annotation(const dogen::formatters::annotation& v);
    void annotation(const dogen::formatters::annotation&& v);
    /**@}*/

public:
    bool operator==(const formatter_settings& rhs) const;
    bool operator!=(const formatter_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formatter_settings& other) noexcept;
    formatter_settings& operator=(formatter_settings other);

private:
    bool generate_preamble_;
    dogen::formatters::annotation annotation_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::formatter_settings& lhs,
    dogen::formatters::formatter_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
