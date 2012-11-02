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
#ifndef DOGEN_STD_MODEL_DOMAIN_DERIVED_HPP
#define DOGEN_STD_MODEL_DOMAIN_DERIVED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/std_model/domain/base.hpp"
#include "dogen/std_model/domain/pkg1/class_c.hpp"
#include "dogen/std_model/serialization/derived_fwd_ser.hpp"

namespace dogen {
namespace std_model {

class derived final : public dogen::std_model::base {
public:
    derived() = default;
    derived(const derived&) = default;
    derived(derived&&) = default;

public:
    derived(
        const std::vector<std::string>& prop_0,
        const dogen::std_model::versioned_key& versioned_key,
        const std::list<dogen::std_model::pkg1::class_c>& prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const derived& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, derived& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    std::list<dogen::std_model::pkg1::class_c> prop_1() const {
        return prop_1_;
    }

    void prop_1(const std::list<dogen::std_model::pkg1::class_c>& v) {
        prop_1_ = v;
    }

public:
    bool operator==(const derived& rhs) const;
    bool operator!=(const derived& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::std_model::base& other) const override;

public:
    void swap(derived& other) noexcept;
    derived& operator=(derived other);

private:
    std::list<dogen::std_model::pkg1::class_c> prop_1_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::std_model::derived& lhs,
    dogen::std_model::derived& rhs) {
    lhs.swap(rhs);
}

}

#endif
