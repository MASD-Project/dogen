/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/engine/types/backends/cpp_backend.hpp"

namespace dogen {
namespace engine {
namespace backends {

cpp_backend::
cpp_backend(const sml::model& model, const config::cpp_settings& settings) :
    transformer_(model, settings), formatter_(settings) { }

backend::ptr cpp_backend::
create(const sml::model& model, const config::cpp_settings& settings) {
    return backend::ptr(new cpp_backend(model, settings));
}

backend::value_type cpp_backend::generate() {
    const auto project(transformer_.execute());
    const auto r(formatter_.execute(project));
    return r;
}

std::vector<boost::filesystem::path> cpp_backend::managed_directories() const {
    return transformer_.managed_directories();
}

} } }
