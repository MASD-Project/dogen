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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVES_REPOSITORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DIRECTIVES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/tack/types/name.hpp"
#include "dogen/tack/hash/name_hash.hpp"
#include "dogen/cpp/serialization/formattables/inclusion_directives_repository_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class inclusion_directives_repository final {
public:
    inclusion_directives_repository() = default;
    inclusion_directives_repository(const inclusion_directives_repository&) = default;
    inclusion_directives_repository(inclusion_directives_repository&&) = default;
    ~inclusion_directives_repository() = default;

public:
    explicit inclusion_directives_repository(const std::unordered_map<dogen::tack::name, std::unordered_map<std::string, std::string> >& inclusion_directives_by_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const inclusion_directives_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, inclusion_directives_repository& v, unsigned int version);

public:
    const std::unordered_map<dogen::tack::name, std::unordered_map<std::string, std::string> >& inclusion_directives_by_name() const;
    std::unordered_map<dogen::tack::name, std::unordered_map<std::string, std::string> >& inclusion_directives_by_name();
    void inclusion_directives_by_name(const std::unordered_map<dogen::tack::name, std::unordered_map<std::string, std::string> >& v);
    void inclusion_directives_by_name(const std::unordered_map<dogen::tack::name, std::unordered_map<std::string, std::string> >&& v);

public:
    bool operator==(const inclusion_directives_repository& rhs) const;
    bool operator!=(const inclusion_directives_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion_directives_repository& other) noexcept;
    inclusion_directives_repository& operator=(inclusion_directives_repository other);

private:
    std::unordered_map<dogen::tack::name, std::unordered_map<std::string, std::string> > inclusion_directives_by_name_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::inclusion_directives_repository& lhs,
    dogen::cpp::formattables::inclusion_directives_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
