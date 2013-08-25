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
#ifndef DOGEN_OM_TYPES_CPP_FEATURE_HPP
#define DOGEN_OM_TYPES_CPP_FEATURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include "dogen/om/serialization/cpp_feature_fwd_ser.hpp"
#include "dogen/om/types/cpp_feature_visitor.hpp"

namespace dogen {
namespace om {

/**
 * @brief Base class for all C++ features.
 */
class cpp_feature {
public:
    cpp_feature() = default;
    cpp_feature(const cpp_feature&) = default;
    cpp_feature(cpp_feature&&) = default;

    virtual ~cpp_feature() noexcept = 0;

public:
    explicit cpp_feature(const std::string& name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_feature& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_feature& v, unsigned int version);

public:
    virtual void accept(const cpp_feature_visitor& v) const = 0;
    virtual void accept(cpp_feature_visitor& v) const = 0;
    virtual void accept(const cpp_feature_visitor& v) = 0;
    virtual void accept(cpp_feature_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

protected:
    bool compare(const cpp_feature& rhs) const;
public:
    virtual bool equals(const cpp_feature& other) const = 0;

protected:
    void swap(cpp_feature& other) noexcept;

private:
    std::string name_;
};

inline cpp_feature::~cpp_feature() noexcept { }

inline bool operator==(const cpp_feature& lhs, const cpp_feature& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
