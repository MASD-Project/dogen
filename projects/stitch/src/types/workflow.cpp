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
#include "dogen/annotations/types/type_repository_factory.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/annotations/types/archetype_location_repository_factory.hpp"
#include "dogen/formatters/types/repository_factory.hpp"
#include "dogen/formatters/io/artefact_io.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"
#include "dogen/stitch/types/parser.hpp"
#include "dogen/stitch/types/properties_factory.hpp"
#include "dogen/stitch/types/workflow_error.hpp"
#include "dogen/stitch/types/workflow.hpp"

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

workflow::workflow() : formatter_() {}

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

boost::filesystem::path
workflow::compute_output_path(const boost::filesystem::path& template_path,
    const properties& props) const {

    boost::filesystem::path r;
    const auto& sp(props.stitching_properties());
    if (!sp.relative_output_directory().empty()) {
        using namespace boost::filesystem;
        path rel_dir(sp.relative_output_directory());
        r = absolute(rel_dir, template_path.parent_path());
    } else
        r = template_path.parent_path();

    std::string output_filename(template_path.stem().generic_string());
    output_filename += stitch_postfix;
    r /= output_filename;

    return r;
}


std::forward_list<std::pair<boost::filesystem::path, std::string> >
workflow::read_text_templates(
    const std::forward_list<boost::filesystem::path>&
    text_template_paths) const {
    std::forward_list<std::pair<boost::filesystem::path, std::string> > r;
    for (const auto& path : text_template_paths) {
        using utility::filesystem::read_file_content;
        const auto content(read_file_content(path));
        if (content.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_template << path.generic_string();
            BOOST_THROW_EXCEPTION(
                workflow_error(empty_template + path.generic_string()));
        }
        r.push_front(std::make_pair(path, content));
    }
    return r;
}

annotations::archetype_location_repository
workflow::obtain_archetype_location_repository() const {
    std::list<annotations::archetype_location> als;
    als.push_back(formatter_.ownership_hierarchy());

    annotations::archetype_location_repository_factory f;
    const auto r(f.make(als));
    return r;
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

std::forward_list<text_template> workflow::create_text_templates(
    const annotations::annotation_groups_factory& af,
    const properties_factory& pf,
    const std::forward_list<std::pair<boost::filesystem::path, std::string> >&
    text_templates_as_string) const {
    std::forward_list<text_template> r;
    parser p;

    for (const auto& pair : text_templates_as_string) {
        const auto& path(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing: " << path.generic_string();

        try {
            /*
             * We first start by parsing the raw text templates into
             * their domain representation. This only populates the
             * lines and scribble group portions of the text
             * template.
             */
            const auto& text_template_as_string(pair.second);
            auto tt(p.parse(text_template_as_string));

            /*
             * The template path is simply the location from where we
             * read it.
             */
            tt.template_path(path);

            /*
             * We then convert the scribble group into annotations,
             * which performs a profile expansion as required. We then
             * take that annotation object and use it to generate the
             * properties.
             */
            const auto& sgrp(tt.scribble_group());
            const auto ag(af.make(sgrp));
            const auto& a(ag.parent());
            tt.properties(pf.make(a));

            /*
             * Finally, we compute an output path for our template,
             * taking into account its input path and any relevant
             * options set by the user.
             */
            tt.output_path(compute_output_path(path, tt.properties()));

            r.push_front(tt);
        } catch(boost::exception& e) {
            e << error_in_file(pair.first.generic_string());
            throw;
        }
    }

    return r;
}

std::forward_list<formatters::artefact> workflow::format_text_templates(
    const std::forward_list<text_template>& text_templates) const {
    std::forward_list<formatters::artefact> r;
    for (const auto& tt : text_templates)
        r.push_front(formatter_.format(tt));
    return r;
}

void workflow::write_artefacts(
    const std::forward_list<formatters::artefact>& artefacts) const {
    BOOST_LOG_SEV(lg, debug) << "Artefacts: " << artefacts;
    formatters::filesystem_writer w(false/*force_write*/);
    w.write(artefacts);
}

void workflow::execute(const boost::filesystem::path& p) const {
    BOOST_LOG_SEV(lg, debug) << "Executing workflow against: "
                             << p.generic_string();

    const auto paths(get_text_template_paths(p));
    validate_text_template_paths(paths);
    const auto templates_as_strings(read_text_templates(paths));

    const auto alrp(obtain_archetype_location_repository());
    const auto data_dirs(create_data_directories());
    const auto atrp(create_annotations_type_repository(data_dirs, alrp));

    const auto frp(create_formatters_repository(data_dirs));
    annotations::annotation_groups_factory af(data_dirs, alrp, atrp);
    properties_factory pf(atrp, frp);
    const auto tts(create_text_templates(af, pf, templates_as_strings));

    const auto artefacts(format_text_templates(tts));
    write_artefacts(artefacts);

    BOOST_LOG_SEV(lg, debug) << "Finished executing workflow.";
}

} }
