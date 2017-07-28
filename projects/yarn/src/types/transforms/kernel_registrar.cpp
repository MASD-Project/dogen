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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/transforms/registrar_error.hpp"
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/transforms/kernel_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.meta_model.kernel_registrar"));

const std::string no_kernels("No kernels provided.");
const std::string null_kernel("Kernel supplied is null");
const std::string language_taken("Kernel already registered for language: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

void kernel_registrar::register_kernel(std::shared_ptr<kernel_interface> k) {
    if (!k) {
        BOOST_LOG_SEV(lg, error) << null_kernel;
        BOOST_THROW_EXCEPTION(registrar_error(null_kernel));
    }

    const auto l(k->language());
    const auto pair(std::make_pair(l, k));
    const auto inserted(kernels_by_language_.insert(pair).second);
    if (!inserted) {
        std::ostringstream s;
        s << language_taken << l << " kernel: " << k->id();
        const auto msg(s.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(registrar_error(msg));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered kernel: " << k->id();
}

void kernel_registrar::validate() const {
    if (kernels_by_language_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_kernels;
        BOOST_THROW_EXCEPTION(registrar_error(no_kernels));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

std::shared_ptr<kernel_interface> kernel_registrar::
kernel_for_language(const yarn::meta_model::languages l) const {
    const auto i(kernels_by_language_.find(l));
    if (i == kernels_by_language_.end())
        return std::shared_ptr<kernel_interface>();

    return i->second;
}

const std::unordered_map<yarn::meta_model::languages, std::
                         shared_ptr<kernel_interface>>&
kernel_registrar::kernels_by_language() const {
    return kernels_by_language_;
}

} } }
