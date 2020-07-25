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
#include "dogen.identification/types/entities/sha1_hash.hpp"
#include "dogen.utility/types/hash/sha1_hasher.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/sha1_hash_io.hpp"
#include "dogen.injection/io/entities/model_io.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.injection/types/transforms/provenance_transform.hpp"

namespace {

const std::string transform_id("injection.transforms.provenance_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::injection::transforms {

identification::entities::sha1_hash provenance_transform::
compute_shah1_hash(const boost::filesystem::path& p) {
    const auto s(utility::filesystem::read_file_content(p));
    BOOST_LOG_SEV(lg, debug) << "File: " << p.generic_string()
                             << " size: " << s.size();

    using identification::entities::sha1_hash;
    const auto r(sha1_hash(utility::hash::sha1_hasher(s)));
    BOOST_LOG_SEV(lg, debug) << "Hash for file: " << r;
    return r;
}

void provenance_transform::apply(const transforms::context& ctx,
    const boost::filesystem::path& p, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "provenance transform",
        transform_id, m.name().simple(), *ctx.tracer(), m);

    /*
     * Update model's provenance properties.
     */
    auto& mp(m.provenance());
    mp.model_sha1_hash(compute_shah1_hash(p));
    using identification::entities::model_type;
    mp.model_type(model_type::not_yet_determined);

    /*
     * Update elements provenance with the models properties.
     */
    for (auto& e : m.elements())
        e.provenance(mp);

    stp.end_transform(m);
}

}
