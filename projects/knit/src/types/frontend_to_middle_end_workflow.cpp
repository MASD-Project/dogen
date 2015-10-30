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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/yarn/types/persister.hpp"
#include "dogen/yarn/types/assembler.hpp"
#include "dogen/yarn/types/frontend_workflow.hpp"
#include "dogen/yarn/io/model_io.hpp"
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
    const dynamic::repository& rp)
    : knitting_options_(o), repository_(rp) {}

std::list<yarn::input_descriptor>
frontend_to_middle_end_workflow::obtain_input_descriptors_activity() const {
    std::list<yarn::input_descriptor> r;
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / library_dir);

    const auto files(find_files(dir));
    BOOST_LOG_SEV(lg, debug) << "Found " << files.size()
                             << " paths to library models.";

    for (const auto& f : files) {
        BOOST_LOG_SEV(lg, debug) << "Library model: " << f.filename();
        yarn::input_descriptor id;
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
        yarn::input_descriptor id;
        id.path(ref.path());
        id.external_module_path(ref.external_module_path());
        id.is_target(false);
        r.push_back(id);
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating paths to reference models.";

    BOOST_LOG_SEV(lg, debug) << "Added target model: "
                             << input_options.target().path();
    yarn::input_descriptor target;
    target.path(input_options.target().path());
    target.is_target(true);
    target.external_module_path(input_options.target().external_module_path());
    r.push_back(target);
    return r;
}

std::list<yarn::model> frontend_to_middle_end_workflow::
import_yarn_models_activity(
    const std::list<yarn::input_descriptor>& descriptors) const {
    yarn::frontend_workflow w(repository_);
    return w.execute(descriptors);
}

boost::filesystem::path frontend_to_middle_end_workflow::
obtain_target_path_activity(
    const std::list<yarn::input_descriptor>& descriptors) const {
    yarn::input_descriptor target_descriptor;
    for (const auto& d : descriptors) {
        if (!d.is_target())
            continue;

        return d.path();
    }
    return boost::filesystem::path();
}

yarn::model frontend_to_middle_end_workflow::
assemble_yarn_models_activity(const std::list<yarn::model>& models) const {
    yarn::assembler a;
    const auto r(a.assemble(models));

    BOOST_LOG_SEV(lg, debug) << "Assembled model: " << r;
    BOOST_LOG_SEV(lg, debug) << "Totals: objects: " << r.objects().size()
                             << " modules: " << r.modules().size()
                             << " concepts: " << r.concepts().size()
                             << " enumerations: " << r.enumerations().size()
                             << " primitives: " << r.primitives().size();

    return r;
}

yarn::model frontend_to_middle_end_workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Workflow started.";

    const auto d(obtain_input_descriptors_activity());
    const auto pm(import_yarn_models_activity(d));
    const auto r(assemble_yarn_models_activity(pm));
    const auto tp(obtain_target_path_activity(d));

    BOOST_LOG_SEV(lg, info) << "Workflow finished.";
    return r;
}

} }
