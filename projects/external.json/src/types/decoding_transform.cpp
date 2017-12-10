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
#include "dogen/utility/log/logger.hpp"
#include "dogen/probing/types/scoped_prober.hpp"
#include "dogen/external/types/transforms/context.hpp"
#include "dogen/external/io/meta_model/model_io.hpp"
#include "dogen/external/types/transforms/transformation_error.hpp"
#include "dogen/external.json/types/new_hydrator.hpp"
#include "dogen/external.json/types/decoding_transform.hpp"

namespace {

using namespace dogen::utility::log;
const std::string transform_id("external.json.decoding_transform");
auto lg(logger_factory(transform_id));

const std::string extension(".json");

}

namespace dogen {
namespace external {
namespace json {

decoding_transform::~decoding_transform() noexcept {}

std::string decoding_transform::extension() const {
    return ::extension;
}

meta_model::model decoding_transform::transform(const transforms::context& ctx,
    const boost::filesystem::path& p) {
    const auto model_name(p.filename().string());
    probing::scoped_transform_prober stp(lg, "JSON decoding transform",
        transform_id, model_name, ctx.prober());

    new_hydrator h;
    const auto r(h.hydrate(p));

    stp.end_transform(r);
    return r;
}

} } }
