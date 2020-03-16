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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_KERNEL_MODEL_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_KERNEL_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/kernel.hpp"

namespace dogen::physical::entities {

/**
 * @brief Collection of code generation kernels available in the current instance of Dogen.
 */
class kernel_model final {
public:
    kernel_model() = default;
    kernel_model(const kernel_model&) = default;
    kernel_model(kernel_model&&) = default;
    ~kernel_model() = default;

public:
    explicit kernel_model(const std::unordered_map<std::string, dogen::physical::entities::kernel>& kernels);

public:
    /**
     * @brief Lists all available kernels, by kernel id.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::physical::entities::kernel>& kernels() const;
    std::unordered_map<std::string, dogen::physical::entities::kernel>& kernels();
    void kernels(const std::unordered_map<std::string, dogen::physical::entities::kernel>& v);
    void kernels(const std::unordered_map<std::string, dogen::physical::entities::kernel>&& v);
    /**@}*/

public:
    bool operator==(const kernel_model& rhs) const;
    bool operator!=(const kernel_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(kernel_model& other) noexcept;
    kernel_model& operator=(kernel_model other);

private:
    std::unordered_map<std::string, dogen::physical::entities::kernel> kernels_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::kernel_model& lhs,
    dogen::physical::entities::kernel_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
