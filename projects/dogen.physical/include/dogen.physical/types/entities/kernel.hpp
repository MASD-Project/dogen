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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_KERNEL_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_KERNEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.physical/types/entities/backend.hpp"
#include "dogen.physical/types/entities/location.hpp"
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.physical/types/entities/meta_name_repository.hpp"

namespace dogen::physical::entities {

class kernel final {
public:
    kernel() = default;
    kernel(const kernel&) = default;
    kernel(kernel&&) = default;
    ~kernel() = default;

public:
    kernel(
        const dogen::physical::entities::location& location,
        const std::string& description,
        const dogen::physical::entities::meta_name& meta_name,
        const std::list<dogen::physical::entities::backend>& backends,
        const dogen::physical::entities::meta_name_repository& names);

public:
    /**
     * @brief Position of this entity in physical space.
     */
    /**@{*/
    const dogen::physical::entities::location& location() const;
    dogen::physical::entities::location& location();
    void location(const dogen::physical::entities::location& v);
    void location(const dogen::physical::entities::location&& v);
    /**@}*/

    /**
     * @brief Human readable description of the entity.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::physical::entities::meta_name& meta_name() const;
    dogen::physical::entities::meta_name& meta_name();
    void meta_name(const dogen::physical::entities::meta_name& v);
    void meta_name(const dogen::physical::entities::meta_name&& v);
    /**@}*/

    const std::list<dogen::physical::entities::backend>& backends() const;
    std::list<dogen::physical::entities::backend>& backends();
    void backends(const std::list<dogen::physical::entities::backend>& v);
    void backends(const std::list<dogen::physical::entities::backend>&& v);

    /**
     * @brief Repository with all the meta-names in this kernel.
     */
    /**@{*/
    const dogen::physical::entities::meta_name_repository& names() const;
    dogen::physical::entities::meta_name_repository& names();
    void names(const dogen::physical::entities::meta_name_repository& v);
    void names(const dogen::physical::entities::meta_name_repository&& v);
    /**@}*/

public:
    bool operator==(const kernel& rhs) const;
    bool operator!=(const kernel& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(kernel& other) noexcept;
    kernel& operator=(kernel other);

private:
    dogen::physical::entities::location location_;
    std::string description_;
    dogen::physical::entities::meta_name meta_name_;
    std::list<dogen::physical::entities::backend> backends_;
    dogen::physical::entities::meta_name_repository names_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::kernel& lhs,
    dogen::physical::entities::kernel& rhs) {
    lhs.swap(rhs);
}

}

#endif
