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
#ifndef DOGEN_GENERATION_CSHARP_TYPES_FABRIC_VISUAL_STUDIO_CONFIGURATION_HPP
#define DOGEN_GENERATION_CSHARP_TYPES_FABRIC_VISUAL_STUDIO_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.generation.csharp/serialization/fabric/visual_studio_configuration_fwd_ser.hpp"

namespace dogen {
namespace generation {
namespace csharp {
namespace fabric {

class visual_studio_configuration final {
public:
    visual_studio_configuration() = default;
    visual_studio_configuration(const visual_studio_configuration&) = default;
    visual_studio_configuration(visual_studio_configuration&&) = default;
    ~visual_studio_configuration() = default;

public:
    visual_studio_configuration(
        const std::string& project_solution_guid,
        const std::string& project_guid);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::generation::csharp::fabric::visual_studio_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::generation::csharp::fabric::visual_studio_configuration& v, unsigned int version);

public:
    const std::string& project_solution_guid() const;
    std::string& project_solution_guid();
    void project_solution_guid(const std::string& v);
    void project_solution_guid(const std::string&& v);

    const std::string& project_guid() const;
    std::string& project_guid();
    void project_guid(const std::string& v);
    void project_guid(const std::string&& v);

public:
    bool operator==(const visual_studio_configuration& rhs) const;
    bool operator!=(const visual_studio_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(visual_studio_configuration& other) noexcept;
    visual_studio_configuration& operator=(visual_studio_configuration other);

private:
    std::string project_solution_guid_;
    std::string project_guid_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::generation::csharp::fabric::visual_studio_configuration& lhs,
    dogen::generation::csharp::fabric::visual_studio_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
