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
#ifndef DOGEN_OM_TYPES_CPP_INCLUDE_DIRECTIVE_HPP
#define DOGEN_OM_TYPES_CPP_INCLUDE_DIRECTIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include "dogen/om/serialization/cpp_include_directive_fwd_ser.hpp"
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_include_types.hpp"

namespace dogen {
namespace om {

class cpp_include_directive final : public dogen::om::cpp_feature {
public:
    cpp_include_directive(const cpp_include_directive&) = default;

public:
    cpp_include_directive();

    virtual ~cpp_include_directive() noexcept { }

public:
    cpp_include_directive(cpp_include_directive&& rhs);

public:
    cpp_include_directive(
        const std::string& name,
        const boost::filesystem::path& relative_path,
        const dogen::om::cpp_include_types& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_include_directive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_include_directive& v, unsigned int version);

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
    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);

    dogen::om::cpp_include_types type() const;
    void type(const dogen::om::cpp_include_types& v);

public:
    bool operator==(const cpp_include_directive& rhs) const;
    bool operator!=(const cpp_include_directive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_include_directive& other) noexcept;
    cpp_include_directive& operator=(cpp_include_directive other);

private:
    boost::filesystem::path relative_path_;
    dogen::om::cpp_include_types type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_include_directive& lhs,
    dogen::om::cpp_include_directive& rhs) {
    lhs.swap(rhs);
}

}

#endif
