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
#ifndef DOGEN_DYNAMIC_TYPES_NUMBER_COLLECTION_HPP
#define DOGEN_DYNAMIC_TYPES_NUMBER_COLLECTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/dynamic/serialization/number_collection_fwd_ser.hpp"
#include "dogen/dynamic/types/number.hpp"
#include "dogen/dynamic/types/value.hpp"

namespace dogen {
namespace dynamic {

class number_collection final : public dogen::dynamic::value {
public:
    number_collection() = default;
    number_collection(const number_collection&) = default;
    number_collection(number_collection&&) = default;

    virtual ~number_collection() noexcept { }

public:
    explicit number_collection(const std::list<dogen::dynamic::number>& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const number_collection& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, number_collection& v, unsigned int version);

public:
    virtual void accept(const value_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(value_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const value_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(value_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<dogen::dynamic::number>& content() const;
    std::list<dogen::dynamic::number>& content();
    void content(const std::list<dogen::dynamic::number>& v);
    void content(const std::list<dogen::dynamic::number>&& v);

public:
    bool operator==(const number_collection& rhs) const;
    bool operator!=(const number_collection& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::dynamic::value& other) const override;

public:
    void swap(number_collection& other) noexcept;
    number_collection& operator=(number_collection other);

private:
    std::list<dogen::dynamic::number> content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dynamic::number_collection& lhs,
    dogen::dynamic::number_collection& rhs) {
    lhs.swap(rhs);
}

}

#endif
