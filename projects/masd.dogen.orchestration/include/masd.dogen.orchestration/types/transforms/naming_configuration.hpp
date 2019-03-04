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
#ifndef MASD_DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_NAMING_CONFIGURATION_HPP
#define MASD_DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_NAMING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace masd::dogen::orchestration::transforms {

class naming_configuration final {
public:
    naming_configuration() = default;
    naming_configuration(const naming_configuration&) = default;
    naming_configuration(naming_configuration&&) = default;
    ~naming_configuration() = default;

public:
    naming_configuration(
        const std::string& external_modules,
        const std::string& model_modules);

public:
    const std::string& external_modules() const;
    std::string& external_modules();
    void external_modules(const std::string& v);
    void external_modules(const std::string&& v);

    const std::string& model_modules() const;
    std::string& model_modules();
    void model_modules(const std::string& v);
    void model_modules(const std::string&& v);

public:
    bool operator==(const naming_configuration& rhs) const;
    bool operator!=(const naming_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(naming_configuration& other) noexcept;
    naming_configuration& operator=(naming_configuration other);

private:
    std::string external_modules_;
    std::string model_modules_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::orchestration::transforms::naming_configuration& lhs,
    masd::dogen::orchestration::transforms::naming_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
