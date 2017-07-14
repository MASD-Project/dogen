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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_GLOBAL_ENABLEMENT_CONFIGURATION_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_GLOBAL_ENABLEMENT_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn/serialization/transforms/global_enablement_configuration_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class global_enablement_configuration final {
public:
    global_enablement_configuration(const global_enablement_configuration&) = default;
    ~global_enablement_configuration() = default;

public:
    global_enablement_configuration();

public:
    global_enablement_configuration(global_enablement_configuration&& rhs);

public:
    global_enablement_configuration(
        const bool kernel_enabled,
        const bool facet_enabled,
        const std::string& facet_name,
        const bool archetype_enabled,
        const bool facet_overwrite,
        const boost::optional<bool>& archetype_overwrite);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::transforms::global_enablement_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::transforms::global_enablement_configuration& v, unsigned int version);

public:
    bool kernel_enabled() const;
    void kernel_enabled(const bool v);

    bool facet_enabled() const;
    void facet_enabled(const bool v);

    const std::string& facet_name() const;
    std::string& facet_name();
    void facet_name(const std::string& v);
    void facet_name(const std::string&& v);

    bool archetype_enabled() const;
    void archetype_enabled(const bool v);

    bool facet_overwrite() const;
    void facet_overwrite(const bool v);

    const boost::optional<bool>& archetype_overwrite() const;
    boost::optional<bool>& archetype_overwrite();
    void archetype_overwrite(const boost::optional<bool>& v);
    void archetype_overwrite(const boost::optional<bool>&& v);

public:
    bool operator==(const global_enablement_configuration& rhs) const;
    bool operator!=(const global_enablement_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(global_enablement_configuration& other) noexcept;
    global_enablement_configuration& operator=(global_enablement_configuration other);

private:
    bool kernel_enabled_;
    bool facet_enabled_;
    std::string facet_name_;
    bool archetype_enabled_;
    bool facet_overwrite_;
    boost::optional<bool> archetype_overwrite_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::transforms::global_enablement_configuration& lhs,
    dogen::yarn::transforms::global_enablement_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
