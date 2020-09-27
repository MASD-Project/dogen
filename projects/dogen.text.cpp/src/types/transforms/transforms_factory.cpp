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
#include "dogen.text.cpp/types/transforms/io/io_factory.hpp"
#include "dogen.text.cpp/types/transforms/odb/odb_factory.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text.cpp/types/transforms/hash/hash_factory.hpp"
#include "dogen.text.cpp/types/transforms/transforms_factory.hpp"
#include "dogen.text.cpp/types/transforms/build/build_factory.hpp"
#include "dogen.text.cpp/types/transforms/tests/tests_factory.hpp"
#include "dogen.text.cpp/types/transforms/types/types_factory.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.text.cpp/types/transforms/templates/templates_factory.hpp"
#include "dogen.text.cpp/types/transforms/test_data/test_data_factory.hpp"
#include "dogen.text.cpp/types/transforms/standard_header_file_factory.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"
#include "dogen.text.cpp/types/transforms/lexical_cast/lexical_cast_factory.hpp"
#include "dogen.text.cpp/types/transforms/serialization/serialization_factory.hpp"
#include "dogen.text.cpp/types/transforms/visual_studio/visual_studio_factory.hpp"

namespace dogen::text::cpp::transforms {
namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dogen.text.cpp.transforms"));

}

physical::entities::backend transforms_factory::make() {
    identification::helpers::physical_meta_name_builder b;
    b.meta_model("masd");
    b.backend("cpp");

    physical::entities::backend r;
    r.meta_name(b.build());
    r.directory_name("cpp");
    r.labels().push_back(identification::entities::label("test", "lbl"));

    const auto fct_inserter([&](const auto& fct) {
        const auto id(fct.meta_name().id());
        const auto pair(std::make_pair(id, fct));
        const auto inserted(r.facets().insert(pair).second);
        if (!inserted) {
            using text::transforms::transformation_error;
            const std::string duplicate_facet("Duplicate facet: ");
            BOOST_LOG_SEV(lg, error) << duplicate_facet << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_facet + id.value()));
        }
    });

    fct_inserter(build::build_factory::make());
    fct_inserter(hash::hash_factory::make());
    fct_inserter(io::io_factory::make());
    fct_inserter(lexical_cast::lexical_cast_factory::make());
    fct_inserter(odb::odb_factory::make());
    fct_inserter(serialization::serialization_factory::make());
    fct_inserter(templates::templates_factory::make());
    fct_inserter(test_data::test_data_factory::make());
    fct_inserter(tests::tests_factory::make());
    fct_inserter(types::types_factory::make());
    fct_inserter(visual_studio::visual_studio_factory::make());

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
    return r;
}

}

