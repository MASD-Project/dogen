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
#include "dogen/annotations/io/field_definition_types_io.hpp"
#include "dogen/annotations/io/ownership_hierarchy_io.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/field_definition_types.hpp"
#include "dogen/annotations/types/instantiation_error.hpp"
#include "dogen/annotations/types/template_instantiator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.instantiator"));

const std::string empty;
const std::string empty_model_name("Model name cannot be empty. Formatter: ");
const std::string empty_facet_name("Facet name cannot be empty. Formatter: ");
const std::string empty_formatter_name("Formatter name cannot be empty");
const std::string field_not_instantiable(
    "Field definition cannot be instantiated: ");
const std::string empty_simple_name("Simple name cannot be empty.");
const std::string qualified_name_not_empty(
    "Qualified name must be empty. Field: ");
const std::string model_name_not_empty(
    "Field definition type is global template but model name is not empty. "
    "Field: ");
const std::string facet_name_not_empty(
    "Field definition type is facet template but facet name is not empty. "
    "Field: ");

const std::string formatter_name_not_empty(
    "Field definition type is formatter template but facet name is not empty. "
    "Field: ");
const std::string unsupported_definition_type(
    "Field definition type is not supported: ");

}

namespace dogen {
namespace annotations {

template_instantiator::
template_instantiator(const std::forward_list<ownership_hierarchy>& ohs)
    : ownership_hierarchies_(ohs),
      facet_names_by_model_name_(obtain_facet_names_by_model_name(ohs)) {

    BOOST_LOG_SEV(lg, debug) << "Initialised.";
    BOOST_LOG_SEV(lg, trace) << "Ownership hierarchies: " << ohs;
    BOOST_LOG_SEV(lg, debug) << "Facet names by model: "
                             << facet_names_by_model_name_;
}

std::unordered_map<std::string, std::unordered_set<std::string> >
template_instantiator::obtain_facet_names_by_model_name(
    const std::forward_list<ownership_hierarchy>& oh) const {
    std::unordered_map<std::string, std::unordered_set<std::string> > r;

    for (const auto& h : oh) {
        if (h.formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(instantiation_error(empty_formatter_name));
        }

        if (h.model_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_model_name << h.formatter_name();
            BOOST_THROW_EXCEPTION(
                instantiation_error(empty_model_name + h.formatter_name()));
        }

        if (h.facet_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_facet_name << h.formatter_name();
            BOOST_THROW_EXCEPTION(
                instantiation_error(empty_facet_name + h.formatter_name()));
        }

        r[h.model_name()].insert(h.facet_name());
    }
    return r;
}

bool template_instantiator::is_instantiable(const type& t) const {
    return
        t.definition_type() == field_definition_types::global_template ||
        t.definition_type() == field_definition_types::model_template ||
        t.definition_type() == field_definition_types::facet_template ||
        t.definition_type() == field_definition_types::formatter_template;
}

void template_instantiator::validate(const type& t) const {
    const auto sn(t.name().simple());
    if (t.name().simple().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple_name;
        BOOST_THROW_EXCEPTION(instantiation_error(empty_simple_name));
    }

    if (!is_instantiable(t)) {
        BOOST_LOG_SEV(lg, error) << field_not_instantiable << sn;
        BOOST_THROW_EXCEPTION(instantiation_error(field_not_instantiable + sn));
    }

    if (!t.name().qualified().empty()) {
        BOOST_LOG_SEV(lg, error) << qualified_name_not_empty << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_error(qualified_name_not_empty + sn));
    }

    if (t.definition_type() == field_definition_types::global_template) {
        if (!t.ownership_hierarchy().facet_name().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(facet_name_not_empty + sn));
        }

        if (!t.ownership_hierarchy().formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << formatter_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(formatter_name_not_empty + sn));
        }
    }

    if (t.definition_type() == field_definition_types::facet_template) {
        if (!t.ownership_hierarchy().facet_name().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(facet_name_not_empty + sn));
        }

        if (!t.ownership_hierarchy().formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << formatter_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(formatter_name_not_empty + sn));
        }
    }

    if (t.definition_type() == field_definition_types::formatter_template) {
        if (!t.ownership_hierarchy().formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << formatter_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(formatter_name_not_empty + sn));
        }
    }
}

std::list<type>
template_instantiator::instantiate_global_template(const type& t) const {
    std::list<type> r;

    for (const auto pair : facet_names_by_model_name_) {
        const auto model_name(pair.first);
        if (!t.ownership_hierarchy().model_name().empty() &&
            t.ownership_hierarchy().model_name() != model_name)
            continue;

        auto instance_type(t);
        instance_type.definition_type(field_definition_types::instance);
        instance_type.name().qualified(model_name + "." + t.name().simple());
        instance_type.ownership_hierarchy().model_name(model_name);
        instance_type.ownership_hierarchy().facet_name(empty);
        instance_type.ownership_hierarchy().formatter_name(empty);
        r.push_back(instance_type);

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            auto instance_type(t);
            const auto sn(t.name().simple());
            instance_type.name().qualified(facet_name + "." + sn);
            instance_type.definition_type(field_definition_types::instance);
            instance_type.ownership_hierarchy().model_name(model_name);
            instance_type.ownership_hierarchy().facet_name(facet_name);
            instance_type.ownership_hierarchy().formatter_name(empty);
            r.push_back(instance_type);
        }
    }

    for (const auto oh : ownership_hierarchies_) {
        if (!t.ownership_hierarchy().model_name().empty() &&
            t.ownership_hierarchy().model_name() != oh.model_name())
            continue;

        auto instance_type(t);
        instance_type.definition_type(field_definition_types::instance);

        const auto fn(oh.formatter_name());
        instance_type.name().qualified(fn + "." + t.name().simple());
        instance_type.ownership_hierarchy(oh);
        r.push_back(instance_type);
    }
    return r;
}

std::list<type>
template_instantiator::instantiate_facet_template(const type& t) const {
    std::list<type> r;
    for (const auto pair : facet_names_by_model_name_) {
        const auto model_name(pair.first);
        if (!t.ownership_hierarchy().model_name().empty() &&
            t.ownership_hierarchy().model_name() != model_name)
            continue;

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            auto instance_type(t);
            instance_type.definition_type(field_definition_types::instance);
            instance_type.name().qualified(facet_name + "." + t.name().simple());
            instance_type.ownership_hierarchy().model_name(model_name);
            instance_type.ownership_hierarchy().facet_name(facet_name);
            instance_type.ownership_hierarchy().formatter_name(empty);
            r.push_back(instance_type);
        }
    }
    return r;
}

std::list<type>
template_instantiator::instantiate_formatter_template(const type& t) const {
    std::list<type> r;
    for (const auto oh : ownership_hierarchies_) {
        if (!t.ownership_hierarchy().model_name().empty() &&
            t.ownership_hierarchy().model_name() != oh.model_name())
            continue;

        if (!t.ownership_hierarchy().facet_name().empty() &&
            t.ownership_hierarchy().facet_name() != oh.facet_name())
            continue;

        auto instance_type(t);
        instance_type.definition_type(field_definition_types::instance);

        const auto fn(oh.formatter_name());
        instance_type.name().qualified(fn + "." + t.name().simple());
        instance_type.ownership_hierarchy(oh);
        r.push_back(instance_type);
    }
    return r;
}

std::list<type>
template_instantiator::instantiate(const type& t) const {
    validate(t);

    BOOST_LOG_SEV(lg, debug) << "Instantiating template: " << t;

    std::list<type> r;
    const auto dt(t.definition_type());
    if (dt == field_definition_types::global_template)
        r = instantiate_global_template(t);
    else if (dt == field_definition_types::facet_template)
        r = instantiate_facet_template(t);
    else if (dt == field_definition_types::formatter_template)
        r = instantiate_formatter_template(t);
    else {
        BOOST_LOG_SEV(lg, error) << unsupported_definition_type << dt;
        BOOST_THROW_EXCEPTION(instantiation_error(unsupported_definition_type +
                boost::lexical_cast<std::string>(dt)));
    }

    BOOST_LOG_SEV(lg, debug) << "Instantiation result: " << r;
    return r;
}

} }
