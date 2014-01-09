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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/sml/types/all_types_traversal.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/om/types/formatter_factory.hpp"
#include "dogen/om/types/code_generation_marker_factory.hpp"
#include "dogen/om/types/workflow_error.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"
#include "dogen/om/types/type_formatter_interface.hpp"
#include "dogen/om/types/module_formatter_interface.hpp"
#include "dogen/om/types/concept_formatter_interface.hpp"
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

class workflow::context {
public:
    std::list<file>& files() { return files_; }

    void type_formatters(
        const std::list<boost::shared_ptr<type_formatter_interface> >& v) {
        type_formatters_ = v;
    }
    const std::list<boost::shared_ptr<type_formatter_interface> >&
    type_formatters() { return type_formatters_; }

    void module_formatters(
        const std::list<boost::shared_ptr<module_formatter_interface> >& v) {
        module_formatters_ = v;
    }
    const std::list<boost::shared_ptr<module_formatter_interface> >&
    module_formatters() { return module_formatters_; }

    void concept_formatters(
        const std::list<boost::shared_ptr<concept_formatter_interface> >& v) {
        concept_formatters_ = v;
    }

    const std::list<boost::shared_ptr<concept_formatter_interface> >&
    concept_formatters() { return concept_formatters_; }

private:
    std::list<file> files_;
    std::list<boost::shared_ptr<type_formatter_interface> >
    type_formatters_;
    std::list<boost::shared_ptr<module_formatter_interface> >
    module_formatters_;
    std::list<boost::shared_ptr<concept_formatter_interface> >
    concept_formatters_;
};

workflow::workflow(const boost::filesystem::path& project_directory,
    const boost::filesystem::path& cpp_source_directory,
    const boost::filesystem::path& cpp_include_directory,
    const std::list<boost::filesystem::path>& data_files_directories,
    const bool legacy_mode)
    : project_directory_(project_directory),
      cpp_source_directory_(cpp_source_directory),
      cpp_include_directory_(cpp_include_directory),
      annotation_factory_(data_files_directories),
      legacy_mode_(legacy_mode) {

    BOOST_LOG_SEV(lg, debug) << "Project directory:" << project_directory_
                             << " C++ source directory: "
                             << cpp_source_directory
                             << " C++ include directory: "
                             << cpp_include_directory;

    if (data_files_directories.empty())
        BOOST_LOG_SEV(lg, warn) << "No data files directory provided.";
    else
        BOOST_LOG_SEV(lg, debug) << "Data directories:"
                                 << data_files_directories;

    annotation_factory_.load_reference_data();
}

void workflow::ensure_non_null_context() const {
    if (context_ != nullptr)
        return;

    BOOST_LOG_SEV(lg, error) << missing_context_ptr;
    BOOST_THROW_EXCEPTION(workflow_error(missing_context_ptr));
}

void workflow::operator()(const sml::type& t) const {
    ensure_non_null_context();

    const auto annotation(annotation_factory_.build(t.meta_data()));
    sml::meta_data_reader reader(t.meta_data());
    for (const auto f : context_->type_formatters()) {
        if (!f->generate(t.meta_data()))
            continue;

        context_->files().push_back(f->format(t, annotation));
    }
}

void workflow::operator()(const sml::module& m) const {
    ensure_non_null_context();

    const auto annotation(annotation_factory_.build(m.meta_data()));
    sml::meta_data_reader reader(m.meta_data());
    for (const auto f : context_->module_formatters()) {
        if (!f->generate(m.meta_data()))
            continue;

        context_->files().push_back(f->format(m, annotation));
    }
}

void workflow::operator()(const sml::concept& c) const {
    ensure_non_null_context();

    const auto annotation(annotation_factory_.build(c.meta_data()));
    sml::meta_data_reader reader(c.meta_data());
    for (const auto f : context_->concept_formatters()) {
        if (!f->generate(c.meta_data()))
            continue;

        context_->files().push_back(f->format(c, annotation));
    }
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
    context_ = std::unique_ptr<context>(new context);

    formatter_factory ff(m, project_directory_, cpp_source_directory_,
        cpp_include_directory_, legacy_mode_);

    context_->type_formatters(ff.build_type_formatters());
    context_->module_formatters(ff.build_module_formatters());
    context_->concept_formatters(ff.build_concept_formatters());

    sml::all_model_items_traversal(m, *this);
    model_file_subworkflow(m);
    const auto r(context_->files());
    context_ = std::unique_ptr<context>();
    return r;
}

} }
