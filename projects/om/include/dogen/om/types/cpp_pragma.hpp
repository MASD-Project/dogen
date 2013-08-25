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
#ifndef DOGEN_OM_TYPES_CPP_PRAGMA_HPP
#define DOGEN_OM_TYPES_CPP_PRAGMA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include "dogen/om/serialization/cpp_pragma_fwd_ser.hpp"
#include "dogen/om/types/cpp_feature.hpp"

namespace dogen {
namespace om {

class cpp_pragma final : public dogen::om::cpp_feature {
public:
    cpp_pragma() = default;
    cpp_pragma(const cpp_pragma&) = default;
    cpp_pragma(cpp_pragma&&) = default;

    virtual ~cpp_pragma() noexcept { }

public:
    cpp_pragma(
        const std::string& name,
        const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_pragma& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_pragma& v, unsigned int version);

public:
    virtual void accept(const cpp_feature_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(cpp_feature_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const cpp_feature_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(cpp_feature_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);

public:
    bool operator==(const cpp_pragma& rhs) const;
    bool operator!=(const cpp_pragma& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_pragma& other) noexcept;
    cpp_pragma& operator=(cpp_pragma other);

private:
    std::string value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_pragma& lhs,
    dogen::om::cpp_pragma& rhs) {
    lhs.swap(rhs);
}

}

#endif
