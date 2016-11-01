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
#include <boost/throw_exception.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/stitch/types/instantiation_error.hpp"
#include "dogen/stitch/types/parser.hpp"
#include "dogen/stitch/types/properties.hpp"
#include "dogen/stitch/types/formatter.hpp"
#include "dogen/stitch/types/instantiator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.instantiator"));

const std::string stitch_postfix("_stitch.cpp");

const std::string empty_template("Template has no content: ");

}

namespace dogen {
namespace stitch {

instantiator::instantiator(const annotations::annotation_groups_factory& af,
    const properties_factory& pf)
    : annotation_factory_(af), properties_factory_(pf) {}

boost::filesystem::path
instantiator::compute_output_path(const boost::filesystem::path& input_path,
    const properties& props) const {

    boost::filesystem::path r;
    const auto& sp(props.stitching_properties());
    if (!sp.relative_output_directory().empty()) {
        using namespace boost::filesystem;
        path rel_dir(sp.relative_output_directory());
        r = absolute(rel_dir, input_path.parent_path());
    } else
        r = input_path.parent_path();

    std::string output_filename(input_path.stem().generic_string());
    output_filename += stitch_postfix;
    r /= output_filename;

    return r;
}

std::string instantiator::
read_text_template(const boost::filesystem::path& input_path) const {
    using utility::filesystem::read_file_content;
    const auto r(read_file_content(input_path));
    if (r.empty()) {
        const auto gs(input_path.generic_string());
        BOOST_LOG_SEV(lg, error) << empty_template << gs;
        BOOST_THROW_EXCEPTION(instantiation_error(empty_template + gs));
    }
    return r;
}

text_template
instantiator::create_text_template(const boost::filesystem::path& input_path,
    const std::string& text_template_as_string) const {

    parser p;
    BOOST_LOG_SEV(lg, debug) << "Processing: " << input_path.generic_string();

    try {
        /*
         * We first start by parsing the raw text templates into
         * their domain representation. This only populates the
         * lines and scribble group portions of the text
         * template.
         */
        text_template r;
        r.body(p.parse(text_template_as_string));

        /*
         * The input path is the location from where we read the
         * template.
         */
        r.input_path(input_path);

        /*
         * We then convert the scribble group into annotations,
         * which performs a profile expansion as required. We then
         * take that annotation object and use it to generate the
         * properties.
         */
        const auto& sgrp(r.body().scribble_group());
        const auto ag(annotation_factory_.make(sgrp));
        const auto& a(ag.parent());
        r.properties(properties_factory_.make(a));

        /*
         * Finally, we compute an output path for our template,
         * taking into account its input path and any relevant
         * options set by the user.
         */
        r.output_path(compute_output_path(input_path, r.properties()));

        return r;
    } catch(boost::exception& e) {
        e << error_in_file(input_path.generic_string());
        throw;
    }
}

formatters::artefact
instantiator::format_text_template(const text_template& tt) const {
    formatter fmt;
    const auto r(fmt.format(tt));
    return r;
}

formatters::artefact
instantiator::instantiate(const boost::filesystem::path& input_path) const {
    BOOST_LOG_SEV(lg, debug) << "Instantiating: "
                             << input_path.generic_string();

    const auto s(read_text_template(input_path));
    const auto tt(create_text_template(input_path, s));
    const auto r(format_text_template(tt));

    BOOST_LOG_SEV(lg, debug) << "Instantiated.";

    return r;
}

} }
