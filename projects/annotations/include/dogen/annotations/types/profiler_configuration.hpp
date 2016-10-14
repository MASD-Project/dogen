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
#ifndef DOGEN_ANNOTATIONS_TYPES_PROFILER_CONFIGURATION_HPP
#define DOGEN_ANNOTATIONS_TYPES_PROFILER_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/annotations/types/profile.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/serialization/profiler_configuration_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class profiler_configuration final {
public:
    profiler_configuration(const profiler_configuration&) = default;
    profiler_configuration(profiler_configuration&&) = default;
    ~profiler_configuration() = default;

public:
    profiler_configuration();

public:
    profiler_configuration(
        const dogen::annotations::profile& profile,
        const dogen::annotations::annotation& annotation,
        const bool merged);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::profiler_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::profiler_configuration& v, unsigned int version);

public:
    const dogen::annotations::profile& profile() const;
    dogen::annotations::profile& profile();
    void profile(const dogen::annotations::profile& v);
    void profile(const dogen::annotations::profile&& v);

    const dogen::annotations::annotation& annotation() const;
    dogen::annotations::annotation& annotation();
    void annotation(const dogen::annotations::annotation& v);
    void annotation(const dogen::annotations::annotation&& v);

    bool merged() const;
    void merged(const bool v);

public:
    bool operator==(const profiler_configuration& rhs) const;
    bool operator!=(const profiler_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(profiler_configuration& other) noexcept;
    profiler_configuration& operator=(profiler_configuration other);

private:
    dogen::annotations::profile profile_;
    dogen::annotations::annotation annotation_;
    bool merged_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::profiler_configuration& lhs,
    dogen::annotations::profiler_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
