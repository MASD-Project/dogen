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
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/sml/types/injector.hpp"
#include "dogen/sml/types/json_hydrator.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/sml/types/resolver.hpp"
#include "dogen/sml/types/meta_data_tagger.hpp"
#include "dogen/sml/types/workflow.hpp"

namespace {

const std::string library_dir("library");

}


namespace dogen {
namespace sml {

workflow::workflow(const bool add_system_models, const config::settings& s)
    : add_system_models_(add_system_models), settings_(s) {}

bool workflow::is_generatable(const type& t) const {
    const auto gt(t.generation_type());
    return
        gt == sml::generation_types::full_generation ||
        gt == sml::generation_types::partial_generation;
}

bool workflow::has_generatable_types(const sml::model& m) const {
    for (const auto pair : m.objects()) {
        if (is_generatable(*pair.second))
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

std::list<model> workflow::
augment_references_activity(const std::list<model>& references) const {
    std::list<model> r(references);
    if (add_system_models_) {
        using namespace dogen::utility::filesystem;
        const auto dir(data_files_directory() / library_dir);
        const auto files(find_files(dir));
        dogen::sml::json_hydrator h;
        for (const auto& f : files) {
            boost::filesystem::ifstream s(f);
            r.push_back(h.hydrate(s));
        }
    }
    return r;
}

model workflow::create_merged_model_activity(const model& target,
    const std::list<model>& references) const {

    injector i;
    auto t(target);
    i.inject(t);

    merger mg;
    mg.add_target(t);

    for (auto r : references) {
        i.inject(r);
        mg.add(r);
    }
    return mg.merge();
}

void workflow::tag_model_activity(model& merged_model) const {
    meta_data_tagger t;
    t.tag(settings_.cpp(), merged_model);
}

void workflow::resolve_types_activity(model& merged_model) const {
    resolver res(merged_model);
    res.resolve();
}

std::pair<bool, model> workflow::
execute(const model& target, const std::list<model>& references) const {
    const auto augment_references(augment_references_activity(references));
    auto r(create_merged_model_activity(target, augment_references));
    resolve_types_activity(r);
    tag_model_activity(r);
    return std::pair<bool, model> { has_generatable_types(r), r };
}

} }
