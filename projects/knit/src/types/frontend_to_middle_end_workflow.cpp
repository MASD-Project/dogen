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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/dynamic/schema/types/workflow.hpp"
#include "dogen/dynamic/expansion/types/workflow.hpp"
#include "dogen/frontend/types/workflow.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/persister.hpp"
#include "dogen/sml/types/workflow.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/backend/types/workflow.hpp"
#include "dogen/knit/types/frontend_to_middle_end_workflow.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.frontend_to_middle_end_workflow"));

const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string target_postfix("_target");
const std::string library_dir("library");
const std::string merged("merged_");
const std::string invalid_archive_type("Invalid or unexpected archive type");
const std::string incorrect_stdout_config(
    "Configuration for output to stdout is incorrect");

}

namespace dogen {
namespace knit {

frontend_to_middle_end_workflow::
frontend_to_middle_end_workflow(const config::knitting_options& o,
    const dynamic::schema::repository& rp)
    : knitting_options_(o), repository_(rp) {}

std::string frontend_to_middle_end_workflow::
extension(config::archive_types at) const {
    using config::archive_types;
    switch (at) {
    case archive_types::xml: return xml_extension;
    case archive_types::text: return text_extension;
    case archive_types::binary: return binary_extension;
    default:
        using dogen::utility::exception::invalid_enum_value;
        BOOST_LOG_SEV(lg, error) << invalid_archive_type;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_archive_type));
    }
}

boost::filesystem::path frontend_to_middle_end_workflow::
create_debug_file_path(const config::archive_types at,
    const boost::filesystem::path& original_path) const {

    const auto& ts(knitting_options_.troubleshooting());
    boost::filesystem::path r(ts.debug_dir());
    r /= original_path.stem().string() + target_postfix;
    r.replace_extension(extension(at));
    return r;
}

std::list<frontend::input_descriptor>
frontend_to_middle_end_workflow::obtain_input_descriptors_activity() const {
    std::list<frontend::input_descriptor> r;
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / library_dir);

    const auto files(find_files(dir));
    BOOST_LOG_SEV(lg, debug) << "Found " << files.size()
                             << " paths to library models.";

    for (const auto& f : files) {
        BOOST_LOG_SEV(lg, debug) << "Library model: " << f.filename();
        frontend::input_descriptor id;
        id.path(f);
        id.is_target(false);
        r.push_back(id);
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating paths to library models.";

    const auto input_options(knitting_options_.input());
    BOOST_LOG_SEV(lg, debug) << "Found " << input_options.references().size()
                             << " paths to reference models.";

    for (const auto ref : input_options.references()) {
        BOOST_LOG_SEV(lg, debug) << "Reference model: "
                                 << ref.path().filename();
        frontend::input_descriptor id;
        id.path(ref.path());
        id.external_module_path(ref.external_module_path());
        id.is_target(false);
        r.push_back(id);
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating paths to reference models.";

    BOOST_LOG_SEV(lg, debug) << "Added target model: "
                             << input_options.target().filename();
    frontend::input_descriptor target;
    target.path(input_options.target());
    target.is_target(true);
    target.external_module_path(input_options.external_module_path());
    r.push_back(target);
    return r;
}

std::list<sml::model> frontend_to_middle_end_workflow::
obtain_partial_sml_models_activity(
    const std::list<frontend::input_descriptor>& descriptors) const {
    frontend::workflow w(knitting_options_, repository_);
    return w.execute(descriptors);
}

boost::filesystem::path frontend_to_middle_end_workflow::
obtain_target_path_activity(
    const std::list<frontend::input_descriptor>& descriptors) const {
    frontend::input_descriptor target_descriptor;
    for (const auto& d : descriptors) {
        if (!d.is_target())
            continue;

        return d.path();
    }
    return boost::filesystem::path();
}

sml::model frontend_to_middle_end_workflow::
merge_models_activity(const std::list<sml::model>& models) const {
    sml::workflow w;
    const auto r(w.execute(models));

    BOOST_LOG_SEV(lg, debug) << "Merged model: " << r;
    BOOST_LOG_SEV(lg, debug) << "Totals: objects: " << r.objects().size()
                             << " modules: " << r.modules().size()
                             << " concepts: " << r.concepts().size()
                             << " enumerations: " << r.enumerations().size()
                             << " primitives: " << r.primitives().size();

    return r;
}

sml::model frontend_to_middle_end_workflow::
expand_model_activity(const sml::model& m) const {
    if (!m.is_expandable()) {
        BOOST_LOG_SEV(lg, debug) << "Model is not expandable, so ignoring it: "
                                 << sml::string_converter::convert(m.name());
        return m;
    }

    dynamic::expansion::workflow w;
    const auto r(w.execute(knitting_options_.cpp(), repository_, m));
    BOOST_LOG_SEV(lg, debug) << "Expanded model: " << r;
    return r;
}

void frontend_to_middle_end_workflow::persist_model_activity(
    const boost::filesystem::path p, const sml::model& m) const {
    const auto& ts(knitting_options_.troubleshooting());
    using config::archive_types;
    archive_types at(ts.save_sml_model());
    if (at == archive_types::invalid)
        return; // FIXME: should we not throw?

    const auto& dp(create_debug_file_path(at, p));
    sml::persister persister;
    persister.persist(m, dp);
}

sml::model frontend_to_middle_end_workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Workflow started.";

    const auto d(obtain_input_descriptors_activity());
    const auto pm(obtain_partial_sml_models_activity(d));
    const auto mm(merge_models_activity(pm));
    const auto r(expand_model_activity(mm));
    const auto tp(obtain_target_path_activity(d));
    persist_model_activity(tp, r);

    BOOST_LOG_SEV(lg, info) << "Workflow finished.";
    return r;
}

} }
