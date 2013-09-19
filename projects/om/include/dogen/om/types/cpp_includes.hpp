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
#ifndef DOGEN_OM_TYPES_CPP_INCLUDES_HPP
#define DOGEN_OM_TYPES_CPP_INCLUDES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/om/serialization/cpp_includes_fwd_ser.hpp"

namespace dogen {
namespace om {

/**
 * @brief User and system include files.
 */
class cpp_includes final {
public:
    cpp_includes() = default;
    cpp_includes(const cpp_includes&) = default;
    cpp_includes(cpp_includes&&) = default;
    ~cpp_includes() = default;

public:
    cpp_includes(
        const std::list<std::string>& system,
        const std::list<std::string>& user);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_includes& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_includes& v, unsigned int version);

public:
    /**
     * @brief System includes.
     *
     * These are expected to use angle brackets and be on the system path.
     */
    /**@{*/
    const std::list<std::string>& system() const;
    std::list<std::string>& system();
    void system(const std::list<std::string>& v);
    void system(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief User includes.
     *
     * These are expected to use quotes and be on the user path.
     */
    /**@{*/
    const std::list<std::string>& user() const;
    std::list<std::string>& user();
    void user(const std::list<std::string>& v);
    void user(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const cpp_includes& rhs) const;
    bool operator!=(const cpp_includes& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cpp_includes& other) noexcept;
    cpp_includes& operator=(cpp_includes other);

private:
    std::list<std::string> system_;
    std::list<std::string> user_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_includes& lhs,
    dogen::om::cpp_includes& rhs) {
    lhs.swap(rhs);
}

}

#endif
