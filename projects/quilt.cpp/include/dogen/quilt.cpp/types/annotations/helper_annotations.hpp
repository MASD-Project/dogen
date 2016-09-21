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
#ifndef DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_HELPER_ANNOTATIONS_HPP
#define DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_HELPER_ANNOTATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/annotations/helper_annotations_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

/**
 * @brief Contains all annotations related to formatter helpers.
 */
class helper_annotations final {
public:
    helper_annotations() = default;
    helper_annotations(const helper_annotations&) = default;
    helper_annotations(helper_annotations&&) = default;
    ~helper_annotations() = default;

public:
    explicit helper_annotations(const std::string& family);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::annotations::helper_annotations& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::annotations::helper_annotations& v, unsigned int version);

public:
    /**
     * @brief Family of the helper methods for this element.
     */
    /**@{*/
    const std::string& family() const;
    std::string& family();
    void family(const std::string& v);
    void family(const std::string&& v);
    /**@}*/

public:
    bool operator==(const helper_annotations& rhs) const;
    bool operator!=(const helper_annotations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_annotations& other) noexcept;
    helper_annotations& operator=(helper_annotations other);

private:
    std::string family_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::annotations::helper_annotations& lhs,
    dogen::quilt::cpp::annotations::helper_annotations& rhs) {
    lhs.swap(rhs);
}

}

#endif
