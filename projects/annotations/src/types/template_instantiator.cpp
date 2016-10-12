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
#include "dogen/annotations/io/ownership_hierarchy_io.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/io/type_template_io.hpp"
#include "dogen/annotations/types/template_kinds.hpp"
#include "dogen/annotations/types/instantiation_error.hpp"
#include "dogen/annotations/types/template_instantiator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.instantiator"));

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

std::unordered_map<std::string, std::unordered_set<std::string>>
template_instantiator::obtain_facet_names_by_model_name(
    const std::forward_list<ownership_hierarchy>& ohs) const {
    std::unordered_map<std::string, std::unordered_set<std::string> > r;

    for (const auto& oh : ohs) {
        if (oh.formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(instantiation_error(empty_formatter_name));
        }

        if (oh.model_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_model_name << oh.formatter_name();
            BOOST_THROW_EXCEPTION(
                instantiation_error(empty_model_name + oh.formatter_name()));
        }

        if (oh.facet_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_facet_name << oh.formatter_name();
            BOOST_THROW_EXCEPTION(
                instantiation_error(empty_facet_name + oh.formatter_name()));
        }

        r[oh.model_name()].insert(oh.facet_name());
    }
    return r;
}

bool template_instantiator::is_instantiable(const type_template& tt) const {
    return
        tt.kind() == template_kinds::global_template ||
        tt.kind() == template_kinds::model_template ||
        tt.kind() == template_kinds::facet_template ||
        tt.kind() == template_kinds::formatter_template;
}

void template_instantiator::validate(const type_template& tt) const {
    const auto sn(tt.name().simple());
    if (tt.name().simple().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple_name;
        BOOST_THROW_EXCEPTION(instantiation_error(empty_simple_name));
    }

    if (!is_instantiable(tt)) {
        BOOST_LOG_SEV(lg, error) << template_not_instantiable << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_error(template_not_instantiable + sn));
    }

    if (!tt.name().qualified().empty()) {
        BOOST_LOG_SEV(lg, error) << qualified_name_not_empty << sn;
        BOOST_THROW_EXCEPTION(
            instantiation_error(qualified_name_not_empty + sn));
    }

    if (tt.kind() == template_kinds::global_template) {
        if (!tt.ownership_hierarchy().facet_name().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(facet_name_not_empty + sn));
        }

        if (!tt.ownership_hierarchy().formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << formatter_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(formatter_name_not_empty + sn));
        }
    }

    if (tt.kind() == template_kinds::facet_template) {
        if (!tt.ownership_hierarchy().facet_name().empty()) {
            BOOST_LOG_SEV(lg, error) << facet_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(facet_name_not_empty + sn));
        }

        if (!tt.ownership_hierarchy().formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << formatter_name_not_empty << sn;
            BOOST_THROW_EXCEPTION(
                instantiation_error(formatter_name_not_empty + sn));
        }
    }

    if (tt.kind() == template_kinds::formatter_template) {
        if (!tt.ownership_hierarchy().formatter_name().empty()) {
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

std::list<type> template_instantiator::
instantiate_global_template(const type_template& tt) const {
    std::list<type> r;

    for (const auto pair : facet_names_by_model_name_) {
        const auto model_name(pair.first);
        if (!tt.ownership_hierarchy().model_name().empty() &&
            tt.ownership_hierarchy().model_name() != model_name)
            continue;

        auto t(to_type(tt));
        t.name().qualified(model_name + "." + tt.name().simple());
        t.ownership_hierarchy().model_name(model_name);
        t.ownership_hierarchy().facet_name(empty);
        t.ownership_hierarchy().formatter_name(empty);
        r.push_back(t);

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            auto t(to_type(tt));
            const auto sn(tt.name().simple());
            t.name().qualified(facet_name + "." + sn);
            t.ownership_hierarchy().model_name(model_name);
            t.ownership_hierarchy().facet_name(facet_name);
            t.ownership_hierarchy().formatter_name(empty);
            r.push_back(t);
        }
    }

    for (const auto oh : ownership_hierarchies_) {
        if (!tt.ownership_hierarchy().model_name().empty() &&
            tt.ownership_hierarchy().model_name() != oh.model_name())
            continue;

        auto t(to_type(tt));

        const auto fn(oh.formatter_name());
        t.name().qualified(fn + "." + tt.name().simple());
        t.ownership_hierarchy(oh);
        r.push_back(t);
    }
    return r;
}

std::list<type> template_instantiator::
instantiate_facet_template(const type_template& tt) const {
    std::list<type> r;
    for (const auto pair : facet_names_by_model_name_) {
        const auto model_name(pair.first);
        if (!tt.ownership_hierarchy().model_name().empty() &&
            tt.ownership_hierarchy().model_name() != model_name)
            continue;

        const auto& facet_names(pair.second);
        for (const auto facet_name : facet_names) {
            auto t(to_type(tt));
            t.name().qualified(facet_name + "." + tt.name().simple());
            t.ownership_hierarchy().model_name(model_name);
            t.ownership_hierarchy().facet_name(facet_name);
            t.ownership_hierarchy().formatter_name(empty);
            r.push_back(t);
        }
    }
    return r;
}

std::list<type> template_instantiator::
instantiate_formatter_template(const type_template& tt) const {
    std::list<type> r;
    for (const auto oh : ownership_hierarchies_) {
        if (!tt.ownership_hierarchy().model_name().empty() &&
            tt.ownership_hierarchy().model_name() != oh.model_name())
            continue;

        if (!tt.ownership_hierarchy().facet_name().empty() &&
            tt.ownership_hierarchy().facet_name() != oh.facet_name())
            continue;

        auto t(to_type(tt));
        const auto fn(oh.formatter_name());
        t.name().qualified(fn + "." + t.name().simple());
        t.ownership_hierarchy(oh);
        r.push_back(t);
    }
    return r;
}

std::list<type>
template_instantiator::instantiate(const type_template& tt) const {
    validate(tt);

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

} }
