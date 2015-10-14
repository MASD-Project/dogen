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
#ifndef DOGEN_CPP_TYPES_SETTINGS_INCLUSION_DIRECTIVE_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_INCLUSION_DIRECTIVE_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/cpp/serialization/settings/inclusion_directive_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class inclusion_directive_settings final {
public:
    inclusion_directive_settings(const inclusion_directive_settings&) = default;
    ~inclusion_directive_settings() = default;

public:
    inclusion_directive_settings();

public:
    inclusion_directive_settings(inclusion_directive_settings&& rhs);

public:
    inclusion_directive_settings(
        const bool inclusion_required,
        const boost::optional<std::string>& inclusion_directive);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const inclusion_directive_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, inclusion_directive_settings& v, unsigned int version);

public:
    bool inclusion_required() const;
    void inclusion_required(const bool v);

    const boost::optional<std::string>& inclusion_directive() const;
    boost::optional<std::string>& inclusion_directive();
    void inclusion_directive(const boost::optional<std::string>& v);
    void inclusion_directive(const boost::optional<std::string>&& v);

public:
    bool operator==(const inclusion_directive_settings& rhs) const;
    bool operator!=(const inclusion_directive_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion_directive_settings& other) noexcept;
    inclusion_directive_settings& operator=(inclusion_directive_settings other);

private:
    bool inclusion_required_;
    boost::optional<std::string> inclusion_directive_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::inclusion_directive_settings& lhs,
    dogen::cpp::settings::inclusion_directive_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
