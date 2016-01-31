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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_DEPENDENCIES_REPOSITORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_DEPENDENCIES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/quilt.cpp/serialization/formattables/helper_dependencies_repository_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Maps a qualified name to the helper dependencies associated with it.
 *
 * At present we only need to know about helper family dependencies so we do not
 * bother modeling helper dependencies as a class.
 */
class helper_dependencies_repository final {
public:
    helper_dependencies_repository() = default;
    helper_dependencies_repository(const helper_dependencies_repository&) = default;
    helper_dependencies_repository(helper_dependencies_repository&&) = default;
    ~helper_dependencies_repository() = default;

public:
    explicit helper_dependencies_repository(const std::unordered_map<std::string, std::list<std::string> >& helper_dependencies_by_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const helper_dependencies_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, helper_dependencies_repository& v, unsigned int version);

public:
    const std::unordered_map<std::string, std::list<std::string> >& helper_dependencies_by_name() const;
    std::unordered_map<std::string, std::list<std::string> >& helper_dependencies_by_name();
    void helper_dependencies_by_name(const std::unordered_map<std::string, std::list<std::string> >& v);
    void helper_dependencies_by_name(const std::unordered_map<std::string, std::list<std::string> >&& v);

public:
    bool operator==(const helper_dependencies_repository& rhs) const;
    bool operator!=(const helper_dependencies_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_dependencies_repository& other) noexcept;
    helper_dependencies_repository& operator=(helper_dependencies_repository other);

private:
    std::unordered_map<std::string, std::list<std::string> > helper_dependencies_by_name_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::helper_dependencies_repository& lhs,
    dogen::quilt::cpp::formattables::helper_dependencies_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
