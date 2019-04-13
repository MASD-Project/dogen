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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/io/forward_list_io.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.utility/types/io/unordered_set_io.hpp"
#include "masd.dogen.variability/io/template_kinds_io.hpp"
#include "masd.dogen.archetypes/io/archetype_location_io.hpp"
#include "masd.dogen.variability/io/type_io.hpp"
#include "masd.dogen.variability/io/type_template_io.hpp"
#include "masd.dogen.variability/io/entry_template_io.hpp"
#include "masd.dogen.variability/types/template_kinds.hpp"
#include "masd.dogen.variability/types/value_factory.hpp"
#include "masd.dogen.variability/types/instantiation_error.hpp"
#include "masd.dogen.variability/types/template_instantiator.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("annotations.template_instantiator"));

const std::string empty;
const std::string template_not_instantiable(
    "Template cannot be instantiated: ");
const std::string empty_simple_name("Simple name cannot be empty.");
const std::string qualified_name_not_empty(
    "Qualified name must be empty. Template: ");
const std::string facet_name_not_empty(
    "Template is 'facet template' but facet name is not empty. Template: ");
const std::string archetype_name_not_empty(
    "Template is 'archetype template' but facet name is not empty. Template: ");
const std::string unsupported_template_kind(
    "Template is not supported: ");
const std::string missing_type("Type not found: ");
const std::string missing_kernel("Recursive templates must supply the kernel.");

}

namespace masd::dogen::variability {

template_instantiator::
template_instantiator(const archetypes::archetype_location_repository& alrp)
    : repository_(alrp) { }

bool template_instantiator::is_instantiable(const template_kinds tk) const {
    return
        tk == template_kinds::recursive_template ||
        tk == template_kinds::backend_template ||
        tk == template_kinds::facet_template ||
        tk == template_kinds::archetype_template;
}

bool template_instantiator::is_partially_mathcable(const value_types vt) const {
    return vt == value_types::key_value_pair;
}

void template_instantiator::validate(const archetypes::archetype_location& al,
    const name& n, const template_kinds tk) const {
    /*
     * All templates must supply a simple name. This cannot be
     * inferred.
     */
    const auto sn(n.simple());
    if (sn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple_name;
        BOOST_THROW_EXCEPTION(instantiation_error(empty_simple_name));
    }

    /*
     * Since we allow "instance" templates, which are basically
     * templates which do not require instantiation, we need to filter
     * them out. Ensure we are only attempting to process "real"
     * templates here.
     */
    if (!is_instantiable(tk)) {
        BOOST_LOG_SEV(lg, error) << template_not_instantiable << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_error(template_not_instantiable + sn));
    }

    /*
     * The qualified name must not be supplied by the template,
     * because it will be derived for each template instantiation.
     */
    if (!n.qualified().empty()) {
        BOOST_LOG_SEV(lg, error) << qualified_name_not_empty << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_error(qualified_name_not_empty + sn));
    }

    if (tk == template_kinds::recursive_template) {
        /*
         * At present our recursive templates are limited to starting
         * at the kernel or backend backend level. Ensure the user is
         * not trying to start at the facet or archetype level.
         */
        if (!al.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(facet_name_not_empty + sn));
        }

        if (!al.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << archetype_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(archetype_name_not_empty + sn));
        }
    }

    if (tk == template_kinds::facet_template) {
        /*
         * Facet templates must not have a facet or archetype, as
         * these will be derived for each instantiation.
         */
        if (!al.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(facet_name_not_empty + sn));
        }

        if (!al.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << archetype_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(archetype_name_not_empty + sn));
        }
    }

    if (tk == template_kinds::archetype_template) {
        /*
         * Archetype templates must not have an archetype, as these
         * will be derived for each instantiation.
         */
        if (!al.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << archetype_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(archetype_name_not_empty + sn));
        }
    }
}

type template_instantiator::to_type(const type_template& tt) const {
    type r;

    r.name(tt.name());
    r.value_type(tt.value_type());
    r.scope(tt.scope());
    r.archetype_location(tt.archetype_location());
    r.default_value(tt.default_value());
    r.is_partially_matchable(is_partially_mathcable(r.value_type()));

    return r;
}

boost::shared_ptr<value>
template_instantiator::to_value(const type_repository& trp,
    const std::string& qn, const entry_template& et) const {
    const auto i(trp.types_by_name().find(qn));
    if (i == trp.types_by_name().end()) {
        BOOST_LOG_SEV(lg, error) << missing_type << qn;
        BOOST_THROW_EXCEPTION(instantiation_error(missing_type + qn));
    }

    const auto t(i->second);
    value_factory f;
    return f.make(t, et.untyped_value());
}

bool template_instantiator::
is_match(const std::string& lhs, const std::string& rhs) const {
    /*
     * We match at the backend or facet level for one of two possible
     * cases: either the template has specifically requested a
     * backend/facet - in which case we just want the items for that
     * backend/facet, and all others can be ignored - or the template
     * requested an expansion across all backends/facets.
     */
    if (lhs.empty())
        return true;

    return lhs == rhs;
}

void template_instantiator::instantiate_facet_template(
    const type_template& tt, const std::string& backend_name,
    const std::unordered_set<std::string>& facet_names,
    std::list<type>& types) const {

    for (const auto facet_name : facet_names) {
        auto t(to_type(tt));
        const auto sn(tt.name().simple());

        /*
         * The facet name is qualified, so we can use it to
         * reconstruct the type's qualified name.
         */
        t.name().qualified(facet_name + "." + sn);
        t.archetype_location().backend(backend_name);
        t.archetype_location().facet(facet_name);
        t.archetype_location().archetype(empty);
        types.push_back(t);
    }
}

std::list<type> template_instantiator::
instantiate_recursive_template(const type_template& tt) const {
    std::list<type> r;

    /*
     * Global templates are expected to always supply a kernel. This
     * is because at present we do not support instantiating templates
     * across families as there is no use case for this.
     */
    const auto ttal(tt.archetype_location());
    if (ttal.kernel().empty()) {
        BOOST_LOG_SEV(lg, error) << missing_kernel;
        BOOST_THROW_EXCEPTION(instantiation_error(missing_kernel));
    }

    /*
     * Handle backends and facets first. We obtain a list of facets by
     * backend name and use it for two purposes: a) to validate if the
     * requested backend is supported or not, filtering out backends
     * without facets; b) to figure out what all the available facets
     * are, so we can instantiate them.
     *
     * If the template did not request a specific backend, this will
     * result in expanding the template for all backends and all facets
     * across all families.
     */
    for (const auto pair : repository_.facet_names_by_backend_name()) {
        const auto backend_name(pair.first);
        if (!is_match(ttal.backend(), backend_name))
            continue;

        /*
         * Expand the type for the backend first.
         */
        auto t(to_type(tt));

        /*
         * The backend name is qualified, so we can use it to
         * reconstruct the type's qualified name.
         */
        t.name().qualified(backend_name + "." + tt.name().simple());
        t.archetype_location().backend(backend_name);
        t.archetype_location().facet(empty);
        t.archetype_location().archetype(empty);
        r.push_back(t);

        /*
         * Now, perform a template expansion for each supported facet.
         */
        const auto& facet_names(pair.second);
        instantiate_facet_template(tt, backend_name, facet_names, r);
    }

    /*
     * Finally, handle expansion at the archetype level.
     */
    for (const auto al : repository_.archetype_locations()) {
        if (!is_match(ttal.backend(), al.backend()))
            continue;

        auto t(to_type(tt));
        t.name().qualified(al.archetype() + "." + tt.name().simple());
        t.archetype_location(al);
        r.push_back(t);
    }
    return r;
}

std::list<type> template_instantiator::
instantiate_facet_template(const type_template& tt) const {
    std::list<type> r;
    for (const auto pair : repository_.facet_names_by_backend_name()) {
        const auto backend_name(pair.first);
        if (!is_match(tt.archetype_location().backend(), backend_name))
            continue;

        const auto& facet_names(pair.second);
        instantiate_facet_template(tt, backend_name, facet_names, r);
    }
    return r;
}

std::list<type> template_instantiator::
instantiate_archetype_template(const type_template& tt) const {
    std::list<type> r;
    const auto ttal(tt.archetype_location());
    for (const auto al : repository_.archetype_locations()) {
        if (!is_match(ttal.backend(), al.backend()) ||
            !is_match(ttal.facet(), al.facet()))
            continue;

        auto t(to_type(tt));
        t.name().qualified(al.archetype() + "." + t.name().simple());
        t.archetype_location(al);
        r.push_back(t);
    }
    return r;
}

std::list<std::pair<std::string, boost::shared_ptr<value>>>
template_instantiator::instantiate_recursive_template(
    const type_repository& trp, const entry_template& et) const {

    const auto etal(et.archetype_location());
    std::list<std::pair<std::string, boost::shared_ptr<value>>> r;
    for (const auto pair : repository_.facet_names_by_backend_name()) {
        const auto backend_name(pair.first);
        if (!is_match(etal.backend(), backend_name))
            continue;

        std::pair<std::string, boost::shared_ptr<value>> entry;
        entry.first = backend_name + "." + et.name().simple();
        entry.second = to_value(trp, entry.first, et);
        r.push_back(entry);

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            std::pair<std::string, boost::shared_ptr<value>> entry;
            entry.first = facet_name + "." + et.name().simple();
            entry.second = to_value(trp, entry.first, et);
            r.push_back(entry);
        }
    }

    for (const auto al : repository_.archetype_locations()) {
        if (!is_match(etal.backend(), al.backend()))
            continue;

        std::pair<std::string, boost::shared_ptr<value>> entry;
        entry.first = al.archetype() + "." + et.name().simple();
        entry.second = to_value(trp, entry.first, et);
        r.push_back(entry);
    }

    return r;
}

std::list<std::pair<std::string, boost::shared_ptr<value>>>
template_instantiator::instantiate_facet_template(
    const type_repository& trp, const entry_template& et) const {

    const auto etal(et.archetype_location());
    std::list<std::pair<std::string, boost::shared_ptr<value>>> r;
    for (const auto pair : repository_.facet_names_by_backend_name()) {
        const auto backend_name(pair.first);
        if (!is_match(etal.backend(), backend_name))
            continue;

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            std::pair<std::string, boost::shared_ptr<value>> entry;
            entry.first = facet_name + "." + et.name().simple();
            entry.second = to_value(trp, entry.first, et);
            r.push_back(entry);
        }
    }

    return r;
}

std::list<std::pair<std::string, boost::shared_ptr<value>>>
template_instantiator::instantiate_archetype_template(
    const type_repository& trp, const entry_template& et) const {
    std::list<std::pair<std::string, boost::shared_ptr<value>>> r;

    const auto etal(et.archetype_location());

    for (const auto al : repository_.archetype_locations()) {
        if (!is_match(etal.backend(), al.backend()) ||
            !is_match(etal.facet(), al.facet()))
            continue;

        std::pair<std::string, boost::shared_ptr<value>> entry;
        entry.first = al.archetype() + "." + et.name().simple();
        entry.second = to_value(trp, entry.first, et);
        r.push_back(entry);
    }

    return r;
}

std::list<type>
template_instantiator::instantiate(const type_template& tt) const {
    validate(tt.archetype_location(), tt.name(), tt.kind());

    BOOST_LOG_SEV(lg, debug) << "Instantiating template: " << tt;

    std::list<type> r;
    const auto tk(tt.kind());
    if (tk == template_kinds::recursive_template)
        r = instantiate_recursive_template(tt);
    else if (tk == template_kinds::facet_template)
        r = instantiate_facet_template(tt);
    else if (tk == template_kinds::archetype_template)
        r = instantiate_archetype_template(tt);
    else {
        BOOST_LOG_SEV(lg, error) << unsupported_template_kind << tk;
        BOOST_THROW_EXCEPTION(instantiation_error(unsupported_template_kind +
                boost::lexical_cast<std::string>(tk)));
    }

    BOOST_LOG_SEV(lg, debug) << "Instantiation result: " << r;
    return r;
}

std::list<std::pair<std::string, boost::shared_ptr<value>>>
template_instantiator::
instantiate(const type_repository& trp, const entry_template& et) const {
    if (et.kind() == template_kinds::instance) {
        std::pair<std::string, boost::shared_ptr<value>> entry;
        entry.first = et.name().qualified();
        entry.second = to_value(trp, entry.first, et);
        std::list<std::pair<std::string, boost::shared_ptr<value>>> r;
        r.push_back(entry);
        return r;
    }

    validate(et.archetype_location(), et.name(), et.kind());

    BOOST_LOG_SEV(lg, debug) << "Instantiating template: " << et;

    std::list<std::pair<std::string, boost::shared_ptr<value>>> r;
    const auto tk(et.kind());
    if (tk == template_kinds::recursive_template)
        r = instantiate_recursive_template(trp, et);
    else if (tk == template_kinds::facet_template)
        r = instantiate_facet_template(trp, et);
    else if (tk == template_kinds::archetype_template)
        r = instantiate_archetype_template(trp, et);
    else {
        BOOST_LOG_SEV(lg, error) << unsupported_template_kind << tk;
        BOOST_THROW_EXCEPTION(instantiation_error(unsupported_template_kind +
                boost::lexical_cast<std::string>(tk)));
    }

    BOOST_LOG_SEV(lg, debug) << "Instantiation result: " << r;
    return r;
}

}
