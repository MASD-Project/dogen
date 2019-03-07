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
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.orchestration/types/transforms/context_factory.hpp"
#include "masd.dogen.orchestration/types/transforms/scoped_context_owner.hpp"

namespace masd::dogen::orchestration::transforms {

scoped_context_owner::scoped_context_owner(
    const configuration& cfg,
    const boost::filesystem::path& output_directory) :
    context_(context_factory::make_context(cfg, output_directory)) {}

scoped_context_owner::~scoped_context_owner() {
    if (context_.injection_context().tracer())
        context_.injection_context().tracer()->end_tracing();
}

const transforms::context& scoped_context_owner::context() const {
    return context_;
}

}
