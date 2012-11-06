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
#ifndef DOGEN_STD_MODEL_DOMAIN_CLASS_A_HPP
#define DOGEN_STD_MODEL_DOMAIN_CLASS_A_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/std_model/domain/class_a_versioned_key.hpp"
#include "dogen/std_model/serialization/class_a_fwd_ser.hpp"

namespace dogen {
namespace std_model {

class class_a final {
public:
    class_a() = default;
    class_a(const class_a&) = default;
    class_a(class_a&&) = default;
    ~class_a() = default;

public:
    class_a(
        const std::string& prop0,
        const std::string& prop1,
        const dogen::std_model::class_a_versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_a& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_a& v, unsigned int version);

public:
    std::string prop0() const {
        return prop0_;
    }

    void prop0(const std::string& v) {
        prop0_ = v;
    }

    /*
     * @brief test inclusion duplicates
     */
    /**@{*/
    std::string prop1() const {
        return prop1_;
    }

    void prop1(const std::string& v) {
        prop1_ = v;
    }
    /**@}*/

    dogen::std_model::class_a_versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::std_model::class_a_versioned_key& v) {
        versioned_key_ = v;
    }

public:
    bool operator==(const class_a& rhs) const;
    bool operator!=(const class_a& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_a& other) noexcept;
    class_a& operator=(class_a other);

private:
    std::string prop0_;
    std::string prop1_;
    dogen::std_model::class_a_versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::std_model::class_a& lhs,
    dogen::std_model::class_a& rhs) {
    lhs.swap(rhs);
}

}

#endif
