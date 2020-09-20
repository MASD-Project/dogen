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
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/transforms/mock_content_filler_transform.hpp"

namespace {

const std::string transform_id(
    "physical.transforms.mock_content_filler_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

std::string create_hacked_contents(const std::string file_name) {
    std::ostringstream ss;

    ss << "// dummy function to suppress ranlib warnings" << std::endl
       << "void " << file_name << "() { }"
       << std::endl;

    return ss.str();
}

std::list<boost::shared_ptr<dogen::physical::entities::artefact>>
gather_artefacts(const dogen::physical::entities::model& m) {
    std::list<boost::shared_ptr<dogen::physical::entities::artefact>>  r;
    for (const auto& pr_pair : m.regions_by_logical_id()) {
        const auto& pr(pr_pair.second);
        for (const auto& a_pair : pr.artefacts_by_archetype())
            r.push_back(a_pair.second);
    }

    for (const auto& a : m.orphan_artefacts())
        r.push_back(a);

    return r;
}

}

namespace dogen::physical::transforms {

void mock_content_filler_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "mock content filler transform", transform_id, m.name().simple(),
        *ctx.tracer());

    auto artefacts(gather_artefacts(m));
    for (auto& ptr : artefacts) {
        auto& a(*ptr);
        if (!a.content().empty())
            continue;

        const auto& fp(a.file_path());
        if (fp.extension() != ".cpp")
            continue;

        const auto gs(fp.generic_string());
        BOOST_LOG_SEV(lg, debug) << "File requires mock content: " << gs;
        const auto fn(fp.stem().generic_string());
        a.content(create_hacked_contents(fn));
    }
}

}
