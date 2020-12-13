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
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/file_to_artefact_transform.hpp"

namespace {

const std::string transform_id("codec.transforms.file_to_artefact_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const char dot('.');

}

namespace dogen::codec::transforms {

entities::artefact file_to_artefact_transform::
apply(const transforms::context& ctx, const boost::filesystem::path& p) {
    const auto fn(p.filename().stem());
    entities::artefact r;
    tracing::scoped_transform_tracer stp(lg, "file to artefact",
        transform_id, fn.stem().generic_string(), *ctx.tracer(), r);

    r.path(p);
    r.content(utility::filesystem::read_file_content(p));

    /*
     * Remove leading dot from extension, if any exists, and make the
     * resulting string the codec type.
     */
    const auto ext(fn.extension().generic_string());
    const auto starts_with_dot(!ext.empty() && ext[0] == dot);
    r.codec_name(starts_with_dot ? ext.substr(1) : ext);

    stp.end_transform(r);

    return r;
}

}
