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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_DECORATION_PROFILE_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_DECORATION_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/formattables/decoration_profile_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class decoration_profile final {
public:
    decoration_profile() = default;
    decoration_profile(const decoration_profile&) = default;
    decoration_profile(decoration_profile&&) = default;
    ~decoration_profile() = default;

public:
    decoration_profile(
        const std::string& licence_name,
        const std::list<std::string>& copyright_notices,
        const std::string& modeline_group_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::decoration_profile& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::decoration_profile& v, unsigned int version);

public:
    const std::string& licence_name() const;
    std::string& licence_name();
    void licence_name(const std::string& v);
    void licence_name(const std::string&& v);

    const std::list<std::string>& copyright_notices() const;
    std::list<std::string>& copyright_notices();
    void copyright_notices(const std::list<std::string>& v);
    void copyright_notices(const std::list<std::string>&& v);

    const std::string& modeline_group_name() const;
    std::string& modeline_group_name();
    void modeline_group_name(const std::string& v);
    void modeline_group_name(const std::string&& v);

public:
    bool operator==(const decoration_profile& rhs) const;
    bool operator!=(const decoration_profile& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decoration_profile& other) noexcept;
    decoration_profile& operator=(decoration_profile other);

private:
    std::string licence_name_;
    std::list<std::string> copyright_notices_;
    std::string modeline_group_name_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::decoration_profile& lhs,
    dogen::quilt::cpp::formattables::decoration_profile& rhs) {
    lhs.swap(rhs);
}

}

#endif
