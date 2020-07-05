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
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/entities/artefact_set.hpp"
#include "dogen.text/io/entities/model_set_io.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/text_model_to_physical_model_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.text_model_to_physical_model_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string duplicate_archetype(
    "Found more than one artefact for archetype:");
const std::string duplicate_logical_element(
    "Found more than one artefact set for logical model ID: ");

}

namespace dogen::orchestration::transforms {

physical::entities::model_set
text_model_to_physical_model_transform::apply(const text::transforms::context& ctx,
    const text::entities::model_set& ms) {
    tracing::scoped_transform_tracer stp(lg, "logical to text model transform",
        transform_id, ms.name().qualified().dot(), *ctx.tracer(), ms);

    physical::entities::model_set r;
    for (const auto& m : ms.models()) {
        physical::entities::model pm;
        pm.logical_name().simple(m.name().simple());
        pm.logical_name().qualified(m.name().qualified().dot());
        pm.origin_sha1_hash(m.origin_sha1_hash());
        pm.name().simple(m.name().simple());
        pm.name().qualified(m.name().qualified().dot());
        pm.configuration(m.root_module()->configuration());
        pm.managed_directories(m.managed_directories());

        for (const auto& ea : m.elements()) {
            const auto& e(*ea.element());
            const auto logical_element_id(e.name().qualified().dot());

            physical::entities::artefact_set as;
            as.logical_element_id(logical_element_id);

            for (const auto& pair : ea.artefacts()) {
                const auto archetype_id(pair.first);
                const auto aptr(pair.second);
                /*
                 * FIXME: mega-hack: prune empty artefacts. This is
                 * needed for now because of how stitch templates are
                 * handled; if we do not have a template, we are
                 * producing blank artefacts with empty path and
                 * contents. This will be addressed with T2T
                 * transforms.
                 */
                const auto& p(aptr->name().qualified());
                if (!p.empty()) {
                    auto& aba(as.artefacts_by_archetype());
                    const auto pair(std::make_pair(archetype_id, aptr));
                    const bool inserted(aba.insert(pair).second);
                    if (!inserted) {
                        BOOST_LOG_SEV(lg, error) << duplicate_archetype
                                                 << archetype_id;
                        BOOST_THROW_EXCEPTION(transform_exception(
                                duplicate_archetype + archetype_id));
                    }
                }
            }

            if (!as.artefacts_by_archetype().empty()) {
                auto& asbli(pm.artefact_sets_by_logical_id());
                const auto& leid(as.logical_element_id());
                auto pair(std::make_pair(leid, as));
                const bool inserted(asbli.insert(pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_logical_element
                                             << leid;
                    BOOST_THROW_EXCEPTION(transform_exception(
                            duplicate_logical_element + leid));
                }
            }
        }
        r.models().push_back(pm);
    }
    return r;
}

}
