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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.injection.org_mode/types/dehydrator.hpp"
#include "dogen.injection.org_mode/types/encoding_transform.hpp"

namespace {

using namespace dogen::utility::log;
const std::string transform_id("injection.org_mode.encoding_transform");
auto lg(logger_factory(transform_id));

const std::string encoder_id("injection.org_mode");
const std::string description("Encodes diagrams as Org Mode documents.");
const std::string extension(".org");

}

namespace dogen::injection::org_mode {

encoding_transform::~encoding_transform() noexcept {}

std::string encoding_transform::id() const {
    return ::encoder_id;
}

std::string encoding_transform::description() const {
    return ::description;
}

std::string encoding_transform::extension() const {
    return ::extension;
}

void encoding_transform::
apply(const transforms::context& ctx, const entities::model& m,
    const boost::filesystem::path& p) {
    tracing::scoped_transform_tracer stp(lg, "Org Mode encoding transform",
        transform_id, m.name(), *ctx.tracer());

    dehydrator::dehydrate(m, p);
}

}
