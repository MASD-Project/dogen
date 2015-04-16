/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/stitch/types/traits.hpp"
#include "dogen/stitch/types/expander.hpp"

namespace {

const std::string stitch_postfix("_stitch.cpp");
}


namespace dogen {
namespace stitch {

void expander::expand(
    const boost::optional<boost::filesystem::path>& template_path,
    dynamic::schema::object& o) const {

    if (!template_path)
        return;

    std::string output_filename(template_path->filename().generic_string());
    output_filename += stitch_postfix;

    const dynamic::schema::field_selector fs(o);
    boost::filesystem::path absolute_output_directory;
    if (fs.has_field(traits::relative_output_directory())) {
        const auto tc(fs.get_text_content(traits::relative_output_directory()));
        using namespace boost::filesystem;
        path rel_dir(tc);
        absolute_output_directory = absolute(rel_dir, *template_path);
    } else
        absolute_output_directory = template_path->parent_path();

    absolute_output_directory /= output_filename;

    const dynamic::schema::field_instance_factory f;
    const auto v(f.make_text(absolute_output_directory.generic_string()));
    o.fields()[traits::output_path()] = v;
}

} }
