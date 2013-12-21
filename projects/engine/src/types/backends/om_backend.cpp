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
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/engine/types/backends/om_backend.hpp"

using dogen::utility::filesystem::data_files_directory;

namespace dogen {
namespace engine {
namespace backends {

om_backend::om_backend(const sml::model& model) :
    model_(model),
    workflow_(std::list<boost::filesystem::path>{data_files_directory()}) { }

backend::ptr om_backend::
create(const sml::model& model) {
    return backend::ptr(new om_backend(model));
}

backend::value_type om_backend::generate() {
    const auto files(workflow_.execute(model_));

    backend::value_type r;
    for (const auto& f : files)
        r.insert(std::make_pair(f.full_path(), f.contents()));

    return r;
}

std::vector<boost::filesystem::path> om_backend::managed_directories() const {
    std::vector<boost::filesystem::path> r;
    return r;
}

} } }
