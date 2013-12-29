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
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/sml/types/all_types_traversal.hpp"
#include "dogen/om/types/code_generation_marker_factory.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/om/types/workflow_error.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"
#include "dogen/om/types/formatter_factory.hpp"
#include "dogen/om/types/annotation_factory.hpp"
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
    context(const std::list<boost::filesystem::path>& data_files_directories)
        : factory_(data_files_directories) { }

public:
    annotation_factory& factory() { return factory_; }
    std::list<file>& files() { return files_; }

private:
    annotation_factory factory_;
    std::list<file> files_;
};

workflow::
workflow(const std::list<boost::filesystem::path>& data_files_directories)
    : data_files_directories_(data_files_directories),
      type_formatters_(formatter_factory::build_type_formatters()),
      module_formatters_(formatter_factory::build_module_formatters()),
      concept_formatters_(formatter_factory::build_concept_formatters()) { }

void workflow::ensure_non_null_context() const {
    if (context_ != nullptr)
        return;

    BOOST_LOG_SEV(lg, error) << missing_context_ptr;
    BOOST_THROW_EXCEPTION(workflow_error(missing_context_ptr));
}

void workflow::operator()(const sml::type& t) const {
    ensure_non_null_context();
    const auto annotation(context_->factory().build(t.meta_data()));
    sml::meta_data_reader reader(t.meta_data());
    for (const auto f : type_formatters_) {
        if (!f->generate(t.meta_data()))
            continue;

        context_->files().push_back(f->format(t, annotation));
    }
}

void workflow::operator()(const sml::module& m) const {
    ensure_non_null_context();

    const auto annotation(context_->factory().build(m.meta_data()));
    sml::meta_data_reader reader(m.meta_data());
    for (const auto f : module_formatters_) {
        if (!f->generate(m.meta_data()))
            continue;

        context_->files().push_back(f->format(m, annotation));
    }
}

void workflow::operator()(const sml::concept& c) const {
    ensure_non_null_context();

    const auto annotation(context_->factory().build(c.meta_data()));
    sml::meta_data_reader reader(c.meta_data());
    for (const auto f : concept_formatters_) {
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
    context_ = std::unique_ptr<context>(new context(data_files_directories_));
    context_->factory().load_reference_data();
    sml::all_model_items_traversal(m, *this);
    model_file_subworkflow(m);
    const auto r(context_->files());
    context_ = std::unique_ptr<context>();
    return r;
}

} }
