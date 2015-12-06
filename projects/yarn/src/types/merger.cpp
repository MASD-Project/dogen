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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/map_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/merging_error.hpp"
#include "dogen/yarn/io/property_io.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/io/origin_types_io.hpp"
#include "dogen/yarn/io/intermediate_model_io.hpp"
#include "dogen/yarn/types/merger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.merger"));

const std::string empty;
const std::string msising_dependency("Cannot find target dependency: ");
const std::string missing_target("Target model not present");
const std::string multiple_merge("Attempt to merge more than once.");

}

namespace dogen {
namespace yarn {

merger::merger() : has_target_(false), has_merged_(false) { }

void merger::require_not_has_target(const std::string& name) const {
    if (!has_target())
        return;

    std::ostringstream stream;
    stream << "Only one target expected. Last target model name: '"
           << merged_model_.name().qualified()
           << "'. New target model name: "
           << name;

    BOOST_LOG_SEV(lg, error) << stream.str();
    BOOST_THROW_EXCEPTION(merging_error(stream.str()));
}

void merger::require_has_target() const {
    if (has_target())
        return;

    BOOST_LOG_SEV(lg, error) << missing_target;
    BOOST_THROW_EXCEPTION(merging_error(missing_target));
}

void merger::require_not_has_merged() const {
    if (!has_merged())
        return;

    BOOST_LOG_SEV(lg, error) << multiple_merge;
    BOOST_THROW_EXCEPTION(merging_error(multiple_merge));
}

void merger::check_name(const name& model_name, const std::string& key,
    const name& value, const bool in_global_namespace) const {

    if (!in_global_namespace) {
        if (value.location().external_module_path() !=
            model_name.location().external_module_path() ||
            value.location().model_module_path() !=
            model_name.location().model_module_path()) {
            std::ostringstream s;
            s << "Type does not belong to this model. Model name: '"
              << model_name.qualified() << "'. Type name: "
              << value.qualified();
            BOOST_LOG_SEV(lg, error) << s.str();
            BOOST_THROW_EXCEPTION(merging_error(s.str()));
        }
    }

    if (key != value.qualified()) {
        std::ostringstream s;
        s << "Inconsistency between key and value names: "
          << " key: " << key << " value: " << value.qualified();
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(merging_error(s.str()));
    }
}

void merger::update_references() {
    for (const auto& pair : models_) {
        const auto n(pair.first);
        if (merged_model_.name() == n)
            continue;

        const auto& model(pair.second);
        const auto p(std::make_pair(model.name(), model.origin_type()));
        merged_model_.references().insert(p);
    }

    BOOST_LOG_SEV(lg, info) << "References: " << merged_model_.references();
}

void merger::add_target(const intermediate_model& target) {
    const auto qn(target.name().qualified());
    require_not_has_target(qn);

    has_target_ = true;
    merged_model_.name(target.name());
    // merged_model_.documentation(target.documentation());
    merged_model_.leaves(target.leaves());
    merged_model_.modules(target.modules());
    merged_model_.references(target.references());
    // merged_model_.extensions(target.extensions());
    merged_model_.is_target(true);

    BOOST_LOG_SEV(lg, debug) << "added target model: " << qn;
}

void merger::add(const intermediate_model& m) {
    require_not_has_merged();

    if (m.is_target())
        add_target(m);

    BOOST_LOG_SEV(lg, debug) << "adding model: '"
                             << m.name().qualified() << "'";
    BOOST_LOG_SEV(lg, debug) << "contents: " << m;
    models_.insert(std::make_pair(m.name(), m));
}

void merger::merge_model(const intermediate_model& m) {
    BOOST_LOG_SEV(lg, info) << "Merging model: '"
                            << m.name().qualified()
                            << " modules: " << m.modules().size()
                            << " concepts: " << m.concepts().size()
                            << " primitives: " << m.primitives().size()
                            << " enumerations: " << m.enumerations().size()
                            << " objects: " << m.objects().size();

    for (const auto& pair : m.concepts()) {
        const auto& k(pair.first);
        const auto& v(pair.second);
        check_name(m.name(), k, v.name(), v.in_global_module());
        merged_model_.concepts().insert(pair);
    }

    for (const auto& pair : m.primitives()) {
        const auto& k(pair.first);
        const auto& v(pair.second);
        check_name(m.name(), k, v.name(), v.in_global_module());
        merged_model_.primitives().insert(pair);
    }

    for (const auto& pair : m.enumerations()) {
        const auto& k(pair.first);
        const auto& v(pair.second);
        check_name(m.name(), k, v.name(), v.in_global_module());
        merged_model_.enumerations().insert(pair);
    }

    for (const auto& pair : m.objects()) {
        const auto& k(pair.first);
        const auto& v(pair.second);
        check_name(m.name(), k, v.name(), v.in_global_module());
        merged_model_.objects().insert(pair);
    }

    for (const auto& pair : m.modules()) {
        const auto& k(pair.first);
        const auto& v(pair.second);
        check_name(m.name(), k, v.name(), v.in_global_module());
        merged_model_.modules().insert(pair);
    }
}

void merger::merge_models() {
    for (const auto& pair : models_)
        merge_model(pair.second);
}

intermediate_model merger::merge() {
    require_has_target();
    require_not_has_merged();
    update_references();
    merge_models();
    has_merged_ = true;
    return merged_model_;
}

} }
