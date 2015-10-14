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
#ifndef DOGEN_CPP_TYPES_SETTINGS_BUNDLE_REPOSITORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_BUNDLE_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <unordered_map>
#include "dogen/tack/types/name.hpp"
#include "dogen/tack/hash/name_hash.hpp"
#include "dogen/cpp/types/settings/bundle.hpp"
#include "dogen/cpp/serialization/settings/bundle_repository_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class bundle_repository final {
public:
    bundle_repository() = default;
    bundle_repository(const bundle_repository&) = default;
    bundle_repository(bundle_repository&&) = default;
    ~bundle_repository() = default;

public:
    explicit bundle_repository(const std::unordered_map<dogen::tack::name, dogen::cpp::settings::bundle>& bundles_by_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const bundle_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, bundle_repository& v, unsigned int version);

public:
    const std::unordered_map<dogen::tack::name, dogen::cpp::settings::bundle>& bundles_by_name() const;
    std::unordered_map<dogen::tack::name, dogen::cpp::settings::bundle>& bundles_by_name();
    void bundles_by_name(const std::unordered_map<dogen::tack::name, dogen::cpp::settings::bundle>& v);
    void bundles_by_name(const std::unordered_map<dogen::tack::name, dogen::cpp::settings::bundle>&& v);

public:
    bool operator==(const bundle_repository& rhs) const;
    bool operator!=(const bundle_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(bundle_repository& other) noexcept;
    bundle_repository& operator=(bundle_repository other);

private:
    std::unordered_map<dogen::tack::name, dogen::cpp::settings::bundle> bundles_by_name_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::bundle_repository& lhs,
    dogen::cpp::settings::bundle_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
