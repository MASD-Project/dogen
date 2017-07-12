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
#include "dogen/yarn/types/transforms/kernel_interface.hpp"
#include "dogen/yarn/types/transforms/kernel_registrar.hpp"

namespace std {

inline bool operator==(const std::shared_ptr<dogen::yarn::transforms::kernel_interface>& lhs,
const std::shared_ptr<dogen::yarn::transforms::kernel_interface>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace yarn {
namespace transforms {

kernel_registrar::kernel_registrar(const std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >& kernels_)
    : kernels__(kernels_) { }

void kernel_registrar::swap(kernel_registrar& other) noexcept {
    using std::swap;
    swap(kernels__, other.kernels__);
}

bool kernel_registrar::operator==(const kernel_registrar& rhs) const {
    return kernels__ == rhs.kernels__;
}

kernel_registrar& kernel_registrar::operator=(kernel_registrar other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >& kernel_registrar::kernels_() const {
    return kernels__;
}

std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >& kernel_registrar::kernels_() {
    return kernels__;
}

void kernel_registrar::kernels_(const std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >& v) {
    kernels__ = v;
}

void kernel_registrar::kernels_(const std::list<std::shared_ptr<dogen::yarn::transforms::kernel_interface> >&& v) {
    kernels__ = std::move(v);
}

} } }
