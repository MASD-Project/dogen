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
#include <list>
#include "dogen/sml/types/type.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/sml/types/tag_adaptor.hpp"
#include "dogen/sml/types/all_types_traversal.hpp"
#include "dogen/om/types/code_generation_marker_factory.hpp"
#include "dogen/om/io/modeline_group_io.hpp"
#include "dogen/om/types/hydration_workflow.hpp"
#include "dogen/om/types/modeline_group_hydrator.hpp"
#include "dogen/om/io/licence_io.hpp"
#include "dogen/om/types/licence_hydrator.hpp"
#include "dogen/om/types/code_generation_marker_factory.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"

#include "dogen/om/types/workflow_error.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"
#include "dogen/om/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.workflow"));
const std::string missing_context_ptr("Context pointer is null");
const std::string modeline_groups_dir("modeline_groups");
const std::string licence_dir("licences");

}

namespace dogen {
namespace om {

workflow::
workflow(const std::list<boost::filesystem::path>& data_files_directories)
    : data_files_directories_(data_files_directories) { }

void workflow::ensure_non_null_context() const {
    if (context_ != nullptr)
        return;

    BOOST_LOG_SEV(lg, error) << missing_context_ptr;
    BOOST_THROW_EXCEPTION(workflow_error(missing_context_ptr));
}

void workflow::
throw_missing_item(const std::string& msg, const std::string& n) const {
    BOOST_LOG_SEV(lg, error) << msg << n;
    BOOST_THROW_EXCEPTION(workflow_error(msg + n));
}

std::list<boost::filesystem::path>
workflow::create_directories(const std::string for_whom) const {
    std::list<boost::filesystem::path> r;
    for (const auto& d : data_files_directories_)
        r.push_back(d / for_whom);
    return r;
}

void workflow::hydrate_modelines_activity() {
    const auto dirs(create_directories(modeline_groups_dir));
    hydration_workflow<modeline_group_hydrator> hw;
    context_->modeline_groups(hw.hydrate(dirs));

    BOOST_LOG_SEV(lg, info) << "Loaded modeline groups. Found: "
                            << context_->modeline_groups().size();
    BOOST_LOG_SEV(lg, debug) << "contents: " << context_->modeline_groups();
}

void workflow::hydrate_licences_activity() {
    std::list<std::string> copyright_holders;
    licence_hydrator lh(copyright_holders);
    const auto dirs(create_directories(licence_dir));
    hydration_workflow<licence_hydrator> hw(lh);
    context_->licences(hw.hydrate(dirs));

    BOOST_LOG_SEV(lg, info) << "Loaded licences. Found: "
                            << context_->licences().size();
    BOOST_LOG_SEV(lg, debug) << "contents: " << context_->licences();
}

void workflow::create_marker_activity(const sml::model& m) {
    auto adaptor(sml::make_tag_adaptor(m));

    const bool add_date_time(
        adaptor.is_true(sml::tags::code_generation_marker::add_date_time));

    const bool add_warning(
        adaptor.is_true(sml::tags::code_generation_marker::add_warning));

    const std::string message(
        adaptor.get(sml::tags::code_generation_marker::message));

    code_generation_marker_factory f(add_date_time, add_warning, message);
    context_->code_generation_marker(f.build());
}

void workflow::setup_reference_data_subworkflow(const sml::model& m) {
    ensure_non_null_context();

    hydrate_modelines_activity();
    hydrate_licences_activity();
    create_marker_activity(m);
    context_->property_cache().populate(m);
}

void workflow::operator()(const sml::type& t) const {
    ensure_non_null_context();
    auto licence(extract_licence(t));
    const auto modeline(extract_modeline(t));
    const auto marker(extract_marker(t));

    cpp_types_main_header_file_formatter f;
    const auto& pc(context_->property_cache());
    const auto file(f.format(t, licence, modeline, marker, pc));
    context_->files().push_back(file);
}

void workflow::operator()(const sml::module& m) const {
    ensure_non_null_context();

    auto licence(extract_licence(m));
    const auto modeline(extract_modeline(m));
    const auto marker(extract_marker(m));

    cpp_types_main_header_file_formatter f;
    const auto file(f.format(m, licence, modeline, marker));
    context_->files().push_back(file);
}

void workflow::operator()(const sml::concept& /*c*/) const {
    // do nothing
}

void workflow::model_file_subworkflow(const sml::model& model) {
    if (model.documentation().empty())
        return;

    sml::module module;
    module.name().simple_name(model.name().model_name());
    module.name().external_module_path(model.name().external_module_path());
    module.documentation(model.documentation());
    module.meta_data(model.meta_data());
    operator()(module);
}

std::list<file> workflow::execute(const sml::model& m) {
    context_ = std::unique_ptr<context>(new context());
    setup_reference_data_subworkflow(m);
    sml::all_model_items_traversal(m, *this);
    model_file_subworkflow(m);
    const auto r(context_->files());
    context_ = std::unique_ptr<context>();
    return r;
}

} }
