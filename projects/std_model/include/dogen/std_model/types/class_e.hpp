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
#ifndef DOGEN_STD_MODEL_TYPES_CLASS_E_HPP
#define DOGEN_STD_MODEL_TYPES_CLASS_E_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <deque>
#include <string>
#include "dogen/std_model/serialization/class_e_fwd_ser.hpp"
#include "dogen/std_model/types/class_a.hpp"
#include "dogen/std_model/types/pkg1/class_c.hpp"

namespace dogen {
namespace std_model {

class class_e final {
public:
    class_e() = default;
    class_e(const class_e&) = default;
    class_e(class_e&&) = default;
    ~class_e() = default;

public:
    class_e(
        const std::deque<std::string>& prop_0,
        const std::deque<dogen::std_model::class_a>& prop_1,
        const std::deque<dogen::std_model::pkg1::class_c>& prop_2,
        const std::deque<unsigned int>& prop_3,
        const std::deque<dogen::std_model::class_a>& prop_4,
        const std::deque<std::deque<unsigned int> >& prop_5);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_e& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_e& v, unsigned int version);

public:
    std::deque<std::string> prop_0() const {
        return prop_0_;
    }

    void prop_0(const std::deque<std::string>& v) {
        prop_0_ = v;
    }

    std::deque<dogen::std_model::class_a> prop_1() const {
        return prop_1_;
    }

    void prop_1(const std::deque<dogen::std_model::class_a>& v) {
        prop_1_ = v;
    }

    std::deque<dogen::std_model::pkg1::class_c> prop_2() const {
        return prop_2_;
    }

    void prop_2(const std::deque<dogen::std_model::pkg1::class_c>& v) {
        prop_2_ = v;
    }

    std::deque<unsigned int> prop_3() const {
        return prop_3_;
    }

    void prop_3(const std::deque<unsigned int>& v) {
        prop_3_ = v;
    }

    std::deque<dogen::std_model::class_a> prop_4() const {
        return prop_4_;
    }

    void prop_4(const std::deque<dogen::std_model::class_a>& v) {
        prop_4_ = v;
    }

    std::deque<std::deque<unsigned int> > prop_5() const {
        return prop_5_;
    }

    void prop_5(const std::deque<std::deque<unsigned int> >& v) {
        prop_5_ = v;
    }

public:
    bool operator==(const class_e& rhs) const;
    bool operator!=(const class_e& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_e& other) noexcept;
    class_e& operator=(class_e other);

private:
    std::deque<std::string> prop_0_;
    std::deque<dogen::std_model::class_a> prop_1_;
    std::deque<dogen::std_model::pkg1::class_c> prop_2_;
    std::deque<unsigned int> prop_3_;
    std::deque<dogen::std_model::class_a> prop_4_;
    std::deque<std::deque<unsigned int> > prop_5_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::std_model::class_e& lhs,
    dogen::std_model::class_e& rhs) {
    lhs.swap(rhs);
}

}

#endif
