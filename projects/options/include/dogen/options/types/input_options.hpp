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
#ifndef DOGEN_OPTIONS_TYPES_INPUT_OPTIONS_HPP
#define DOGEN_OPTIONS_TYPES_INPUT_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/options/types/input.hpp"
#include "dogen/options/serialization/input_options_fwd_ser.hpp"

namespace dogen {
namespace options {

/**
 * @brief Options related to the input files.
 */
class input_options final {
public:
    input_options() = default;
    input_options(const input_options&) = default;
    input_options(input_options&&) = default;
    ~input_options() = default;

public:
    explicit input_options(const dogen::options::input& target);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::options::input_options& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::options::input_options& v, unsigned int version);

public:
    /**
     * @brief Path to the Dia diagram that contains the model to generate.
     */
    /**@{*/
    const dogen::options::input& target() const;
    dogen::options::input& target();
    void target(const dogen::options::input& v);
    void target(const dogen::options::input&& v);
    /**@}*/

public:
    bool operator==(const input_options& rhs) const;
    bool operator!=(const input_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(input_options& other) noexcept;
    input_options& operator=(input_options other);

private:
    dogen::options::input target_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::options::input_options& lhs,
    dogen::options::input_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
