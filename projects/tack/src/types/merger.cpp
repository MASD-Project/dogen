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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/tack/types/object.hpp"
#include "dogen/tack/types/merging_error.hpp"
#include "dogen/tack/io/property_io.hpp"
#include "dogen/tack/io/model_io.hpp"
#include "dogen/tack/types/merger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("tack.merger"));

const std::string empty;
const std::string hardware_model_name("hardware");
const std::string msising_dependency("Cannot find target dependency: ");
const std::string missing_target("Target model not present");
}

namespace dogen {
namespace tack {

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

    std::ostringstream stream;
    stream << "Attempt to merge more than once.";

    BOOST_LOG_SEV(lg, error) << stream.str();
    BOOST_THROW_EXCEPTION(merging_error(stream.str()));
}

void merger::check_name(const std::string& model_name, const name& key,
    const name& value) const {

    if (key.location().original_model_name() != model_name) {
        std::ostringstream s;
        s << "Type does not belong to this model. Model name: '"
          << model_name << "'. Type name: "
          << key.qualified();
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(merging_error(s.str()));
    }

    if (key != value) {
        std::ostringstream s;
        s << "Inconsistency between key and value names: "
          << " key: " << key.qualified()
          << " value: " << value.qualified();
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(merging_error(s.str()));
    }
}

void merger::update_references() {
    typedef std::pair<name, origin_types> value_type;
    std::map<std::string, value_type> references_by_model_name;
    for (const auto& pair : models_) {
        const auto& model(pair.second);
        const auto value(std::make_pair(model.name(), model.origin_type()));
        const auto mn(model.name().location().original_model_name());
        const auto p(std::make_pair(mn, value));
        references_by_model_name.insert(p);
    }

    std::unordered_map<name, origin_types> updated_references;
    for (auto& pair : merged_model_.references()) {
        const auto n(pair.first);
        const auto mn(n.location().original_model_name());
        const auto i(references_by_model_name.find(mn));
        if (i == references_by_model_name.end()) {
            BOOST_LOG_SEV(lg, error) << msising_dependency << mn;
            BOOST_THROW_EXCEPTION(merging_error(msising_dependency + mn));
        }

        const auto p(std::make_pair(i->second.first, i->second.second));
        updated_references.insert(p);
    }
    merged_model_.references(updated_references);
}

void merger::add_target(const model& target) {
    const auto qn(target.name().qualified());
    require_not_has_target(qn);

    has_target_ = true;
    merged_model_.name(target.name());
    merged_model_.documentation(target.documentation());
    merged_model_.leaves(target.leaves());
    merged_model_.modules(target.modules());
    merged_model_.references(target.references());
    merged_model_.extensions(target.extensions());
    merged_model_.is_target(true);

    BOOST_LOG_SEV(lg, debug) << "added target model: " << qn;
}

void merger::add(const model& m) {
    require_not_has_merged();

    if (m.is_target())
        add_target(m);

    BOOST_LOG_SEV(lg, debug) << "adding model: "
                             << m.name().qualified();
    BOOST_LOG_SEV(lg, debug) << "contents: " << m;
    models_.insert(std::make_pair(m.name(), m));
}

void merger::merge_model(const model& m) {
    BOOST_LOG_SEV(lg, info) << "Merging model: '"
                            << m.name().qualified()
                            << " modules: " << m.modules().size()
                            << " concepts: " << m.concepts().size()
                            << " primitives: " << m.primitives().size()
                            << " enumerations: " << m.enumerations().size()
                            << " objects: " << m.objects().size();

    const auto mn(m.name().location().original_model_name());
    for (const auto& c : m.concepts()) {
        check_name(mn, c.first, c.second.name());
        merged_model_.concepts().insert(c);
    }

    for (const auto& pair : m.primitives()) {
        // FIXME: mega hack to handle primitive model.
        const auto pmn(mn == hardware_model_name ? empty : mn);
        check_name(pmn, pair.first, pair.second.name());
        merged_model_.primitives().insert(pair);
    }

    for (const auto& pair : m.enumerations()) {
        check_name(mn, pair.first, pair.second.name());
        merged_model_.enumerations().insert(pair);
    }

    for (const auto& pair : m.objects()) {
        check_name(mn, pair.first, pair.second.name());
        merged_model_.objects().insert(pair);
    }

    for (const auto& pair : m.modules()) {
        if (!pair.first.simple().empty())
            check_name(mn, pair.first, pair.second.name());
        merged_model_.modules().insert(pair);
    }
}

void merger::merge_models() {
    for (const auto& pair : models_)
        merge_model(pair.second);
}

model merger::merge() {
    require_has_target();
    require_not_has_merged();
    update_references();
    merge_models();
    has_merged_ = true;
    return merged_model_;
}

} }
