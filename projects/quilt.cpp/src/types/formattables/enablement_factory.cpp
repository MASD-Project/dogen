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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.enablement_factory"));

const std::string global_properties_not_found(
    "Could not find global enablement properties for formatter: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

enablement_factory::enablement_factory(
    const dynamic::repository& srp,
    const formatters::container& fc,
    const std::unordered_map<std::string,
                             global_enablement_properties>& gep)
    : global_enablement_properties_(gep),
      field_definitions_(create_field_definitions(srp, fc)) {}

std::unordered_map<std::string, enablement_factory::field_definitions>
enablement_factory::create_field_definitions(
    const dynamic::repository& rp,
    const formatters::container& fc) const {
    const dynamic::repository_selector s(rp);

    std::unordered_map<std::string, field_definitions> r;
    for (const auto& f : fc.all_file_formatters()) {
        field_definitions fd;
        const auto oh(f->ownership_hierarchy());
        const auto& fn(oh.formatter_name());
        fd.enabled = s.select_field_by_name(fn, traits::enabled());

        const auto& fctn(oh.facet_name());
        fd.supported = s.select_field_by_name(fctn, traits::supported());
        r[fn] = fd;
    }
    return r;
}

std::unordered_map<std::string, enablement_factory::local_enablement_properties>
enablement_factory::obtain_local_properties(
    const dynamic::object& o) const {
    std::unordered_map<std::string, local_enablement_properties> r;
    const dynamic::field_selector fs(o);
    for (const auto& pair : field_definitions_) {
        const auto& fn(pair.first);
        const auto& fd(pair.second);

        local_enablement_properties lep;
        lep.supported = fs.get_boolean_content_or_default(fd.supported);
        if (fs.has_field(fd.enabled))
            lep.enabled = fs.get_boolean_content(fd.enabled);

        r[fn] = lep;
    }
    return r;
}

std::unordered_map<std::string, bool>
enablement_factory::compute_enablement_value(
    const std::unordered_map<std::string, local_enablement_properties>&
    lep, const bool types_only) const {

    std::unordered_map<std::string, bool> r;
    for (const auto& pair : lep) {
        const auto& fn(pair.first);
        const auto i(global_enablement_properties_.find(fn));
        if (i == global_enablement_properties_.end()) {
            BOOST_LOG_SEV(lg, error) << global_properties_not_found << fn;
            BOOST_THROW_EXCEPTION(
                building_error(global_properties_not_found + fn));
        }

        const auto gep(i->second);
        if (!gep.model_enabled() || !gep.facet_enabled()) {
            // model or facet have been disabled, so formatter will be
            // disabled.
            r[fn] = false;
            continue;
        }

        if (types_only) {
            const auto is_types(boost::starts_with(fn, "quilt.cpp.types."));
            r[fn] = is_types;
            continue;
        }

        if (pair.second.enabled) {
            // formatter field has been set and so takes precedence.
            r[fn] = *pair.second.enabled;
            continue;
        }

        r[fn] = gep.formatter_enabled();
    }
    return r;
}

std::unordered_map<std::string, bool> enablement_factory::
make(const dynamic::object& o, const bool types_only) const {
    const auto lep(obtain_local_properties(o));
    return compute_enablement_value(lep, types_only);
}

} } } }
