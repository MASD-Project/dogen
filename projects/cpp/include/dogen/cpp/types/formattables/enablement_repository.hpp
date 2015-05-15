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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_ENABLEMENT_REPOSITORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_ENABLEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/cpp/serialization/formattables/enablement_repository_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class enablement_repository final {
public:
    enablement_repository() = default;
    enablement_repository(const enablement_repository&) = default;
    enablement_repository(enablement_repository&&) = default;
    ~enablement_repository() = default;

public:
    explicit enablement_repository(const std::unordered_map<dogen::sml::qname, std::unordered_map<std::string, bool> >& enablement_by_qname);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const enablement_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, enablement_repository& v, unsigned int version);

public:
    const std::unordered_map<dogen::sml::qname, std::unordered_map<std::string, bool> >& enablement_by_qname() const;
    std::unordered_map<dogen::sml::qname, std::unordered_map<std::string, bool> >& enablement_by_qname();
    void enablement_by_qname(const std::unordered_map<dogen::sml::qname, std::unordered_map<std::string, bool> >& v);
    void enablement_by_qname(const std::unordered_map<dogen::sml::qname, std::unordered_map<std::string, bool> >&& v);

public:
    bool operator==(const enablement_repository& rhs) const;
    bool operator!=(const enablement_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(enablement_repository& other) noexcept;
    enablement_repository& operator=(enablement_repository other);

private:
    std::unordered_map<dogen::sml::qname, std::unordered_map<std::string, bool> > enablement_by_qname_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::enablement_repository& lhs,
    dogen::cpp::formattables::enablement_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
