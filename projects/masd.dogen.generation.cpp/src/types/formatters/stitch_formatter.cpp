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
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/formatters/stitch_formatter.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formatters.stitch_formatter"));

const std::string empty;
const std::string stitch_extension(".stitch");
const std::string decoration_preamble_key(
    "masd.generation.decoration.preamble");
const std::string decoration_postamble_key(
    "masd.generation.decoration.postamble");

}

namespace masd::dogen::generation::cpp::formatters {

stitch_formatter::stitch_formatter(const annotations::type_repository& atrp,
    const annotations::annotation_factory& af,
    const annotations::annotation_expander& ae,
    const dogen::extraction::repository& frp)
    : instantiator_(atrp, af, ae, frp) {}

bool stitch_formatter::is_header(const inclusion_support_types ist) const {
    return
        ist == inclusion_support_types::regular_support ||
        ist == inclusion_support_types::canonical_support;
}

extraction::meta_model::artefact stitch_formatter::
format(const artefact_formatter_interface& stock_formatter, const context& ctx,
    const coding::meta_model::element& e) const {
    const auto al(stock_formatter.archetype_location());
    const auto needs_guard(is_header(stock_formatter.inclusion_support_type()));

    assistant a(ctx, e, al, needs_guard);
    const auto& fp(a.artefact_properties().file_path());
    auto stitch_template(fp);
    stitch_template.replace_extension(stitch_extension);

    /*
     * If the template does not yet exist, we should just create an
     * empty artefact.
     *
     * This scenario happens when creating a new model or when adding
     * a new artefact formatter for the first time.
     */
    if (!boost::filesystem::exists(stitch_template)) {
        BOOST_LOG_SEV(lg, debug) << "Stitch template not found: "
                                 << fp.generic_string();

        extraction::meta_model::artefact r;
        // FIXME: what is the name/path for the artefact?! This may
        // FIXME: explain empty artefacts!
        r.overwrite(a.new_artefact_properties().overwrite());

        extraction::meta_model::operation op;
        using ot = extraction::meta_model::operation_type;
        op.type(r.overwrite() ? ot::write : ot::create_only);
        r.operation(op);

        return r;
    }

    /*
     * Since the template exists, we can instantiate it.
     */
    const auto external_keys = std::unordered_map<std::string, std::string> {
        {
            decoration_preamble_key,
            e.decoration() ?  e.decoration()->preamble() : empty
        },
        {
            decoration_postamble_key,
            e.decoration() ?  e.decoration()->postamble() : empty
        },
    };

    auto r(instantiator_.instantiate(stitch_template, external_keys));
    r.overwrite(a.new_artefact_properties().overwrite());

    extraction::meta_model::operation op;
    using ot = extraction::meta_model::operation_type;
    op.type(r.overwrite() ? ot::write : ot::create_only);
    r.operation(op);

    r.dependencies().push_back(stitch_template);
    return r;
}

}
