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
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen.annotations/types/type_repository_factory.hpp"
#include "dogen.annotations/types/archetype_location_repository_builder.hpp"
#include "dogen.formatters/types/repository_factory.hpp"
#include "dogen/yarn/io/meta_model/artefact_io.hpp"
#include "dogen/yarn/types/helpers/filesystem_writer.hpp"
#include "dogen.stitch/types/parser.hpp"
#include "dogen.stitch/types/properties_factory.hpp"
#include "dogen.stitch/types/instantiator.hpp"
#include "dogen.stitch/types/formatter.hpp"
#include "dogen.stitch/types/workflow_error.hpp"
#include "dogen.stitch/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.workflow"));

const std::string annotations_dir("annotations");
const std::string stitch_extension(".stitch");
const std::string stitch_postfix("_stitch.cpp");

const std::string no_template_paths("No paths to text templates found.");
const std::string empty_template("Template has no content: ");
const std::string error_in_file("Failed to parse file: ");

}

namespace dogen {
namespace stitch {

workflow::workflow(const bool compatibility_mode)
    : compatibility_mode_(compatibility_mode) {}

std::vector<boost::filesystem::path>
workflow::create_data_directories() const {
    const auto data_dir(dogen::utility::filesystem::data_files_directory());
    return std::vector<boost::filesystem::path> { data_dir };
}

std::forward_list<boost::filesystem::path> workflow::
get_text_template_paths(
    const boost::filesystem::path& file_or_directory) const {
    std::forward_list<boost::filesystem::path> r;
    if (boost::filesystem::is_directory(file_or_directory)) {
        using utility::filesystem::find_files;
        const auto candidates(find_files(file_or_directory));
        for (const auto& candidate : candidates) {
            const auto extension(candidate.extension());
            if (extension.generic_string() == stitch_extension)
                r.push_front(candidate);
        }
        return r;
    }

    const auto extension(file_or_directory.extension());
    if (extension.generic_string() == stitch_extension)
        r.push_front(file_or_directory);

    return r;
}

void workflow::
validate_text_template_paths(const std::forward_list<boost::filesystem::path>&
    text_template_paths) const {
    if (text_template_paths.empty()) {
        BOOST_LOG_SEV(lg, error) << no_template_paths;
        BOOST_THROW_EXCEPTION(workflow_error(no_template_paths));
    }
}

annotations::archetype_location_repository
workflow::obtain_archetype_location_repository() const {
    std::list<annotations::archetype_location> als;
    formatter fmt;
    als.push_back(fmt.archetype_location());

    annotations::archetype_location_repository_builder b;
    b.add(als);
    return b.build();
}

dogen::formatters::repository workflow::create_formatters_repository(
    const std::vector<boost::filesystem::path>& data_dirs) const {
    dogen::formatters::repository_factory f;
    return f.make(data_dirs);
}

annotations::type_repository workflow::create_annotations_type_repository(
    const std::vector<boost::filesystem::path>& data_dirs,
    const annotations::archetype_location_repository& alrp) const {
    annotations::type_repository_factory f;
    return f.make(alrp, data_dirs);
}

std::list<yarn::meta_model::artefact>
workflow::create_artefacts(const annotations::type_repository& atrp,
    const annotations::annotation_factory& af,
    const dogen::formatters::repository& drp, const std::forward_list<
    boost::filesystem::path>& text_template_paths) const {

    std::list<yarn::meta_model::artefact> r;
    const instantiator inst(atrp, af, drp);
    for (const auto& p : text_template_paths)
        r.push_front(inst.instantiate(p));

    return r;
}

void workflow::
write_artefacts(const std::list<yarn::meta_model::artefact>& artefacts) const {
    BOOST_LOG_SEV(lg, debug) << "About to write. Artefacts: " << artefacts;

    yarn::helpers::filesystem_writer w(false/*force_write*/);
    w.write(artefacts);

    BOOST_LOG_SEV(lg, debug) << "Finished writing.";
}

void workflow::execute(const boost::filesystem::path& p) const {
    BOOST_LOG_SEV(lg, debug) << "Executing workflow against: "
                             << p.generic_string();

    const auto paths(get_text_template_paths(p));
    validate_text_template_paths(paths);

    const auto alrp(obtain_archetype_location_repository());
    const auto data_dirs(create_data_directories());
    const auto atrp(create_annotations_type_repository(data_dirs, alrp));

    const auto cm(compatibility_mode_);
    const auto frp(create_formatters_repository(data_dirs));
    annotations::annotation_factory af(data_dirs, alrp, atrp, cm);
    properties_factory pf(atrp, frp);
    const auto artefacts(create_artefacts(atrp, af, frp, paths));
    write_artefacts(artefacts);

    BOOST_LOG_SEV(lg, debug) << "Finished executing workflow.";
}

} }
