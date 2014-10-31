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
#include <iterator>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/consumption_workflow.hpp"
#include "dogen/formatters/types/meta_data/general_settings_factory.hpp"
#include "dogen/backend/types/workflow_error.hpp"
#include "dogen/backend/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("backend.workflow"));

std::string empty;
const std::string null_registrar("Registrar is null");
const std::string no_generatable_model_modules(
    "No generatable model modules found.");
const std::string multiple_generatable_model_modules(
    "More than one model module is generatable: ");

}
namespace dogen {
namespace backend {

std::shared_ptr<backend::registrar> workflow::registrar_;

workflow::workflow(const config::knitting_settings& ks,
    const std::forward_list<boost::filesystem::path>& data_files_dirs)
    : knitting_settings_(ks), data_files_directories_(data_files_dirs) { }

backend::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<backend::registrar>();

    return *registrar_;
}

void workflow::validate_backends_activity() const {
    BOOST_LOG_SEV(lg, debug) << "Validating backend workflow.";
    registrar().validate();
    const auto& backends(registrar().backends());
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(backends.begin(), backends.end())
                             << " registered backend(s): ";

    for (const auto& b : backends) {
        BOOST_LOG_SEV(lg, debug) << "Backend: '" << b->id() << "'";
        b->validate();
    }
    BOOST_LOG_SEV(lg, debug) << "Finished validating backend workflow.";
}

formatters::general_settings
workflow::create_general_settings_activity(const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Creating general settings.";

    boost::optional<formatters::general_settings> r;
    using formatters::meta_data::general_settings_factory;
    general_settings_factory f(data_files_directories_);
    f.load_reference_data();

    for (const auto pair : m.modules()) {
        const auto mod(pair.second);
        if (mod.generation_type() != sml::generation_types::full_generation ||
            mod.type() != sml::module_types::model)
            continue;

        if (r) {
            BOOST_LOG_SEV(lg, error) << multiple_generatable_model_modules
                                     << mod.name();

            const auto sn(mod.name().simple_name());
            BOOST_THROW_EXCEPTION(workflow_error(
                    multiple_generatable_model_modules + sn));
        }
        r = f.build(mod.meta_data());
    }

    if (!r) {
        BOOST_LOG_SEV(lg, error) << no_generatable_model_modules;
        BOOST_THROW_EXCEPTION(workflow_error(no_generatable_model_modules));
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating general settings.";
    return *r;
}

void workflow::register_backend(std::shared_ptr<backend_interface> b) {
    registrar().register_backend(b);
}

std::forward_list<formatters::file>
workflow::execute(const sml::model& m) const {
    validate_backends_activity();
    const auto gs(create_general_settings_activity(m));

    std::forward_list<formatters::file> r;
    for(const auto b : registrar().backends()) {
        const auto id(b->id());
        BOOST_LOG_SEV(lg, debug) << "Generating files backend '" << id << "'";
        auto files(b->generate(gs, m));
        BOOST_LOG_SEV(lg, debug) << "Files for backend '" << id << "': "
                                 << std::distance(files.begin(), files.end());
        r.splice_after(r.before_begin(), files);
    }

    return r;
}

} }
