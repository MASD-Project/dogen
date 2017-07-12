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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_KERNEL_REGISTRAR_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_KERNEL_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <algorithm>
#include "dogen/yarn/types/transforms/kernel_interface_fwd.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class kernel_registrar final {
public:
    kernel_registrar() = default;
    kernel_registrar(const kernel_registrar&) = default;
    kernel_registrar(kernel_registrar&&) = default;
    ~kernel_registrar() = default;

public:
    explicit kernel_registrar(const std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >& kernels_);

public:
    const std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >& kernels_() const;
    std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >& kernels_();
    void kernels_(const std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >& v);
    void kernels_(const std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >&& v);

public:
    bool operator==(const kernel_registrar& rhs) const;
    bool operator!=(const kernel_registrar& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(kernel_registrar& other) noexcept;
    kernel_registrar& operator=(kernel_registrar other);

private:
    std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> > kernels__;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::transforms::kernel_registrar& lhs,
    dogen::yarn::transforms::kernel_registrar& rhs) {
    lhs.swap(rhs);
}

}

#endif
