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
#ifndef DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_ODB_ANNOTATIONS_HPP
#define DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_ODB_ANNOTATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/types/annotations/opaque_annotations.hpp"
#include "dogen/quilt.cpp/serialization/annotations/odb_annotations_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

/**
 * @brief Annotations for ODB formatters.
 */
class odb_annotations final : public dogen::quilt::cpp::annotations::opaque_annotations {
public:
    odb_annotations() = default;
    odb_annotations(const odb_annotations&) = default;
    odb_annotations(odb_annotations&&) = default;

    virtual ~odb_annotations() noexcept { }

public:
    explicit odb_annotations(const std::list<std::string>& pragmas);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::annotations::odb_annotations& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::annotations::odb_annotations& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief ODB pragmas.
     */
    /**@{*/
    const std::list<std::string>& pragmas() const;
    std::list<std::string>& pragmas();
    void pragmas(const std::list<std::string>& v);
    void pragmas(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const odb_annotations& rhs) const;
    bool operator!=(const odb_annotations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::quilt::cpp::annotations::opaque_annotations& other) const override;

public:
    void swap(odb_annotations& other) noexcept;
    odb_annotations& operator=(odb_annotations other);

private:
    std::list<std::string> pragmas_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::annotations::odb_annotations& lhs,
    dogen::quilt::cpp::annotations::odb_annotations& rhs) {
    lhs.swap(rhs);
}

}

#endif
