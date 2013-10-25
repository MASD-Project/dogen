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
#include "dogen/sml/types/tag_adaptor.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/tag_adaptor.hpp"
#include "dogen/sml/types/all_types_traversal.hpp"
#include "dogen/om/types/code_generation_marker_factory.hpp"
#include "dogen/om/io/modeline_group_io.hpp"
#include "dogen/om/types/hydration_workflow.hpp"
#include "dogen/om/types/modeline_group_hydrator.hpp"
#include "dogen/om/io/licence_io.hpp"
#include "dogen/om/types/licence_hydrator.hpp"
#include "dogen/om/types/code_generation_marker_factory.hpp"
#include "dogen/sml/types/property_cache.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/types/modeline_group.hpp"
#include "dogen/om/types/workflow_error.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"
#include "dogen/om/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.workflow"));
const std::string missing_context_ptr("Context pointer is null");
const std::string modeline_groups_dir("modeline_groups");
const std::string licence_dir("licences");
const std::string missing_licence("Licence not found: ");
const std::string missing_modeline_group("Modeline group not found: ");
const std::string missing_modeline("Modeline not found: ");
const std::string cpp_modeline_name("c++");
}

namespace dogen {
namespace om {

class workflow::context {
public:
    sml::property_cache& property_cache() {
        return property_cache_;
    }

    const std::unordered_map<std::string, modeline_group>& modeline_groups() {
        return modeline_groups_;
    }

    void modeline_groups(
        const std::unordered_map<std::string, modeline_group>& v) {
        modeline_groups_ = v;
    }

    const std::unordered_map<std::string, licence>& licences() const {
        return licences_;
    }

    void licences(const std::unordered_map<std::string, licence>& v) {
        licences_ = v;
    }

    std::string code_generation_marker() {
        return code_generation_marker_;
    }

    void code_generation_marker(const std::string& v) {
        code_generation_marker_ = v;
    }

    std::list<file>& files() { return files_; }

private:
    sml::property_cache property_cache_;
    std::unordered_map<std::string, modeline_group> modeline_groups_;
    std::unordered_map<std::string, licence> licences_;
    std::string code_generation_marker_;
    std::list<file> files_;
};

workflow::
workflow(const std::list<boost::filesystem::path>& data_files_directories)
    : data_files_directories_(data_files_directories) { }

void workflow::ensure_non_null_context() const {
    if (context_ != nullptr)
        return;

    BOOST_LOG_SEV(lg, error) << missing_context_ptr;
    BOOST_THROW_EXCEPTION(workflow_error(missing_context_ptr));
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

void workflow::hydrate_licences_activity(const sml::model& m) {
    std::list<std::string> copyright_holders;
    const auto i(m.complex_tags().find(sml::tags::copyright_holder));
    if (i != m.complex_tags().end())
        copyright_holders = i->second;

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
    hydrate_licences_activity(m);
    create_marker_activity(m);
    context_->property_cache().populate(m);
}

void workflow::operator()(const sml::type& t) const {
    ensure_non_null_context();
    auto adaptor(sml::make_tag_adaptor(t));

    const auto licence_name(adaptor.get(sml::tags::licence_name));
    const auto i(context_->licences().find(licence_name));
    if (i == context_->licences().end()) {
        BOOST_LOG_SEV(lg, error) << missing_licence << licence_name;
        BOOST_THROW_EXCEPTION(workflow_error(missing_licence + licence_name));
    }
    auto licence(i->second);
    if (adaptor.has_key(sml::tags::copyright_holder)) {
        const auto copyright_holder(adaptor.get(sml::tags::copyright_holder));
        licence.copyright_holders().push_back(copyright_holder);
    }

    const auto modeline_group_name(adaptor.get(sml::tags::modeline_group_name));
    const auto j(context_->modeline_groups().find(modeline_group_name));
    if (j == context_->modeline_groups().end()) {
        BOOST_LOG_SEV(lg, error) << missing_modeline_group
                                 << modeline_group_name;
        BOOST_THROW_EXCEPTION(
            workflow_error(missing_modeline_group + modeline_group_name));
    }

    const auto modeline_group(j->second);
    const auto k(modeline_group.modelines().find(cpp_modeline_name));
    if (k == modeline_group.modelines().end()) {
        BOOST_LOG_SEV(lg, error) << missing_modeline << cpp_modeline_name;
        BOOST_THROW_EXCEPTION(
            workflow_error(missing_modeline + cpp_modeline_name));
    }
    const auto modeline(k->second);
    const auto cgm(adaptor.get(sml::tags::code_generation_marker));

    cpp_types_main_header_file_formatter f;
    const auto& pc(context_->property_cache());
    const auto file(f.format(t, licence, modeline, cgm, pc));
    context_->files().push_back(file);
}

void workflow::operator()(const sml::module& /*m*/) const {
    ensure_non_null_context();
}

void workflow::operator()(const sml::concept& /*c*/) const {
    // do nothing
}

std::list<file> workflow::execute(const sml::model& m) {
    context_ = std::shared_ptr<context>(new context());
    setup_reference_data_subworkflow(m);
    sml::all_model_items_traversal(m, *this);
    const auto r(context_->files());
    context_ = std::shared_ptr<context>();
    return r;
}

} }
