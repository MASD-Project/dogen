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
#ifndef DOGEN_FORMATTERS_TYPES_GENERAL_SETTINGS_HPP
#define DOGEN_FORMATTERS_TYPES_GENERAL_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/formatters/types/annotation.hpp"
#include "dogen/formatters/serialization/general_settings_fwd_ser.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Collection of generic settings used by all formatters.
 */
class general_settings final {
public:
    general_settings(const general_settings&) = default;
    general_settings(general_settings&&) = default;
    ~general_settings() = default;

public:
    general_settings();

public:
    general_settings(
        const bool generate_preamble,
        const dogen::formatters::annotation& annotation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const general_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, general_settings& v, unsigned int version);

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
    bool operator==(const general_settings& rhs) const;
    bool operator!=(const general_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(general_settings& other) noexcept;
    general_settings& operator=(general_settings other);

private:
    bool generate_preamble_;
    dogen::formatters::annotation annotation_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::general_settings& lhs,
    dogen::formatters::general_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
