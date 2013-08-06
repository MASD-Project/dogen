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
#ifndef DOGEN_SML_TO_CPP_TYPES_INCLUSION_LISTS_HPP
#define DOGEN_SML_TO_CPP_TYPES_INCLUSION_LISTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/sml_to_cpp/serialization/inclusion_lists_fwd_ser.hpp"

namespace dogen {
namespace sml_to_cpp {

/**
 * @brief Result of a request for includes.
 */
class inclusion_lists final {
public:
    inclusion_lists() = default;
    inclusion_lists(const inclusion_lists&) = default;
    inclusion_lists(inclusion_lists&&) = default;
    ~inclusion_lists() = default;

public:
    inclusion_lists(
        const std::list<std::string>& system,
        const std::list<std::string>& user);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const inclusion_lists& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, inclusion_lists& v, unsigned int version);

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
    bool operator==(const inclusion_lists& rhs) const;
    bool operator!=(const inclusion_lists& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion_lists& other) noexcept;
    inclusion_lists& operator=(inclusion_lists other);

private:
    std::list<std::string> system_;
    std::list<std::string> user_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml_to_cpp::inclusion_lists& lhs,
    dogen::sml_to_cpp::inclusion_lists& rhs) {
    lhs.swap(rhs);
}

}

#endif
