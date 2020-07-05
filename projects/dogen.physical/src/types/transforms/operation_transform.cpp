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
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/io/entities/operation_type_io.hpp"
#include "dogen.physical/io/helpers/files_by_status_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/helpers/file_status_collector.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/operation_transform.hpp"

namespace {

const std::string transform_id(
    "physical.transforms.operation_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string unexpected_operation(
    "Operation not expected by transform: ");
const std::string empty_file_name("Empty file name supplied.");

}

namespace dogen::physical::transforms {

void operation_transform::
apply(entities::artefact& a, const bool force_write) {
    const auto p(a.name().qualified());
    const auto gs(p.generic());
    BOOST_LOG_SEV(lg, trace) << "Processing: " << gs;

    if (p.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_file_name;
        BOOST_THROW_EXCEPTION(transform_exception(empty_file_name));
    }

    /*
     * We only expect artefacts with a limited range of operation
     * types. If this artefact is aksing for anything else, throw.
     */
    using physical::entities::operation_type;
    const auto ot(a.operation().type());
    if (ot != operation_type::create_only && ot != operation_type::write) {
        const auto s(boost::lexical_cast<std::string>(ot));
        BOOST_LOG_SEV(lg, error) << unexpected_operation << ot;
        BOOST_THROW_EXCEPTION(
            transform_exception(unexpected_operation + s));
    }

    /*
     * If the file does not yet exist, it must be a newly
     * generated file. If the user requested create only, we can
     * safely bump it to write.
     */
    using physical::entities::operation_reason;
    if (!boost::filesystem::exists(p)) {
        a.operation().type(operation_type::write);
        a.operation().reason(operation_reason::newly_generated);
        BOOST_LOG_SEV(lg, trace) << "File does not yet exist for artefact.";
        return;
    }

    /*
     * The file already exists. Check to see if the user requested
     * to create it only if it doesn't yet exist; if so, we are
     * now safe to ignore it.
     */
    if (ot == operation_type::create_only) {
        a.operation().type(operation_type::ignore);
        a.operation().reason(operation_reason::already_exists);
        BOOST_LOG_SEV(lg, trace) << "Ignoring file as it is create only.";
        return;
    }

    /*
     * If the user requested force write, we should always write
     * regardlesss of contents. However, note that this does not
     * apply to create only, which has already been handled above.
     */
    if (force_write) {
        a.operation().reason(operation_reason::force_write);
        BOOST_LOG_SEV(lg, trace) << "Force write is on so writing.";
        return;
    }

    /*
     * Check if there is a need to write or not. For this we
     * perform a binary diff of the file content; if it has
     * changed, we need to write.
     */
    using dogen::utility::filesystem::read_file_content;
    const std::string c(read_file_content(p));
    if (c == a.content()) {
        a.operation().type(operation_type::ignore);
        a.operation().reason(operation_reason::unchanged_generated);
        BOOST_LOG_SEV(lg, trace) << "File contents have not changed.";
        return;
    }

    /*
     * The last scenario is a generated file which has been
     * changed.
     */
    BOOST_LOG_SEV(lg, trace) << "File contents have changed.";
    a.operation().reason(operation_reason::changed_generated);

}

void operation_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "operation transform", transform_id, m.name().simple(),
        *ctx.tracer(), m);

    for (auto& as_pair : m.artefact_sets_by_logical_id()) {
        auto& as(as_pair.second);
        for (auto& a_pair : as.artefacts_by_archetype()) {
            auto& a(*a_pair.second);
            apply(a, m.outputting_properties().force_write());
        }
    }

    for (const auto& aptr : m.orphan_artefacts()) {
        auto& a(*aptr);
        apply(a, m.outputting_properties().force_write());
    }

    stp.end_transform(m);
}

}
