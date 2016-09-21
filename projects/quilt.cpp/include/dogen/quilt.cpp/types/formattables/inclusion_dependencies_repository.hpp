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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_REPOSITORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/quilt.cpp/serialization/formattables/inclusion_dependencies_repository_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class inclusion_dependencies_repository final {
public:
    inclusion_dependencies_repository() = default;
    inclusion_dependencies_repository(const inclusion_dependencies_repository&) = default;
    inclusion_dependencies_repository(inclusion_dependencies_repository&&) = default;
    ~inclusion_dependencies_repository() = default;

public:
    explicit inclusion_dependencies_repository(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::list<std::string> > >& by_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::inclusion_dependencies_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::inclusion_dependencies_repository& v, unsigned int version);

public:
    const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::list<std::string> > >& by_name() const;
    std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::list<std::string> > >& by_name();
    void by_name(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::list<std::string> > >& v);
    void by_name(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::list<std::string> > >&& v);

public:
    bool operator==(const inclusion_dependencies_repository& rhs) const;
    bool operator!=(const inclusion_dependencies_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion_dependencies_repository& other) noexcept;
    inclusion_dependencies_repository& operator=(inclusion_dependencies_repository other);

private:
    std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, std::list<std::string> > > by_name_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::inclusion_dependencies_repository& lhs,
    dogen::quilt::cpp::formattables::inclusion_dependencies_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
