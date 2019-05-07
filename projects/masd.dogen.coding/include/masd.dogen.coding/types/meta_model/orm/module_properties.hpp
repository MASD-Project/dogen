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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_ORM_MODULE_PROPERTIES_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_ORM_MODULE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace masd::dogen::coding::meta_model::orm {

class module_properties final {
public:
    module_properties() = default;
    module_properties(const module_properties&) = default;
    module_properties(module_properties&&) = default;
    ~module_properties() = default;

public:
    explicit module_properties(const std::string& schema_name);

public:
    /**
     * @brief Name of the database schema in which to place this element.
     */
    /**@{*/
    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);
    /**@}*/

public:
    bool operator==(const module_properties& rhs) const;
    bool operator!=(const module_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(module_properties& other) noexcept;
    module_properties& operator=(module_properties other);

private:
    std::string schema_name_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::orm::module_properties& lhs,
    masd::dogen::coding::meta_model::orm::module_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
