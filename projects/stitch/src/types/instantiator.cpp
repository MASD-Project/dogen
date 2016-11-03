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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/io/annotation_io.hpp"
#include "dogen/wale/types/workflow.hpp"
#include "dogen/stitch/types/instantiation_error.hpp"
#include "dogen/stitch/types/parser.hpp"
#include "dogen/stitch/types/properties.hpp"
#include "dogen/stitch/types/formatter.hpp"
#include "dogen/stitch/types/instantiator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.instantiator"));

const std::string stitch_postfix(".cpp");
const std::string wale_key("stitch.wale.template_instantiation_result");

const std::string empty_template("Template has no content: ");
const std::string duplicate_variable("Attempt to insert duplicate variable: ");

}

namespace dogen {
namespace stitch {

instantiator::instantiator(const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& agf,
    const dogen::formatters::repository& frp)
    : annotation_factory_(agf), properties_factory_(atrp, frp) {}

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
    // FIXME: compute extension based on properties
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

void instantiator::handle_wale_template(const std::unordered_map<std::string,
    std::string>& external_kvps, text_template& tt) const {

    /*
     * Check if we have an associated wale template. If we don't,
     * there is nothing to do here.
     */
    const auto st(tt.properties().stitching_properties());
    const auto wt(st.wale_template());
    if (wt.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No wale template supplied.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Instantiating wale template: "
                             << st.wale_template();
    BOOST_LOG_SEV(lg, debug) << "Stitching properties kvps: "
                             << st.wale_kvps();

    /*
     * Execute the wale workflow and store the result as a stitch
     * variable. Note that the external kvps take precedence over the
     * internal kvps. This is somewhat arbitrary, and was chosen so
     * that we could move the templates from "internal" to "external"
     * kvps, one template at a time. Once this work is completed, we
     * probably should throw if both are present as this seems like a
     * mistake.
     */
    wale::workflow wkf;
    const auto& kvps(external_kvps.empty() ? st.wale_kvps() : external_kvps);
    const auto wale_value(wkf.execute(wt, kvps));
    const auto pair(std::make_pair(wale_key, wale_value));
    const auto inserted(tt.variables().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_variable << wale_key;
        BOOST_THROW_EXCEPTION(
            instantiation_error(duplicate_variable + wale_key));
    }
}

text_template
instantiator::create_text_template(const boost::filesystem::path& input_path,
    const std::string& text_template_as_string,
    const std::unordered_map<std::string, std::string>& wale_kvps) const {

    BOOST_LOG_SEV(lg, debug) << "Processing: " << input_path.generic_string();

    text_template r;
    try {
        /*
         * We first start by parsing the raw text templates into
         * their domain representation. This only populates the
         * lines and scribble group portions of the text
         * template.
         */
        parser p;
        r.body(p.parse(text_template_as_string));

        /*
         * The input path is the location from where we read the
         * template.
         */
        r.input_path(input_path);

        /*
         * Convert the scribble group into annotations, which performs
         * a profile expansion as required. We then take that
         * annotation object and use it to generate the properties.
         */
        const auto& sgrp(r.body().scribble_group());
        const auto ag(annotation_factory_.make(sgrp));
        const auto& a(ag.parent());
        BOOST_LOG_SEV(lg, debug) << "Annotation: " << a;
        r.properties(properties_factory_.make(a));

        /*
         * Perform the required processing for wale templates.
         */
        handle_wale_template(wale_kvps, r);

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
instantiator::instantiate(const boost::filesystem::path& input_path,
    const std::unordered_map<std::string, std::string>& wale_kvps) const {
    BOOST_LOG_SEV(lg, debug) << "Instantiating: "
                             << input_path.generic_string();

    const auto s(read_text_template(input_path));
    const auto tt(create_text_template(input_path, s, wale_kvps));
    const auto r(format_text_template(tt));

    BOOST_LOG_SEV(lg, debug) << "Instantiated.";

    return r;
}

} }
