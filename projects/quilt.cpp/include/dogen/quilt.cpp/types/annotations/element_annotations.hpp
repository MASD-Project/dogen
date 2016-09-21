/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_ELEMENT_ANNOTATIONS_HPP
#define DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_ELEMENT_ANNOTATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_fwd.hpp"
#include "dogen/quilt.cpp/serialization/annotations/element_annotations_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

class element_annotations final {
public:
    element_annotations() = default;
    element_annotations(const element_annotations&) = default;
    element_annotations(element_annotations&&) = default;
    ~element_annotations() = default;

public:
    element_annotations(
        const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& opaque_annotations,
        const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >& opaque_annotations_for_property);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::annotations::element_annotations& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::annotations::element_annotations& v, unsigned int version);

public:
    const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& opaque_annotations() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& opaque_annotations();
    void opaque_annotations(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& v);
    void opaque_annotations(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >&& v);

    const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >& opaque_annotations_for_property() const;
    std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >& opaque_annotations_for_property();
    void opaque_annotations_for_property(const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >& v);
    void opaque_annotations_for_property(const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > >&& v);

public:
    bool operator==(const element_annotations& rhs) const;
    bool operator!=(const element_annotations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_annotations& other) noexcept;
    element_annotations& operator=(element_annotations other);

private:
    std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > opaque_annotations_;
    std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > > opaque_annotations_for_property_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::annotations::element_annotations& lhs,
    dogen::quilt::cpp::annotations::element_annotations& rhs) {
    lhs.swap(rhs);
}

}

#endif
