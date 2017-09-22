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
#ifndef DOGEN_YARN_TYPES_META_MODEL_KERNEL_PROPERTIES_HPP
#define DOGEN_YARN_TYPES_META_MODEL_KERNEL_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/yarn/serialization/meta_model/kernel_properties_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Properties related to the kernel.
 */
class kernel_properties final {
public:
    kernel_properties(const kernel_properties&) = default;
    kernel_properties(kernel_properties&&) = default;
    ~kernel_properties() = default;

public:
    kernel_properties();

public:
    kernel_properties(
        const bool enabled,
        const std::string& directory,
        const bool force_kernel_directory);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::kernel_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::kernel_properties& v, unsigned int version);

public:
    /**
     * @brief If true, this kernel is enabled.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    /**
     * @brief Kernel specific directory name, if any.
     */
    /**@{*/
    const std::string& directory() const;
    std::string& directory();
    void directory(const std::string& v);
    void directory(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the kernel directory will be expressed, even when there is only one kernel
     * enabled.
     */
    /**@{*/
    bool force_kernel_directory() const;
    void force_kernel_directory(const bool v);
    /**@}*/

public:
    bool operator==(const kernel_properties& rhs) const;
    bool operator!=(const kernel_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(kernel_properties& other) noexcept;
    kernel_properties& operator=(kernel_properties other);

private:
    bool enabled_;
    std::string directory_;
    bool force_kernel_directory_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::kernel_properties& lhs,
    dogen::yarn::meta_model::kernel_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
