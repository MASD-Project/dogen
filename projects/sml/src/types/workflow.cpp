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
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/sml/types/injector.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/json_hydrator.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/sml/types/resolver.hpp"
#include "dogen/sml/types/meta_data_processor.hpp"
#include "dogen/sml/types/concept_indexer.hpp"
#include "dogen/sml/types/property_indexer.hpp"
#include "dogen/sml/types/association_indexer.hpp"
#include "dogen/sml/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.json_hydrator"));
const std::string library_dir("library");

}


namespace dogen {
namespace sml {

workflow::
workflow(const bool load_library_models, const config::knitting_settings& s)
    : load_library_models_(load_library_models), settings_(s) { }

bool workflow::is_generatable(const type& t) const {
    const auto gt(t.generation_type());
    return
        gt == sml::generation_types::full_generation ||
        gt == sml::generation_types::partial_generation;
}

bool workflow::has_generatable_types(const sml::model& m) const {
    for (const auto pair : m.objects()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : m.enumerations()) {
        if (is_generatable(pair.second))
            return true;
    }

    for (const auto pair : m.enumerations()) {
        if (is_generatable(pair.second))
            return true;
    }

    return false;
}

std::list<model> workflow::load_library_models_activity() const {
    std::list<model> r;

    if (!load_library_models_)
        return r;

    BOOST_LOG_SEV(lg, debug) << "Loading models from the library.";
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / library_dir);
    const auto files(find_files(dir));
    dogen::sml::json_hydrator h;
    for (const auto& f : files) {
        BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << f;
        boost::filesystem::ifstream s(f);
        r.push_back(h.hydrate(s));
    }
    BOOST_LOG_SEV(lg, debug) << "Finished loading models from the library.";
    return r;
}

void workflow::inject_system_types_activity(model& target,
    std::list<model>& user_models) const {

    injector i;
    i.inject(target);

    for (auto& m : user_models)
        i.inject(m);
}

model workflow::create_merged_model_activity(const model& target,
    const std::list<model>& library_models,
    const std::list<model>& user_models) const {

    merger mg;
    mg.add_target(target);

    for (const auto& m : library_models)
        mg.add(m);

    for (const auto& m : user_models)
        mg.add(m);

    return mg.merge();
}

void workflow::process_meta_data_activity(model& merged_model) const {
    meta_data_processor p;
    p.process(merged_model);
}

void workflow::resolve_types_activity(model& merged_model) const {
    resolver res(merged_model);
    res.resolve();
}

void workflow::index_concepts_activity(model& merged_model) const {
    concept_indexer indexer;
    indexer.index(merged_model);
}

void workflow::index_properties_activity(model& merged_model) const {
    property_indexer indexer;
    indexer.index(merged_model);
}

void workflow::index_associations_activity(model& merged_model) const {
    association_indexer indexer;
    indexer.index(merged_model);
}

std::pair<bool, model> workflow::
execute(model target, std::list<model> user_models) const {
    const auto library_models(load_library_models_activity());
    inject_system_types_activity(target, user_models);
    auto r(create_merged_model_activity(target, library_models, user_models));
    resolve_types_activity(r);
    index_concepts_activity(r);
    index_properties_activity(r);
    index_associations_activity(r);
    process_meta_data_activity(r);
    return std::pair<bool, model> { has_generatable_types(r), r };
}

} }
