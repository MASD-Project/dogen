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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/element_fwd.hpp"
#include "dogen/quilt.cpp/types/formattables/element_configuration.hpp"
#include "dogen/quilt.cpp/serialization/formattables/formattable_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class formattable final {
public:
    formattable() = default;
    formattable(const formattable&) = default;
    formattable(formattable&&) = default;
    ~formattable() = default;

public:
    formattable(
        const boost::shared_ptr<dogen::yarn::element>& master_segment,
        const std::list<boost::shared_ptr<dogen::yarn::element> >& all_segments,
        const dogen::quilt::cpp::formattables::element_configuration& configuration);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::formattable& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::formattable& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::yarn::element>& master_segment() const;
    boost::shared_ptr<dogen::yarn::element>& master_segment();
    void master_segment(const boost::shared_ptr<dogen::yarn::element>& v);
    void master_segment(const boost::shared_ptr<dogen::yarn::element>&& v);

    const std::list<boost::shared_ptr<dogen::yarn::element> >& all_segments() const;
    std::list<boost::shared_ptr<dogen::yarn::element> >& all_segments();
    void all_segments(const std::list<boost::shared_ptr<dogen::yarn::element> >& v);
    void all_segments(const std::list<boost::shared_ptr<dogen::yarn::element> >&& v);

    const dogen::quilt::cpp::formattables::element_configuration& configuration() const;
    dogen::quilt::cpp::formattables::element_configuration& configuration();
    void configuration(const dogen::quilt::cpp::formattables::element_configuration& v);
    void configuration(const dogen::quilt::cpp::formattables::element_configuration&& v);

public:
    bool operator==(const formattable& rhs) const;
    bool operator!=(const formattable& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formattable& other) noexcept;
    formattable& operator=(formattable other);

private:
    boost::shared_ptr<dogen::yarn::element> master_segment_;
    std::list<boost::shared_ptr<dogen::yarn::element> > all_segments_;
    dogen::quilt::cpp::formattables::element_configuration configuration_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::formattable& lhs,
    dogen::quilt::cpp::formattables::formattable& rhs) {
    lhs.swap(rhs);
}

}

#endif
