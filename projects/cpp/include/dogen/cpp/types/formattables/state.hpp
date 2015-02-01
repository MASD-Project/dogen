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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_STATE_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_STATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include "dogen/cpp/serialization/formattables/state_fwd_ser.hpp"
#include "dogen/cpp/types/formattables/property_info.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents a C++ class.
 */
class state final {
public:
    state(const state&) = default;
    state(state&&) = default;
    ~state() = default;

public:
    state();

public:
    state(
        const std::list<dogen::cpp::formattables::property_info>& personal_properties,
        const std::list<dogen::cpp::formattables::property_info>& all_properties,
        const bool has_primitive_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const state& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, state& v, unsigned int version);

public:
    /**
     * @brief Properties of the class itself (e.g. excludes inherited
     * properties).
     */
    /**@{*/
    const std::list<dogen::cpp::formattables::property_info>& personal_properties() const;
    std::list<dogen::cpp::formattables::property_info>& personal_properties();
    void personal_properties(const std::list<dogen::cpp::formattables::property_info>& v);
    void personal_properties(const std::list<dogen::cpp::formattables::property_info>&& v);
    /**@}*/

    /**
     * @brief All properties of the class including inherited.
     */
    /**@{*/
    const std::list<dogen::cpp::formattables::property_info>& all_properties() const;
    std::list<dogen::cpp::formattables::property_info>& all_properties();
    void all_properties(const std::list<dogen::cpp::formattables::property_info>& v);
    void all_properties(const std::list<dogen::cpp::formattables::property_info>&& v);
    /**@}*/

    /**
     * @brief True if the class has at least one property which is a
     * primitive, false otherwise.
     */
    /**@{*/
    bool has_primitive_properties() const;
    void has_primitive_properties(const bool v);
    /**@}*/

public:
    bool operator==(const state& rhs) const;
    bool operator!=(const state& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(state& other) noexcept;
    state& operator=(state other);

private:
    std::list<dogen::cpp::formattables::property_info> personal_properties_;
    std::list<dogen::cpp::formattables::property_info> all_properties_;
    bool has_primitive_properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::state& lhs,
    dogen::cpp::formattables::state& rhs) {
    lhs.swap(rhs);
}

}

#endif
