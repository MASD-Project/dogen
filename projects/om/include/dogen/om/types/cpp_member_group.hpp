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
#ifndef DOGEN_OM_TYPES_CPP_MEMBER_GROUP_HPP
#define DOGEN_OM_TYPES_CPP_MEMBER_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <list>
#include "dogen/om/serialization/cpp_member_group_fwd_ser.hpp"
#include "dogen/om/types/cpp_access_specifier_types.hpp"
#include "dogen/om/types/cpp_feature_fwd.hpp"

namespace dogen {
namespace om {

class cpp_member_group final {
public:
    cpp_member_group(const cpp_member_group&) = default;
    cpp_member_group(cpp_member_group&&) = default;
    ~cpp_member_group() = default;

public:
    cpp_member_group();

public:
    cpp_member_group(
        const dogen::om::cpp_access_specifier_types& type,
        const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_member_group& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_member_group& v, unsigned int version);

public:
    dogen::om::cpp_access_specifier_types type() const;
    void type(const dogen::om::cpp_access_specifier_types& v);

    const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features() const;
    std::list<boost::shared_ptr<dogen::om::cpp_feature> >& features();
    void features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >& v);
    void features(const std::list<boost::shared_ptr<dogen::om::cpp_feature> >&& v);

public:
    bool operator==(const cpp_member_group& rhs) const;
    bool operator!=(const cpp_member_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cpp_member_group& other) noexcept;
    cpp_member_group& operator=(cpp_member_group other);

private:
    dogen::om::cpp_access_specifier_types type_;
    std::list<boost::shared_ptr<dogen::om::cpp_feature> > features_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_member_group& lhs,
    dogen::om::cpp_member_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
