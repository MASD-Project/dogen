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
#ifndef DOGEN_OM_TYPES_CPP_IFDEF_HPP
#define DOGEN_OM_TYPES_CPP_IFDEF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <iosfwd>
#include <list>
#include <string>
#include "dogen/om/serialization/cpp_ifdef_fwd_ser.hpp"
#include "dogen/om/types/cpp_feature.hpp"

namespace dogen {
namespace om {

class cpp_ifdef final : public dogen::om::cpp_feature {
public:
    cpp_ifdef() = default;
    cpp_ifdef(const cpp_ifdef&) = default;
    cpp_ifdef(cpp_ifdef&&) = default;

    virtual ~cpp_ifdef() noexcept { }

public:
    cpp_ifdef(
        const std::string& name,
        const std::string& condition,
        const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_ifdef& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_ifdef& v, unsigned int version);

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
    const std::string& condition() const;
    std::string& condition();
    void condition(const std::string& v);
    void condition(const std::string&& v);

    const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features() const;
    std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features();
    void features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& v);
    void features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >&& v);

public:
    bool operator==(const cpp_ifdef& rhs) const;
    bool operator!=(const cpp_ifdef& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_ifdef& other) noexcept;
    cpp_ifdef& operator=(cpp_ifdef other);

private:
    std::string condition_;
    std::list<boost::shared_ptr<dogen::om::cpp_feature> > features_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_ifdef& lhs,
    dogen::om::cpp_ifdef& rhs) {
    lhs.swap(rhs);
}

}

#endif
