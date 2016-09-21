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
#ifndef DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_INCLUSION_DIRECTIVE_ANNOTATIONS_HPP
#define DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_INCLUSION_DIRECTIVE_ANNOTATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/quilt.cpp/serialization/annotations/inclusion_directive_annotations_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

class inclusion_directive_annotations final {
public:
    inclusion_directive_annotations(const inclusion_directive_annotations&) = default;
    ~inclusion_directive_annotations() = default;

public:
    inclusion_directive_annotations();

public:
    inclusion_directive_annotations(inclusion_directive_annotations&& rhs);

public:
    inclusion_directive_annotations(
        const bool inclusion_required,
        const boost::optional<std::string>& inclusion_directive);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::annotations::inclusion_directive_annotations& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::annotations::inclusion_directive_annotations& v, unsigned int version);

public:
    bool inclusion_required() const;
    void inclusion_required(const bool v);

    const boost::optional<std::string>& inclusion_directive() const;
    boost::optional<std::string>& inclusion_directive();
    void inclusion_directive(const boost::optional<std::string>& v);
    void inclusion_directive(const boost::optional<std::string>&& v);

public:
    bool operator==(const inclusion_directive_annotations& rhs) const;
    bool operator!=(const inclusion_directive_annotations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion_directive_annotations& other) noexcept;
    inclusion_directive_annotations& operator=(inclusion_directive_annotations other);

private:
    bool inclusion_required_;
    boost::optional<std::string> inclusion_directive_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::annotations::inclusion_directive_annotations& lhs,
    dogen::quilt::cpp::annotations::inclusion_directive_annotations& rhs) {
    lhs.swap(rhs);
}

}

#endif
