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
#include "dogen/annotations/types/repository_workflow.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/io/file_io.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"
#include "dogen/stitch/types/parser.hpp"
#include "dogen/stitch/types/expander.hpp"
#include "dogen/stitch/types/properties_factory.hpp"
#include "dogen/stitch/types/workflow_error.hpp"
#include "dogen/stitch/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.workflow"));

const std::string annotations_dir("annotations");
const std::string stitch_extension(".stitch");
const std::string no_template_paths("No paths to text templates found.");
const std::string empty_template("Template has no content: ");
const std::string error_in_file("Failed to parse file: ");

}

namespace dogen {
namespace stitch {

workflow::workflow() : formatter_() {}

void workflow::perform_expansion(const boost::filesystem::path& p,
    annotations::annotation& a) const {
    expander e;
    e.expand(p, a);
}

std::forward_list<boost::filesystem::path> workflow::
get_text_template_paths_activity(
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

std::forward_list<std::pair<boost::filesystem::path, std::string> >
workflow::read_text_templates_activity(
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

std::forward_list<annotations::ownership_hierarchy>
workflow::obtain_ownership_hierarchy_activity() const {
    std::forward_list<annotations::ownership_hierarchy> r;
    r.push_front(formatter_.ownership_hierarchy());
    return r;
}

dogen::formatters::repository workflow::
create_formatters_repository_activity() const {
    using dogen::utility::filesystem::data_files_directory;
    std::forward_list<boost::filesystem::path> dirs { data_files_directory() };
    dogen::formatters::hydration_workflow hw;
    return hw.hydrate(dirs);
}

annotations::type_repository workflow::create_annotations_repository_activity(
    const std::forward_list<annotations::ownership_hierarchy>& oh) const {
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / annotations_dir);
    annotations::repository_workflow w;
    return w.execute(oh, std::forward_list<boost::filesystem::path> { dir });
}

std::forward_list<text_template> workflow::parse_text_templates_activity(
    const annotations::type_repository& rp,
    const std::forward_list<std::pair<boost::filesystem::path, std::string> >&
    text_templates_as_string) const {
    std::forward_list<text_template> r;
    const annotations::annotation_groups_factory f(rp);
    const parser p(f);
    for (const auto& pair : text_templates_as_string) {
        BOOST_LOG_SEV(lg, debug) << "Parsing file: "
                                 << pair.first.generic_string();
        try {
            auto tt(p.parse(pair.second));
            perform_expansion(pair.first, tt.annotation());
            r.push_front(tt);
        } catch(boost::exception& e) {
            e << error_in_file(pair.first.generic_string());
            throw;
        }
    }

    return r;
}

void workflow::populate_properties_activity(
    const annotations::type_repository& annotations_repository,
    const dogen::formatters::repository& formatters_repository,
    std::forward_list<text_template>& text_templates) const {

    properties_factory f(annotations_repository, formatters_repository);
    for (auto& tt : text_templates)
        tt.properties(f.make(tt.annotation()));
}

std::forward_list<formatters::file> workflow::format_text_templates_activity(
    const std::forward_list<text_template>& text_templates) const {
    std::forward_list<formatters::file> r;
    for (const auto& tt : text_templates)
        r.push_front(formatter_.format(tt));
    return r;
}

void workflow::
write_files_activity(const std::forward_list<formatters::file>& files) const {
    BOOST_LOG_SEV(lg, debug) << "Files: " << files;
    formatters::filesystem_writer w(false/*force_write*/);
    w.write(files);
}

void workflow::execute(const boost::filesystem::path& p) const {
    BOOST_LOG_SEV(lg, debug) << "Executing workflow against: "
                             << p.generic_string();

    const auto paths(get_text_template_paths_activity(p));
    validate_text_template_paths(paths);

    const auto templates_as_strings(read_text_templates_activity(paths));
    const auto oh(obtain_ownership_hierarchy_activity());
    const auto annotations_rp(create_annotations_repository_activity(oh));

    auto tt(parse_text_templates_activity(annotations_rp, templates_as_strings));
    const auto formatters_rp(create_formatters_repository_activity());
    populate_properties_activity(annotations_rp, formatters_rp, tt);
    const auto files(format_text_templates_activity(tt));
    write_files_activity(files);

    BOOST_LOG_SEV(lg, debug) << "Finished executing workflow.";
}

} }
