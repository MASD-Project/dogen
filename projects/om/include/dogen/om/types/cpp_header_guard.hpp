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
#ifndef DOGEN_OM_TYPES_CPP_HEADER_GUARD_HPP
#define DOGEN_OM_TYPES_CPP_HEADER_GUARD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include "dogen/om/serialization/cpp_header_guard_fwd_ser.hpp"
#include "dogen/om/types/cpp_feature.hpp"

namespace dogen {
namespace om {

class cpp_header_guard final : public dogen::om::cpp_feature {
public:
    cpp_header_guard(const cpp_header_guard&) = default;
    cpp_header_guard(cpp_header_guard&&) = default;

public:
    cpp_header_guard();

    virtual ~cpp_header_guard() noexcept { }

public:
    cpp_header_guard(
        const std::string& name,
        const std::string& guard_name,
        const bool use_pragma_once);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_header_guard& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_header_guard& v, unsigned int version);

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
    const std::string& guard_name() const;
    std::string& guard_name();
    void guard_name(const std::string& v);
    void guard_name(const std::string&& v);

    bool use_pragma_once() const;
    void use_pragma_once(const bool v);

public:
    bool operator==(const cpp_header_guard& rhs) const;
    bool operator!=(const cpp_header_guard& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_header_guard& other) noexcept;
    cpp_header_guard& operator=(cpp_header_guard other);

private:
    std::string guard_name_;
    bool use_pragma_once_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_header_guard& lhs,
    dogen::om::cpp_header_guard& rhs) {
    lhs.swap(rhs);
}

}

#endif
