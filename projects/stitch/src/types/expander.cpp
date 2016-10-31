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
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/annotation_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/stitch/types/traits.hpp"
#include "dogen/stitch/types/expander.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.expander"));

const std::string stitch_postfix("_stitch.cpp");

}

namespace dogen {
namespace stitch {

annotations::annotation_group expander::create_annotation_group(
    const annotations::annotation_groups_factory& factory,
    const text_template& tt) const {
    const auto& sgrp(tt.scribble_group());
    return factory.make(sgrp);
}

properties expander::create_properties(
    const annotations::type_repository& annotations_repository,
    const dogen::formatters::repository& formatters_repository,
    const annotations::annotation& a) const {
    properties_factory f(annotations_repository, formatters_repository);
    return f.make(a);
}

boost::filesystem::path expander::compute_output_path(
    const boost::optional<boost::filesystem::path>& template_path,
    const annotations::annotation& a) const {

    boost::filesystem::path r;
    const annotations::entry_selector s(a);
    if (s.has_entry(traits::relative_output_directory())) {
        const auto tc(s.get_text_content(traits::relative_output_directory()));
        using namespace boost::filesystem;
        path rel_dir(tc);
        r = absolute(rel_dir, template_path->parent_path());
    } else
        r = template_path->parent_path();

    std::string output_filename(template_path->stem().generic_string());
    output_filename += stitch_postfix;
    r /= output_filename;

    return r;
}

void expander::
expand(const boost::optional<boost::filesystem::path>& template_path,
        const annotations::type_repository& atrp,
        const dogen::formatters::repository& frp,
        const annotations::annotation_groups_factory& factory,
        text_template& tt) const {

    const auto ag(create_annotation_group(factory, tt));
    const auto& a(ag.parent());

    tt.properties(create_properties(atrp, frp, a));

    if (template_path) {
        tt.output_path(compute_output_path(template_path, a));
        BOOST_LOG_SEV(lg, debug) << "Output path: "
                                 << tt.output_path().generic_string();
    } else
        BOOST_LOG_SEV(lg, debug) << "No template path, not setting output path";
}

} }
