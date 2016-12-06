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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt/types/registrar_error.hpp"
#include "dogen/quilt/types/kernel_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.kernel_registrar"));

const std::string no_kernels("No kernels provided.");
const std::string null_kernel("Kernel supplied is null");

}

namespace dogen {
namespace quilt {

void kernel_registrar::validate() const {
    if (kernels_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_kernels;
        BOOST_THROW_EXCEPTION(registrar_error(no_kernels));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

void kernel_registrar::register_kernel(std::shared_ptr<kernel_interface> b) {
    // no logging by design
    if (!b)
        BOOST_THROW_EXCEPTION(registrar_error(null_kernel));

    kernels_.push_front(b);
}

const std::forward_list<std::shared_ptr<kernel_interface> >&
kernel_registrar::kernels() const {
    return kernels_;
}

} }
