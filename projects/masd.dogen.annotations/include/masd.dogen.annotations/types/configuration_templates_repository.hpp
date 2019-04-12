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
#ifndef MASD_DOGEN_ANNOTATIONS_TYPES_CONFIGURATION_TEMPLATES_REPOSITORY_HPP
#define MASD_DOGEN_ANNOTATIONS_TYPES_CONFIGURATION_TEMPLATES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "masd.dogen.annotations/types/profile.hpp"

namespace masd::dogen::annotations {

class configuration_templates_repository final {
public:
    configuration_templates_repository() = default;
    configuration_templates_repository(const configuration_templates_repository&) = default;
    configuration_templates_repository(configuration_templates_repository&&) = default;
    ~configuration_templates_repository() = default;

public:
    explicit configuration_templates_repository(const std::unordered_map<std::string, masd::dogen::annotations::profile>& by_name);

public:
    const std::unordered_map<std::string, masd::dogen::annotations::profile>& by_name() const;
    std::unordered_map<std::string, masd::dogen::annotations::profile>& by_name();
    void by_name(const std::unordered_map<std::string, masd::dogen::annotations::profile>& v);
    void by_name(const std::unordered_map<std::string, masd::dogen::annotations::profile>&& v);

public:
    bool operator==(const configuration_templates_repository& rhs) const;
    bool operator!=(const configuration_templates_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration_templates_repository& other) noexcept;
    configuration_templates_repository& operator=(configuration_templates_repository other);

private:
    std::unordered_map<std::string, masd::dogen::annotations::profile> by_name_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::annotations::configuration_templates_repository& lhs,
    masd::dogen::annotations::configuration_templates_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
