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
#ifndef DOGEN_STD_MODEL_DOMAIN_CLASS_D_HPP
#define DOGEN_STD_MODEL_DOMAIN_CLASS_D_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/std_model/domain/class_a.hpp"
#include "dogen/std_model/domain/pkg1/class_c.hpp"
#include "dogen/std_model/serialization/class_d_fwd_ser.hpp"

namespace dogen {
namespace std_model {

class class_d final {
public:
    class_d() = default;
    class_d(const class_d&) = default;
    class_d(class_d&&) = default;
    ~class_d() = default;

public:
    class_d(
        const std::list<std::string>& prop_0,
        const std::list<dogen::std_model::class_a>& prop_1,
        const std::list<dogen::std_model::pkg1::class_c>& prop_2,
        const std::list<unsigned int>& prop_3,
        const std::list<dogen::std_model::class_a>& prop_4,
        const std::list<std::list<unsigned int> >& prop_5);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_d& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_d& v, unsigned int version);

public:
    std::list<std::string> prop_0() const {
        return prop_0_;
    }

    void prop_0(const std::list<std::string>& v) {
        prop_0_ = v;
    }

    std::list<dogen::std_model::class_a> prop_1() const {
        return prop_1_;
    }

    void prop_1(const std::list<dogen::std_model::class_a>& v) {
        prop_1_ = v;
    }

    std::list<dogen::std_model::pkg1::class_c> prop_2() const {
        return prop_2_;
    }

    void prop_2(const std::list<dogen::std_model::pkg1::class_c>& v) {
        prop_2_ = v;
    }

    std::list<unsigned int> prop_3() const {
        return prop_3_;
    }

    void prop_3(const std::list<unsigned int>& v) {
        prop_3_ = v;
    }

    std::list<dogen::std_model::class_a> prop_4() const {
        return prop_4_;
    }

    void prop_4(const std::list<dogen::std_model::class_a>& v) {
        prop_4_ = v;
    }

    std::list<std::list<unsigned int> > prop_5() const {
        return prop_5_;
    }

    void prop_5(const std::list<std::list<unsigned int> >& v) {
        prop_5_ = v;
    }

public:
    bool operator==(const class_d& rhs) const;
    bool operator!=(const class_d& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_d& other) noexcept;
    class_d& operator=(class_d other);

private:
    std::list<std::string> prop_0_;
    std::list<dogen::std_model::class_a> prop_1_;
    std::list<dogen::std_model::pkg1::class_c> prop_2_;
    std::list<unsigned int> prop_3_;
    std::list<dogen::std_model::class_a> prop_4_;
    std::list<std::list<unsigned int> > prop_5_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::std_model::class_d& lhs,
    dogen::std_model::class_d& rhs) {
    lhs.swap(rhs);
}

}

#endif
