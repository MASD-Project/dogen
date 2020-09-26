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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/stitch_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.transforms.stitch_transform"));

const std::string empty;
const std::string stitch_extension(".stitch");
const std::string decoration_preamble_key(
    "masd.decoration.preamble");
const std::string decoration_postamble_key(
    "masd.decoration.postamble");

}

namespace dogen::text::cpp::transforms {

stitch_transform::stitch_transform(
    const formattables::locator& l,
    const variability::entities::feature_model& fm,
    const variability::helpers::configuration_factory& cf)
    : instantiator_(l.templates_project_path(), fm, cf) {}

bool stitch_transform::is_header(const inclusion_support_types ist) const {
    return
        ist == inclusion_support_types::regular_support ||
        ist == inclusion_support_types::canonical_support;
}

void stitch_transform::apply(const model_to_text_transform& stock_transform,
    const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    const auto pn(stock_transform.archetype().meta_name());
    const auto needs_guard(is_header(stock_transform.inclusion_support_type()));

    assistant ast(ctx, e, pn, needs_guard, a);
    const auto& fp(ast.artefact_properties().file_path());
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

        // FIXME: mega-hack: do not populate the path if the
        // artchetype is going to be empty. This will trigger
        // filtering later.
        // a.name().qualified(fp);

        physical::entities::operation op;
        using ot = physical::entities::operation_type;
        const bool overwrite(a.enablement_properties().overwrite());
        op.type(overwrite ? ot::write : ot::create_only);
        a.operation(op);
        return;
    }

    /*
     * Since the template exists, we can instantiate it.
     */
    const auto ts(identification::entities::technical_space::cpp);
    const auto i(e.decoration().find(ts));
    auto dec(i->second);
    const auto external_keys = std::unordered_map<std::string, std::string> {
        {
            decoration_preamble_key, dec ? dec->preamble() : empty
        },
        {
            decoration_postamble_key, dec ? dec->postamble() : empty
        }
    };

    a.name().simple(fp.filename().generic_string());
    a.name().id(identification::entities::physical_id(fp.generic_string()));
    a.file_path(fp);
    a.content(instantiator_.instantiate(stitch_template, external_keys));

    physical::entities::operation op;
    using ot = physical::entities::operation_type;
    const bool overwrite(a.enablement_properties().overwrite());
    op.type(overwrite ? ot::write : ot::create_only);
    a.operation(op);

    a.dependencies().push_back(stitch_template);
}

}
