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
#include "dogen/annotations/io/object_io.hpp"
#include "dogen/annotations/types/field_selector.hpp"
#include "dogen/annotations/types/field_instance_factory.hpp"
#include "dogen/stitch/types/traits.hpp"
#include "dogen/stitch/types/expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.expander"));

const std::string stitch_postfix("_stitch.cpp");

}

namespace dogen {
namespace stitch {

void expander::expand(
    const boost::optional<boost::filesystem::path>& template_path,
    annotations::object& o) const {

    BOOST_LOG_SEV(lg, debug) << "Before expansion: " << o;

    if (!template_path) {
        BOOST_LOG_SEV(lg, debug)
            << "No template path supplied so not performing expansion";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Template path: "
                             << template_path->generic_string();

    std::string output_filename(template_path->stem().generic_string());
    output_filename += stitch_postfix;

    const annotations::field_selector fs(o);
    boost::filesystem::path absolute_output_directory;
    if (fs.has_field(traits::relative_output_directory())) {
        const auto tc(fs.get_text_content(traits::relative_output_directory()));
        using namespace boost::filesystem;
        path rel_dir(tc);
        absolute_output_directory = absolute(rel_dir,
            template_path->parent_path());
    } else
        absolute_output_directory = template_path->parent_path();

    absolute_output_directory /= output_filename;

    const annotations::field_instance_factory f;
    const auto v(f.make_text(absolute_output_directory.generic_string()));
    o.fields()[traits::output_path()] = v;

    BOOST_LOG_SEV(lg, debug) << "After expansion: " << o;
}

} }
