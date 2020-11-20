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
#include "dogen.text/types/transforms/cpp/cpp_factory.hpp"
#include "dogen.text/types/transforms/cpp/testing_factory.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.text/types/transforms/cpp/implementation_factory.hpp"
#include "dogen.text/types/transforms/cpp/public_headers_factory.hpp"
#include "dogen.text/types/transforms/cpp/standard_header_file_factory.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"

namespace dogen::text::transforms::cpp {
namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dogen.text.transforms.cpp"));

}

physical::entities::backend cpp_factory::make() {
    identification::helpers::physical_meta_name_builder b;
    b.meta_model("masd");
    b.backend("cpp");

    physical::entities::backend r;
    r.meta_name(b.build());
    r.directory_name("cpp");
    r.labels().push_back(identification::entities::label("test", "lbl"));

    const auto ak_inserter([&](const auto& ak) {
        const auto pair(std::make_pair(ak.id(), ak));
        const auto inserted(r.archetype_kinds().insert(pair).second);
        if (!inserted) {
            using text::transforms::transformation_error;
            const std::string duplicate_facet("Duplicate archetype kind: ");
            BOOST_LOG_SEV(lg, error) << duplicate_facet << ak.id();
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_facet + ak.id()));
        }
    });
    ak_inserter(standard_header_file_factory::make());

    const auto part_inserter([&](const auto& part) {
        const auto id(part.meta_name().id());
        const auto pair(std::make_pair(id, part));
        const auto inserted(r.parts().insert(pair).second);
        if (!inserted) {
            using text::transforms::transformation_error;
            const std::string duplicate_facet("Duplicate part: ");
            BOOST_LOG_SEV(lg, error) << duplicate_facet << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_facet + id.value()));
        }
    });
    part_inserter(implementation_factory::make());
    part_inserter(public_headers_factory::make());
    part_inserter(testing_factory::make());
    return r;
}

}

