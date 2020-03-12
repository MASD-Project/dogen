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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.archetypes/io/location_io.hpp"
#include "dogen.variability/io/meta_model/profile_io.hpp"
#include "dogen.variability/io/meta_model/feature_io.hpp"
#include "dogen.variability/io/meta_model/template_kind_io.hpp"
#include "dogen.variability/io/meta_model/feature_template_io.hpp"
#include "dogen.variability/io/meta_model/profile_template_io.hpp"
#include "dogen.variability/io/meta_model/configuration_point_io.hpp"
#include "dogen.variability/io/meta_model/configuration_point_template_io.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/instantiation_exception.hpp"
#include "dogen.variability/types/helpers/template_instantiator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("variability.helpers.template_instantiator"));

const std::string empty;
const std::string empty_msg("<empty>");

const std::string empty_qualified_name(
    "Qualified name cannot be empty for instance templates.");
const std::string empty_owner("Owner cannot be empty.");
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
const std::string empty_domains("No instantiation domain names found.");
const std::string empty_domain_name(
    "Template has an empty domain name: ");
const std::string invalid_domain_name(
    "Instantiation domain name could not be located: ");
const std::string missing_feature("Feature not found: ");
const std::string missing_kernel("Recursive templates must supply the kernel.");
const std::string duplicate_configuration_point(
    "Found more than one configuration point for the same feature: ");

}

namespace dogen::variability::helpers {

template_instantiator::template_instantiator(
    const archetypes::location_repository& alrp, const bool compatibility_mode)
    : repository_(alrp), compatibility_mode_(compatibility_mode) {

    BOOST_LOG_SEV(lg, trace) << "Compatibility mode: " << compatibility_mode_;
}

bool template_instantiator::
is_instantiable(const meta_model::template_kind tk) const {
    using meta_model::template_kind;
    return
        tk == template_kind::recursive_template ||
        tk == template_kind::backend_template ||
        tk == template_kind::facet_template ||
        tk == template_kind::archetype_template;
}

bool template_instantiator::
is_partially_mathcable(const meta_model::value_type vt) const {
    return vt == meta_model::value_type::key_value_pair;
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

void template_instantiator::validate(const archetypes::location& al,
    const meta_model::name& n, const meta_model::template_kind tk) const {
    /*
     * All templates must supply a simple name. This cannot be
     * inferred.
     */
    const auto sn(n.simple());
    if (sn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple_name;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_simple_name));
    }

    /*
     * The qualified name must not be supplied by instantiable
     * templates because it will be derived for each template
     * instantiation.
     */
    if (is_instantiable(tk) && !n.qualified().empty()) {
        BOOST_LOG_SEV(lg, error) << qualified_name_not_empty << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_exception(qualified_name_not_empty + sn));
    }

    using meta_model::template_kind;
    if (tk == template_kind::recursive_template) {
        /*
         * At present our recursive templates are limited to starting
         * at the kernel or backend backend level. Ensure the user is
         * not trying to start at the facet or archetype level.
         */
        if (!al.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_exception(facet_name_not_empty + sn));
        }

        if (!al.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << archetype_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_exception(archetype_name_not_empty + sn));
        }
    }

    if (tk == template_kind::facet_template) {
        /*
         * Facet templates must not have a facet or archetype, as
         * these will be derived for each instantiation.
         */
        if (!al.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_exception(facet_name_not_empty + sn));
        }

        if (!al.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << archetype_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_exception(archetype_name_not_empty + sn));
        }
    }

    if (tk == template_kind::archetype_template) {
        /*
         * Archetype templates must not have an archetype, as these
         * will be derived for each instantiation.
         */
        if (!al.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << archetype_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_exception(archetype_name_not_empty + sn));
        }
    }
}

meta_model::configuration_point template_instantiator::to_configuration_point(
    const meta_model::feature_model& fm, const std::string& owner,
    const meta_model::configuration_point_template& cpt) const {
    /*
     * Determine which qualified name to use for the point's feature.
     */
    std::string fqn;
    if (cpt.kind() == meta_model::template_kind::instance) {
        /*
         * Instance templates must have a qualified name.
         */
        if (cpt.name().qualified().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_qualified_name;
            BOOST_THROW_EXCEPTION(
                instantiation_exception(empty_qualified_name));
        }
        fqn = cpt.name().qualified();
    } else {
        /*
         * Non-instance templates must have a owner.
         */
        if (owner.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_owner;
            BOOST_THROW_EXCEPTION(instantiation_exception(empty_owner));
        }
        fqn = owner + "." + cpt.name().simple();
    }

    /*
     * Locate the feature for this configuration point template.
     */
    const auto& bn(fm.by_name());
    BOOST_LOG_SEV(lg, trace) << "Feature qualified name: " << fqn;
    const auto i(bn.find(fqn));
    if (i == bn.end()) {
        BOOST_LOG_SEV(lg, error) << missing_feature << fqn;
        BOOST_THROW_EXCEPTION(instantiation_exception(missing_feature + fqn));
    }

    /*
     * Now we can populate the name of the point from the point
     * template's associated feature, and, if supplied, the owner.
     */
    const auto& feature(i->second);
    meta_model::configuration_point r;
    r.name().simple(feature.name().simple());
    r.name().qualified(feature.name().qualified());

    /*
     * Finally we can create the value.
     */
    helpers::value_factory vf;
    r.value(vf.make(feature, cpt.untyped_value()));
    return r;
}

meta_model::feature template_instantiator::
to_feature(const meta_model::feature_template& ft) const {
    meta_model::feature r;

    r.name(ft.name());
    r.value_type(ft.value_type());
    r.binding_point(ft.binding_point());
    r.location(ft.location());
    r.default_value(ft.default_value());
    r.is_partially_matchable(is_partially_mathcable(r.value_type()));

    return r;
}

std::list<meta_model::configuration_point>
template_instantiator::instantiate_recursive_template(
    const meta_model::feature_model& fm,
    const meta_model::configuration_point_template& cpt) const {

    const auto& l(cpt.location());
    std::list<meta_model::configuration_point> r;
    for (const auto pair : repository_.facet_names_by_backend_name()) {
        /*
         * If the point template specified a backend, make sure we
         * only include facets that match it. If it was blank, we'll
         * match all backends.
         */
        const auto backend_name(pair.first);
        if (!is_match(l.backend(), backend_name))
            continue;

        /*
         * Create the configuration point for the backend itself.
         */
        r.push_back(to_configuration_point(fm, backend_name, cpt));

        /*
         * Now create configuration points for its facets.
         */
        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names)
            r.push_back(to_configuration_point(fm, facet_name, cpt));
    }

    /*
     * Now handle all archetypes.
     */
    for (const auto al : repository_.all()) {
        /*
         * Again, apply the backend matching logic.
         */
        if (!is_match(l.backend(), al.backend()))
            continue;

        const auto archetype_name(al.archetype() + "." + cpt.name().simple());
        r.push_back(to_configuration_point(fm, archetype_name, cpt));
    }

    return r;
}

std::list<meta_model::configuration_point> template_instantiator::
instantiate_facet_template(const meta_model::feature_model& fm,
    const meta_model::configuration_point_template& cpt) const {

    const auto& l(cpt.location());
    std::list<meta_model::configuration_point> r;
    for (const auto pair : repository_.facet_names_by_backend_name()) {
        const auto backend_name(pair.first);
        if (!is_match(l.backend(), backend_name)) {
            BOOST_LOG_SEV(lg, trace) << "Ignoring backend: " << backend_name;
            continue;
        }

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            BOOST_LOG_SEV(lg, trace) << "Processing facet: " << facet_name;
            r.push_back(to_configuration_point(fm, facet_name, cpt));
        }
    }
    return r;
}

std::list<meta_model::configuration_point> template_instantiator::
instantiate_archetype_template(const meta_model::feature_model& fm,
    const meta_model::configuration_point_template& cpt) const {

    std::list<meta_model::configuration_point> r;
    const auto l(cpt.location());
    for (const auto al : repository_.all()) {
        if (!is_match(l.backend(), al.backend()) ||
            !is_match(l.facet(), al.facet()))
            continue;

        const auto archetype_name(al.archetype() + "." + cpt.name().simple());
        r.push_back(to_configuration_point(fm, archetype_name, cpt));
    }

    return r;
}

std::list<meta_model::configuration_point>
template_instantiator::instantiate(const meta_model::feature_model& fm,
    const meta_model::configuration_point_template& cpt) const {
    /*
     * First, sanity check the template to make sure it is vaguely
     * valid.
     */
    validate(cpt.location(), cpt.name(), cpt.kind());

    /*
     * Dispatch to the appropriate instantiator.
     */
    BOOST_LOG_SEV(lg, debug) << "Instantiating point template: " << cpt;

    const auto tk(cpt.kind());
    using meta_model::template_kind;
    std::list<meta_model::configuration_point> r;
    if (tk == template_kind::recursive_template)
        r = instantiate_recursive_template(fm, cpt);
    else if (tk == template_kind::facet_template)
        r = instantiate_facet_template(fm, cpt);
    else if (tk == template_kind::archetype_template)
        r = instantiate_archetype_template(fm, cpt);
    else {
        const auto s(boost::lexical_cast<std::string>(tk));
        BOOST_LOG_SEV(lg, error) << unsupported_template_kind << s;
        BOOST_THROW_EXCEPTION(
            instantiation_exception(unsupported_template_kind + s));
    }

    BOOST_LOG_SEV(lg, debug) << "Instantiation result: " << r;
    return r;
}

std::list<meta_model::feature> template_instantiator::
instantiate(const std::unordered_map<std::string, std::vector<std::string>>&
    template_instantiation_domains,
    const meta_model::feature_template& ft) const {
    /*
     * Domain names should never be empty.
     */
    if (template_instantiation_domains.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_domains ;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_domains));

    }

    /*
     * All templates must supply a simple name. This cannot be
     * inferred.
     */
    const auto& n(ft.name());
    const auto sn(n.simple());
    if (sn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple_name;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_simple_name));
    }

    /*
     * All templates must supply a instantiation domain name.
     */
    const auto idn(ft.instantiation_domain_name());
    if (idn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_domain_name << sn;
        BOOST_THROW_EXCEPTION(instantiation_exception(empty_domain_name + sn));
    }

    /*
     * The instantiation domain name provided must exist in our
     * collection of all domain names.
     */
    const auto i(template_instantiation_domains.find(idn));
    if (i == template_instantiation_domains.end()) {
        BOOST_LOG_SEV(lg, error) << invalid_domain_name << idn
                                 << " Requested for template: " << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_exception(invalid_domain_name + idn));
    }

    /*
     * Perform the template expansion across the domain.
     */
    const auto& domain(i->second);
    std::list<meta_model::feature> r;
    for (const auto& e : domain) {
        auto f(to_feature(ft));
        f.name().qualified(e + "." + sn);
        r.push_back(f);
    }
    return r;
}

meta_model::profile
template_instantiator::instantiate(const meta_model::feature_model& fm,
    const meta_model::profile_template& pt) const {

    const auto ptqn(pt.name().qualified());
    BOOST_LOG_SEV(lg, debug) << "Instantiating profile template: " << ptqn;

    meta_model::profile r;
    r.name(pt.name());
    r.stereotype(pt.stereotype());
    r.parents(pt.parents());

    for (auto& cpt : pt.templates()) {
        const auto cptqn(cpt.name().qualified());
        BOOST_LOG_SEV(lg, debug) << "Configuration point template: "
                                 << cpt.name().simple() << " ('"
                                 << (cptqn.empty() ? empty_msg : cptqn)
                                 << "')" ;
        std::list<meta_model::configuration_point> cps;

        /*
         * Try to instantiate the template.
         */
        try {
            cps = instantiate(fm, cpt);
        } catch(const instantiation_exception& e) {
            /*
             * This is not a particularly glamorous approach to handling
             * backwards compatibility. The idea is that we may be trying
             * to instantiate features that are no longer supported. If
             * the user has requested backwards compatibility mode, we try
             * to continue by ignoring the fact that those features no
             * longer exist. This is also not ideal because we may capture
             * errors when the user requested a template kind that is not
             * supported.
             */
            if (!compatibility_mode_) {
                BOOST_LOG_SEV(lg, error) << "Error instantiating template: "
                                         << ptqn << ". Message: "
                                         << e.what() << ".";
                throw e;
            }

            BOOST_LOG_SEV(lg, warn) << "Error instantiating template: "
                                    << ptqn << ". Message: " << e.what()
                                    << ". Skipping template.";
            continue;
        }

        /*
         * Now process all configuration points that were generated as
         * part of the instantiation.
         */
        for (const auto& cp : cps) {
            const auto cpqn(cp.name().qualified());
            const auto pair(std::make_pair(cpqn, cp));
            const auto inserted(r.configuration_points().insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_configuration_point
                                         << cpqn;
                BOOST_THROW_EXCEPTION(instantiation_exception(
                        duplicate_configuration_point + cpqn));
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Instantiated profile template: "
                             << ptqn << " Result: " << r;
    return r;
}

}
