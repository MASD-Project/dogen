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
#include "dogen/stitch/types/workflow.hpp"

namespace dogen {
namespace stitch {

std::list<boost::filesystem::path> workflow::
get_text_template_paths_activity(
    const boost::filesystem::path& /*file_or_directory*/) const {
    std::list<boost::filesystem::path> r;
    return r;
}

std::list<std::string> workflow::read_text_templates_activity(
    const std::list<boost::filesystem::path>& /*text_template_paths*/) const {
    std::list<std::string> r;
    return r;
}

std::forward_list<dynamic::schema::ownership_hierarchy>
workflow::obtain_ownership_hierarchy_activity() const {
    std::forward_list<dynamic::schema::ownership_hierarchy> r;
    return r;
}

dynamic::schema::repository workflow::setup_schema_repository_activity(
    const std::forward_list<dynamic::schema::ownership_hierarchy>& /*oh*/)
    const {
    dynamic::schema::repository r;
    return r;
}

std::list<text_template> workflow::parse_text_templates_activity(
    const std::list<std::string>& /*text_templates_as_string*/) const {
    std::list<text_template> r;
    return r;
}

std::list<text_template> workflow::obtain_settings_bundle_activity(
    const std::list<text_template>& /*text_template*/) const {
    std::list<text_template> r;
    return r;
}

std::list<formatters::file> workflow::format_text_templates_activity(
    const std::list<text_template>& /*text_templates*/) const {
    std::list<formatters::file> r;
    return r;
}

void workflow::output_files_activity(
    const std::list<formatters::file>& /*files*/) const {
}

void workflow::execute(const boost::filesystem::path& /*p*/) const {
}

} }
