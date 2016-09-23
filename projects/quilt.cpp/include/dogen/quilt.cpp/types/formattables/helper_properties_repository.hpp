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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_PROPERTIES_REPOSITORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_PROPERTIES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/quilt.cpp/types/formattables/helper_configuration.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_properties_repository_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class helper_properties_repository final {
public:
    helper_properties_repository() = default;
    helper_properties_repository(const helper_properties_repository&) = default;
    helper_properties_repository(helper_properties_repository&&) = default;
    ~helper_properties_repository() = default;

public:
    explicit helper_properties_repository(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_configuration> >& by_id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::helper_properties_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::helper_properties_repository& v, unsigned int version);

public:
    const std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_configuration> >& by_id() const;
    std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_configuration> >& by_id();
    void by_id(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_configuration> >& v);
    void by_id(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_configuration> >&& v);

public:
    bool operator==(const helper_properties_repository& rhs) const;
    bool operator!=(const helper_properties_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_properties_repository& other) noexcept;
    helper_properties_repository& operator=(helper_properties_repository other);

private:
    std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_configuration> > by_id_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::helper_properties_repository& lhs,
    dogen::quilt::cpp::formattables::helper_properties_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
