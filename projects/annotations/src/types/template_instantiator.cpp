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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/annotations/io/template_kinds_io.hpp"
#include "dogen/annotations/io/archetype_location_io.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/io/type_template_io.hpp"
#include "dogen/annotations/io/entry_template_io.hpp"
#include "dogen/annotations/types/template_kinds.hpp"
#include "dogen/annotations/types/value_factory.hpp"
#include "dogen/annotations/types/instantiation_error.hpp"
#include "dogen/annotations/types/template_instantiator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.template_instantiator"));

const std::string empty;
const std::string empty_model_name("Model name cannot be empty. Formatter: ");
const std::string empty_facet_name("Facet name cannot be empty. Formatter: ");
const std::string empty_formatter_name("Formatter name cannot be empty");
const std::string template_not_instantiable(
    "Template cannot be instantiated: ");
const std::string empty_simple_name("Simple name cannot be empty.");
const std::string qualified_name_not_empty(
    "Qualified name must be empty. Template: ");
const std::string model_name_not_empty(
    "Template is global template but model name is not empty. Template: ");
const std::string facet_name_not_empty(
    "Template is facet template but facet name is not empty. Template: ");
const std::string formatter_name_not_empty(
    "Template is formatter template but facet name is not empty. Template: ");
const std::string unsupported_template_kind(
    "Template is not supported: ");
const std::string missing_type("Type not found: ");

}

namespace dogen {
namespace annotations {

template_instantiator::
template_instantiator(const ownership_hierarchy_repository& ohrp)
    : repository_(ohrp) { }

void template_instantiator::validate(const archetype_location& oh,
    const name& n, const template_kinds tk) const {
    const auto sn(n.simple());
    if (sn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple_name;
        BOOST_THROW_EXCEPTION(instantiation_error(empty_simple_name));
    }

    if (!is_instantiable(tk)) {
        BOOST_LOG_SEV(lg, error) << template_not_instantiable << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_error(template_not_instantiable + sn));
    }

    if (!n.qualified().empty()) {
        BOOST_LOG_SEV(lg, error) << qualified_name_not_empty << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_error(qualified_name_not_empty + sn));
    }

    if (tk == template_kinds::global_template) {
        if (!oh.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(facet_name_not_empty + sn));
        }

        if (!oh.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << formatter_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(formatter_name_not_empty + sn));
        }
    }

    if (tk == template_kinds::facet_template) {
        if (!oh.facet().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(facet_name_not_empty + sn));
        }

        if (!oh.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << formatter_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(formatter_name_not_empty + sn));
        }
    }

    if (tk == template_kinds::formatter_template) {
        if (!oh.archetype().empty()) {
            BOOST_LOG_SEV(lg, error) << formatter_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(formatter_name_not_empty + sn));
        }
    }
}

type template_instantiator::to_type(const type_template& tt) const {
    type r;
    r.name(tt.name());
    r.value_type(tt.value_type());
    r.scope(tt.scope());
    r.ownership_hierarchy(tt.ownership_hierarchy());
    r.default_value(tt.default_value());
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

std::list<type> template_instantiator::
instantiate_global_template(const type_template& tt) const {
    std::list<type> r;

    for (const auto pair : repository_.facet_names_by_model_name()) {
        const auto model_name(pair.first);
        if (!tt.ownership_hierarchy().kernel().empty() &&
            tt.ownership_hierarchy().kernel() != model_name)
            continue;

        auto t(to_type(tt));
        t.name().qualified(model_name + "." + tt.name().simple());
        t.ownership_hierarchy().kernel(model_name);
        t.ownership_hierarchy().facet(empty);
        t.ownership_hierarchy().archetype(empty);
        r.push_back(t);

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            auto t(to_type(tt));
            const auto sn(tt.name().simple());
            t.name().qualified(facet_name + "." + sn);
            t.ownership_hierarchy().kernel(model_name);
            t.ownership_hierarchy().facet(facet_name);
            t.ownership_hierarchy().archetype(empty);
            r.push_back(t);
        }
    }

    for (const auto oh : repository_.ownership_hierarchies()) {
        if (!tt.ownership_hierarchy().kernel().empty() &&
            tt.ownership_hierarchy().kernel() != oh.kernel())
            continue;

        auto t(to_type(tt));

        const auto fn(oh.archetype());
        t.name().qualified(fn + "." + tt.name().simple());
        t.ownership_hierarchy(oh);
        r.push_back(t);
    }
    return r;
}

std::list<type> template_instantiator::
instantiate_facet_template(const type_template& tt) const {
    std::list<type> r;
    for (const auto pair : repository_.facet_names_by_model_name()) {
        const auto model_name(pair.first);
        if (!tt.ownership_hierarchy().kernel().empty() &&
            tt.ownership_hierarchy().kernel() != model_name)
            continue;

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            auto t(to_type(tt));
            t.name().qualified(facet_name + "." + tt.name().simple());
            t.ownership_hierarchy().kernel(model_name);
            t.ownership_hierarchy().facet(facet_name);
            t.ownership_hierarchy().archetype(empty);
            r.push_back(t);
        }
    }
    return r;
}

std::list<type> template_instantiator::
instantiate_formatter_template(const type_template& tt) const {
    std::list<type> r;
    for (const auto oh : repository_.ownership_hierarchies()) {
        if (!tt.ownership_hierarchy().kernel().empty() &&
            tt.ownership_hierarchy().kernel() != oh.kernel())
            continue;

        if (!tt.ownership_hierarchy().facet().empty() &&
            tt.ownership_hierarchy().facet() != oh.facet())
            continue;

        auto t(to_type(tt));
        const auto fn(oh.archetype());
        t.name().qualified(fn + "." + t.name().simple());
        t.ownership_hierarchy(oh);
        r.push_back(t);
    }
    return r;
}

std::list<std::pair<std::string, boost::shared_ptr<value>>>
template_instantiator::instantiate_global_template(
    const type_repository& trp, const entry_template& et) const {
    std::list<std::pair<std::string, boost::shared_ptr<value>>> r;
    for (const auto pair : repository_.facet_names_by_model_name()) {
        const auto model_name(pair.first);
        if (!et.ownership_hierarchy().kernel().empty() &&
            et.ownership_hierarchy().kernel() != model_name)
            continue;

        std::pair<std::string, boost::shared_ptr<value>> entry;
        entry.first = model_name + "." + et.name().simple();
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

    for (const auto oh : repository_.ownership_hierarchies()) {
        if (!et.ownership_hierarchy().kernel().empty() &&
            et.ownership_hierarchy().kernel() != oh.kernel())
            continue;

        std::pair<std::string, boost::shared_ptr<value>> entry;
        const auto fn(oh.archetype());
        entry.first = fn + "." + et.name().simple();
        entry.second = to_value(trp, entry.first, et);
        r.push_back(entry);
    }

    return r;
}

std::list<std::pair<std::string, boost::shared_ptr<value>>>
template_instantiator::instantiate_facet_template(
    const type_repository& trp, const entry_template& et) const {
    std::list<std::pair<std::string, boost::shared_ptr<value>>> r;

    for (const auto pair : repository_.facet_names_by_model_name()) {
        const auto model_name(pair.first);
        if (!et.ownership_hierarchy().kernel().empty() &&
            et.ownership_hierarchy().kernel() != model_name)
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
template_instantiator::instantiate_formatter_template(
    const type_repository& trp, const entry_template& et) const {
    std::list<std::pair<std::string, boost::shared_ptr<value>>> r;

    for (const auto oh : repository_.ownership_hierarchies()) {
        if (!et.ownership_hierarchy().kernel().empty() &&
            et.ownership_hierarchy().kernel() != oh.kernel())
            continue;

        if (!et.ownership_hierarchy().facet().empty() &&
            et.ownership_hierarchy().facet() != oh.facet())
            continue;

        std::pair<std::string, boost::shared_ptr<value>> entry;
        const auto fn(oh.archetype());
        entry.first = fn + "." + et.name().simple();
        entry.second = to_value(trp, entry.first, et);
        r.push_back(entry);
    }

    return r;
}

bool template_instantiator::is_instantiable(const template_kinds tk) const {
    return
        tk == template_kinds::global_template ||
        tk == template_kinds::model_template ||
        tk == template_kinds::facet_template ||
        tk == template_kinds::formatter_template;
}

std::list<type>
template_instantiator::instantiate(const type_template& tt) const {
    validate(tt.ownership_hierarchy(), tt.name(), tt.kind());

    BOOST_LOG_SEV(lg, debug) << "Instantiating template: " << tt;

    std::list<type> r;
    const auto tk(tt.kind());
    if (tk == template_kinds::global_template)
        r = instantiate_global_template(tt);
    else if (tk == template_kinds::facet_template)
        r = instantiate_facet_template(tt);
    else if (tk == template_kinds::formatter_template)
        r = instantiate_formatter_template(tt);
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

    validate(et.ownership_hierarchy(), et.name(), et.kind());

    BOOST_LOG_SEV(lg, debug) << "Instantiating template: " << et;

    std::list<std::pair<std::string, boost::shared_ptr<value>>> r;
    const auto tk(et.kind());
    if (tk == template_kinds::global_template)
        r = instantiate_global_template(trp, et);
    else if (tk == template_kinds::facet_template)
        r = instantiate_facet_template(trp, et);
    else if (tk == template_kinds::formatter_template)
        r = instantiate_formatter_template(trp, et);
    else {
        BOOST_LOG_SEV(lg, error) << unsupported_template_kind << tk;
        BOOST_THROW_EXCEPTION(instantiation_error(unsupported_template_kind +
                boost::lexical_cast<std::string>(tk)));
    }

    BOOST_LOG_SEV(lg, debug) << "Instantiation result: " << r;
    return r;
}

} }
