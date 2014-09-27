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
#ifndef DOGEN_FRONTEND_TYPES_SOURCE_SETTINGS_HPP
#define DOGEN_FRONTEND_TYPES_SOURCE_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/frontend/serialization/source_settings_fwd_ser.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Settings that control the reading abilities of the source.
 */
class source_settings final {
public:
    source_settings(const source_settings&) = default;
    source_settings(source_settings&&) = default;
    ~source_settings() = default;

public:
    source_settings();

public:
    source_settings(
        const bool save_original_input,
        const std::string& original_input_extension);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const source_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, source_settings& v, unsigned int version);

public:
    /**
     * @brief If true, the workflow will save the source's original input after parsing.
     */
    /**@{*/
    bool save_original_input() const;
    void save_original_input(const bool v);
    /**@}*/

    /**
     * @brief Extension to use for the source's original input.
     */
    /**@{*/
    const std::string& original_input_extension() const;
    std::string& original_input_extension();
    void original_input_extension(const std::string& v);
    void original_input_extension(const std::string&& v);
    /**@}*/

public:
    bool operator==(const source_settings& rhs) const;
    bool operator!=(const source_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(source_settings& other) noexcept;
    source_settings& operator=(source_settings other);

private:
    bool save_original_input_;
    std::string original_input_extension_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::frontend::source_settings& lhs,
    dogen::frontend::source_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
