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
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.engine/types/transforms/context_factory.hpp"
#include "dogen.engine/types/transforms/scoped_context_manager.hpp"

namespace dogen::engine::transforms {

scoped_context_manager::scoped_context_manager(
    const configuration& cfg,
    const std::string& activity,
    const boost::filesystem::path& output_directory) :
    context_(context_factory::make_context(cfg, activity, output_directory)) {}

scoped_context_manager::~scoped_context_manager() {
    if (context_.injection_context().tracer())
        context_.injection_context().tracer()->end_run();
}

const transforms::context& scoped_context_manager::context() const {
    return context_;
}

scoped_injection_context_manager::scoped_injection_context_manager(
    const configuration& cfg, const std::string& activity) :
    context_(context_factory::make_injection_context(cfg, activity)) {}

scoped_injection_context_manager::~scoped_injection_context_manager() {
    if (context_.tracer())
        context_.tracer()->end_run();
}

const injection::transforms::context&
scoped_injection_context_manager::context() const {
    return context_;
}

}
