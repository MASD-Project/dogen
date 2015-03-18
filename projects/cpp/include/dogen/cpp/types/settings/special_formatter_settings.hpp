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
#ifndef DOGEN_CPP_TYPES_SETTINGS_SPECIAL_FORMATTER_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_SPECIAL_FORMATTER_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/cpp/serialization/settings/special_formatter_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class special_formatter_settings {
public:
    special_formatter_settings() = default;
    special_formatter_settings(const special_formatter_settings&) = default;
    special_formatter_settings(special_formatter_settings&&) = default;
    special_formatter_settings& operator=(const special_formatter_settings&) = default;

    virtual ~special_formatter_settings() noexcept = 0;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const special_formatter_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, special_formatter_settings& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

protected:
    bool compare(const special_formatter_settings& rhs) const;
public:
    virtual bool equals(const special_formatter_settings& other) const = 0;

protected:
    void swap(special_formatter_settings& other) noexcept;

};

inline special_formatter_settings::~special_formatter_settings() noexcept { }

inline bool operator==(const special_formatter_settings& lhs, const special_formatter_settings& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif
