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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec.json/types/hydrator.hpp"
#include "dogen.codec.json/types/decoding_transform.hpp"

namespace {

using namespace dogen::utility::log;
const std::string transform_id("codec.json.decoding_transform");
auto lg(logger_factory(transform_id));

const std::string decoder_id("codec.json");
const std::string description("Decodes diagrams in JSON format.");
const std::string extension(".json");

}

namespace dogen::codec::json {

decoding_transform::~decoding_transform() noexcept {}

std::string decoding_transform::id() const {
    return ::decoder_id;
}

std::string decoding_transform::description() const {
    return ::description;
}

std::string decoding_transform::extension() const {
    return ::extension;
}

entities::model decoding_transform::apply(const transforms::context& ctx,
    const boost::filesystem::path& p) {
    const auto model_name(p.filename().string());
    tracing::scoped_transform_tracer stp(lg, "JSON decoding transform",
        transform_id, model_name, *ctx.tracer());

    hydrator h;
    const auto r(h.hydrate(p));

    stp.end_transform(r);
    return r;
}

}
