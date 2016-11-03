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
#include <list>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/annotations/types/type_repository_factory.hpp"
#include "dogen/annotations/types/archetype_location_repository_factory.hpp"
#include "dogen/options/types/knitting_options_validator.hpp"
#include "dogen/options/io/knitting_options_io.hpp"
#include "dogen/yarn/types/workflow.hpp"
#include "dogen/formatters/types/formatting_error.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"
#include "dogen/quilt/types/workflow.hpp"
#include "dogen/knit/types/workflow_error.hpp"
#include "dogen/knit/types/housekeeper.hpp"
#include "dogen/knit/types/workflow.hpp"

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.workflow"));

const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string target_postfix("_target");
const std::string merged("merged_");
const std::string invalid_archive_type("Invalid or unexpected archive type");
const std::string incorrect_stdout_options(
    "Configuration for output to stdout is incorrect");
const std::string code_generation_failure("Code generation failure.");

}

namespace dogen {
namespace knit {

workflow::workflow(workflow&& rhs)
    : knitting_options_(std::move(rhs.knitting_options_)) { }

workflow::
workflow(const options::knitting_options& o) : knitting_options_(o) {
    options::knitting_options_validator v;
    v.validate(knitting_options_);
}

bool workflow::housekeeping_required() const {
    return knitting_options_.output().delete_extra_files();
}

std::vector<boost::filesystem::path> workflow::obtain_data_dirs() const {
    using namespace dogen::utility::filesystem;
    const auto data_dir(dogen::utility::filesystem::data_files_directory());
    return std::vector<boost::filesystem::path>({ data_dir });
}

annotations::archetype_location_repository workflow::
obtain_archetype_location_repository() const {
    std::list<annotations::archetype_location> als;
    const auto& rg(quilt::workflow::registrar());
    for (const auto b : rg.backends())
        for (const auto al : b->archetype_location())
            als.push_back(al);

    annotations::archetype_location_repository_factory f;
    const auto r(f.make(als));
    return r;
}

annotations::type_repository workflow::setup_annotations_repository(
    const std::vector<boost::filesystem::path>& data_dirs,
    const annotations::archetype_location_repository& alrp) const {
    annotations::type_repository_factory f;
    return f.make(alrp, data_dirs);
}

annotations::annotation_groups_factory
workflow::create_annotation_groups_factory(
    const std::vector<boost::filesystem::path>& data_dirs,
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp) const {
    annotations::annotation_groups_factory r(data_dirs, alrp, atrp);
    return r;
}

yarn::model workflow::
obtain_yarn_model(const std::vector<boost::filesystem::path>& data_dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp) const {
    yarn::workflow w;
    const auto io(knitting_options_.input());
    return w.execute(data_dirs, agf, atrp, io);
}

void workflow::perform_housekeeping(
    const std::forward_list<formatters::artefact>& artefacts,
    const std::forward_list<boost::filesystem::path>& dirs) const {

    std::set<boost::filesystem::path> expected_files;
    for (const auto a : artefacts) {
        expected_files.insert(a.path().generic_string());
        for (const auto& d : a.dependencies())
            expected_files.insert(d.generic_string());
    }

    const auto& ip(knitting_options_.output().ignore_patterns());
    std::forward_list<std::string> ignore_patterns(ip.begin(), ip.end());
    housekeeper hk(ignore_patterns, dirs, expected_files);
    hk.tidy_up();
}

std::shared_ptr<dogen::formatters::artefact_writer_interface>
workflow::obtain_file_writer() const {
    const options::output_options& options(knitting_options_.output());
    const auto fw(options.force_write());

    using dogen::formatters::filesystem_writer;
    return std::make_shared<filesystem_writer>(fw);
}

void workflow::write_files(
    std::shared_ptr<dogen::formatters::artefact_writer_interface> writer,
    const std::forward_list<formatters::artefact>& artefacts) const {

    if (artefacts.empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, so no output.";
        return;
    }

    writer->write(artefacts);
}

void workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Starting.";
    BOOST_LOG_SEV(lg, info) << "Knitting options: " << knitting_options_;

    try {
        const auto data_dirs(obtain_data_dirs());
        const auto alrp(obtain_archetype_location_repository());
        const auto atrp(setup_annotations_repository(data_dirs, alrp));
        const auto agf(create_annotation_groups_factory(data_dirs, alrp, atrp));
        const auto m(obtain_yarn_model(data_dirs, agf, atrp));

        if (!m.has_generatable_types()) {
            BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
            return;
        }

        quilt::workflow w(knitting_options_, atrp, agf);
        const auto artefacts(w.execute(m));

        const auto writer(obtain_file_writer());
        write_files(writer, artefacts);

        if (housekeeping_required()) {
            const auto md(w.managed_directories(m));
            perform_housekeeping(artefacts, md);
        }
    } catch(const dogen::formatters::formatting_error& e) {
        BOOST_THROW_EXCEPTION(workflow_error(e.what()));
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Finished.";
}

} }
