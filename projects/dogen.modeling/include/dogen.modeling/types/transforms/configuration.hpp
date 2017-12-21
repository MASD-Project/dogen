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
#ifndef DOGEN_MODELING_TYPES_TRANSFORMS_CONFIGURATION_HPP
#define DOGEN_MODELING_TYPES_TRANSFORMS_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_set>
#include "dogen.modeling/serialization/transforms/configuration_fwd_ser.hpp"

namespace dogen {
namespace modeling {
namespace transforms {

class configuration final {
public:
    configuration(const configuration&) = default;
    configuration(configuration&&) = default;
    ~configuration() = default;

public:
    configuration();

public:
    configuration(
        const std::unordered_set<std::string>& enabled_backends,
        const bool enable_backend_directories);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::modeling::transforms::configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::modeling::transforms::configuration& v, unsigned int version);

public:
    const std::unordered_set<std::string>& enabled_backends() const;
    std::unordered_set<std::string>& enabled_backends();
    void enabled_backends(const std::unordered_set<std::string>& v);
    void enabled_backends(const std::unordered_set<std::string>&& v);

    bool enable_backend_directories() const;
    void enable_backend_directories(const bool v);

public:
    bool operator==(const configuration& rhs) const;
    bool operator!=(const configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration& other) noexcept;
    configuration& operator=(configuration other);

private:
    std::unordered_set<std::string> enabled_backends_;
    bool enable_backend_directories_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::modeling::transforms::configuration& lhs,
    dogen::modeling::transforms::configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
