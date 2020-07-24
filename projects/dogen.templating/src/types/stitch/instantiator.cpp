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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.templating/types/wale/instantiator.hpp"
#include "dogen.templating/types/helpers/kvp_validator.hpp"
#include "dogen.templating/types/stitch/instantiation_error.hpp"
#include "dogen.templating/types/stitch/parser.hpp"
#include "dogen.templating/types/stitch/properties.hpp"
#include "dogen.templating/types/stitch/formatter.hpp"
#include "dogen.templating/types/stitch/features.hpp"
#include "dogen.templating/types/stitch/instantiator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("templating.stitch.instantiator"));

const std::string wale_key("stitch.wale.template_instantiation_result");

const std::string empty_template("Template has no content: ");
const std::string duplicate_variable("Attempt to insert duplicate variable: ");
const std::string duplicate_key("Attempt to insert duplicate key: ");

}

namespace dogen::templating::stitch {

instantiator::
instantiator(const boost::filesystem::path& wale_templates_directory,
    const variability::entities::feature_model& fm,
    const variability::helpers::configuration_factory& cf)
    : wale_templates_directory_(wale_templates_directory),
      configuration_factory_(cf), feature_model_(fm) {}

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

void instantiator::update_expected_keys(text_template& tt) const {
    /*
     * Locate all variable blocks and extract the variable names from
     * them. Put these in the expected keys container.
     */
    auto& e(tt.expected_keys());
    for (const auto& l : tt.body().lines()) {
        for (const auto& b : l.blocks()) {
            if (b.type() == block_types::variable_block)
                e.insert(b.content());
        }
    }
}

void instantiator::handle_wale_template(text_template& tt) const {
    /*
     * Check if we have an associated wale template. If we don't,
     * there is nothing to do here.
     */
    const auto& props(tt.properties());
    const auto& wt(props.wale_template());
    if (wt.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No wale template supplied.";
        return;
    }
    const auto p(wale_templates_directory_ / wt);
    BOOST_LOG_SEV(lg, debug) << "Instantiating wale template: "
                             << props.wale_template() << ". Path: "
                             << p.generic_string();
    BOOST_LOG_SEV(lg, debug) << "Stitching properties kvps: "
                             << props.wale_kvps();

    /*
     * Execute the wale instantiation and store the result as a stitch
     * variable.
     */
    wale::instantiator inst;
    const auto wale_value(inst.instantiate(p, props.wale_kvps()));
    const auto pair(std::make_pair(wale_key, wale_value));
    const auto inserted(tt.supplied_kvps().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_variable << wale_key;
        BOOST_THROW_EXCEPTION(
            instantiation_error(duplicate_variable + wale_key));
    }
}

void instantiator::
merge_kvps(const std::unordered_map<std::string, std::string>& kvps,
    text_template& tt) const {

    for (const auto& pair : kvps) {
        const auto inserted(tt.supplied_kvps().insert(pair).second);
        if (!inserted) {
            const auto& k(pair.first);
            BOOST_LOG_SEV(lg, error) << duplicate_key << k;
            BOOST_THROW_EXCEPTION(instantiation_error(duplicate_key + k));
        }
    }
}

void instantiator::validate_kvps(text_template& tt) const {
    helpers::kvp_validator v;
    v.validate(tt.expected_keys(), tt.supplied_kvps());
}

properties instantiator::create_properties(
    const variability::entities::configuration& cfg) const {
    const auto fg(features::make_feature_group(feature_model_));
    const auto scfg(features::make_static_configuration(fg, cfg));

    properties r;
    r.stream_variable_name(scfg.stream_variable_name);
    r.inclusion_dependencies(scfg.inclusion_dependency);

    using utility::string::splitter;
    const auto cns(splitter::split_scoped(scfg.containing_namespaces));
    r.containing_namespaces(cns);

    r.wale_template(scfg.text_template);
    for (const auto& pair : scfg.kvp)
        r.wale_kvps()[pair.first] = pair.second;

    return r;
}

text_template
instantiator::create_text_template(const std::string& text_template_as_string,
    const std::unordered_map<std::string, std::string>& kvps) const {

    BOOST_LOG_SEV(lg, debug) << "Processing template.";

    /*
     * We first start by parsing the raw text templates into their
     * domain representation. This only populates the lines and
     * tagged values portions of the text template.
     */
    parser p;
    text_template r;
    r.body(p.parse(text_template_as_string));

    /*
     * Merge in all of the externally supplied KVPs, if any.
     */
    if (!kvps.empty())
        merge_kvps(kvps, r);

    /*
     * Get all of the variables used by the template.
     */
    update_expected_keys(r);

    /*
     * Convert the tagged values into an annotation, which
     * performs a profile expansion as required. We then take that
     * annotation object and use it to generate the properties.
     *
     * Note that we do not support configuration overrides on
     * stitch templates at present, so we just default them to
     * empty.
     */
    const auto& tvs(r.body().tagged_values());
    const std::list<identification::entities::tagged_value> otvs;
    const auto bp(variability::entities::binding_point::global);
    const auto cfg(configuration_factory_.make(tvs, otvs, bp));
    r.properties(create_properties(cfg));

    /*
     * Perform the required processing for wale templates.
     */
    handle_wale_template(r);

    /*
     * Ensure that all referenced variables are present in the KVP
     * map.
     */
    validate_kvps(r);
    return r;
}

std::string instantiator::format_text_template(const text_template& tt) const {
    formatter fmt;
    const auto r(fmt.format(tt));
    return r;
}

std::string instantiator::instantiate(const std::string& input,
    const std::unordered_map<std::string, std::string>& kvps) const {
    BOOST_LOG_SEV(lg, debug) << "Instantiating string.";

    const auto tt(create_text_template(input, kvps));
    const auto r(format_text_template(tt));

    BOOST_LOG_SEV(lg, debug) << "Instantiated.";
    return r;
}

std::string instantiator::instantiate(const boost::filesystem::path& input_path,
    const std::unordered_map<std::string, std::string>& kvps) const {
    BOOST_LOG_SEV(lg, debug) << "Instantiating: "
                             << input_path.generic_string();

    try {
        const auto s(read_text_template(input_path));
        const auto tt(create_text_template(s, kvps));
        const auto r(format_text_template(tt));

        BOOST_LOG_SEV(lg, debug) << "Instantiated. Path: "
                                 <<  input_path.generic_string();
        return r;
    } catch(boost::exception& e) {
        e << error_in_file(input_path.generic_string());
        throw;
    }
}

}
