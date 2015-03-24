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
#include "dogen/knit/types/backends/cpp_backend.hpp"

namespace dogen {
namespace knit {
namespace backends {

cpp_backend::
cpp_backend(const config::knitting_options& o,
    const dynamic::schema::repository& rp,
    const sml::model& model) :
    transformer_(model, o), formatter_(o),
    model_(model), backend_workflow_(o, rp) { }

backend::ptr cpp_backend::
create(const config::knitting_options& o, const dynamic::schema::repository& rp,
    const sml::model& model) {
    return backend::ptr(new cpp_backend(o, rp, model));
}

backend::value_type cpp_backend::generate() {
    const auto project(transformer_.execute());
    /*const*/ auto r(formatter_.execute(project));

    // FIXME: massive hack for now.
    const bool dump_files(false); // set to true to use new formatters.
    if (dump_files) {
        const auto files(backend_workflow_.execute(model_));
        for (const auto& f : files)
            r[f.path()] = f.content();
    } else
        backend_workflow_.execute(model_);

    return r;
}

std::forward_list<boost::filesystem::path>
cpp_backend::managed_directories() const {
    return transformer_.managed_directories();
}

} } }
