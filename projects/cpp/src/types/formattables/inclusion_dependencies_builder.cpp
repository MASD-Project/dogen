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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_dependencies_builder"));

const auto empty_list = std::list<std::string> {};
const std::string bool_type("bool");
const std::string double_type("double");
const std::string float_type("float");
const std::string pair_type("pair");
const std::string string_type("string");
const std::string variant_type("variant");
const std::string ptree_type("ptree");
const std::string path_type("path");

const std::string empty_directive("Cannot add empty include directive.");
const std::string qname_not_found("Cannot find qname: ");
const std::string formatter_name_not_found("Cannot find formatter name: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_dependencies_builder::
inclusion_dependencies_builder(const enablement_repository& erp,
    const inclusion_directives_repository& idrp,
    const integrated_facets_repository& ifrp)
    : enablement_repository_(erp),
      directives_repository_(idrp),
      integrated_facets_repository_(ifrp) {}

boost::optional<std::string>
inclusion_dependencies_builder::get_inclusion_directive(
    const sml::qname& qn,
    const std::string& formatter_name) const {

    const auto& idqn(directives_repository_.inclusion_directives_by_qname());
    const auto i(idqn.find(qn));
    if (i == idqn.end())
        return boost::optional<std::string>();

    const auto j(i->second.find(formatter_name));
    if (j == i->second.end())
        return boost::optional<std::string>();

    return j->second;
}

inclusion_dependencies_builder::special_includes
inclusion_dependencies_builder::make_special_includes(
    const sml::object& o) const {
    special_includes r;
    const auto lambda([&](const sml::relationship_types rt) {
            const auto i(o.relationships().find(rt));
            if (i == o.relationships().end())
                return;

            for (const auto& qn : i->second) {
                const auto sn(qn.simple_name());
                if (sn == bool_type || sn == double_type || sn == float_type)
                    r.requires_stream_manipulators = true;
                else if (sn == string_type)
                    r.has_std_string = true;
                else if (sn == variant_type)
                    r.has_variant = true;
                else if (sn == pair_type)
                    r.has_std_pair = true;
                else if (sn == ptree_type)
                    r.has_ptree = true;
                else if (sn == path_type)
                    r.has_path = true;
            }
        });

    using rt = dogen::sml::relationship_types;
    lambda(rt::regular_associations);
    lambda(rt::weak_associations);

    return r;
}

bool inclusion_dependencies_builder::is_enabled(const sml::qname& qn,
    const std::string& formatter_name) const {

    const auto& eqn(enablement_repository_.enablement_by_qname());
    const auto i(eqn.find(qn));
    if (i == eqn.end()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << qname_not_found << n;
        BOOST_THROW_EXCEPTION(building_error(qname_not_found + n));
    }

    const auto j(i->second.find(formatter_name));
    if (j == i->second.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_name_not_found << formatter_name;
        BOOST_THROW_EXCEPTION(
            building_error(formatter_name_not_found + formatter_name));
    }

    const bool r(j->second);
    if (!r) {
        BOOST_LOG_SEV(lg, debug) << "Formatter disabled. Formatter: "
                                 << formatter_name << " on type: "
                                 << sml::string_converter::convert(qn) << "'";
    }
    return r;
}

bool inclusion_dependencies_builder::is_integrated(
    const std::string& formatter_name, const std::string& facet_name) const {
    const auto& ifrp(integrated_facets_repository_);
    const auto& iffn(ifrp.integrated_facets_by_formatter_name());

    const auto i(iffn.find(formatter_name));
    if (i == iffn.end())
        return false;

    const auto j(i->second.find(facet_name));
    const bool r(j != i->second.end());

    if (!r) {
        BOOST_LOG_SEV(lg, debug) << "Facet not integrated. "
                                 << " Facet: '" << facet_name << "'";
    }
    return r;
}

void inclusion_dependencies_builder::
add(const std::string& inclusion_directive) {
    if (inclusion_directive.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_directive;
        BOOST_THROW_EXCEPTION(building_error(empty_directive));
    }
    inclusion_dependencies_.push_back(inclusion_directive);
}

void inclusion_dependencies_builder::
add(const sml::qname& qn, const std::string& formatter_name) {
    if (!is_enabled(qn, formatter_name))
        return;

    const auto id(get_inclusion_directive(qn, formatter_name));
    if (id)
        add(*id);
}

void inclusion_dependencies_builder::
add(const std::list<sml::qname>& qn, const std::string& formatter_name) {
    for (const auto& n : qn)
        add(n, formatter_name);
}

void inclusion_dependencies_builder::add(const sml::object& o,
    const sml::relationship_types rt,
    const std::string& formatter_name) {

    const auto i(o.relationships().find(rt));
    if (i == o.relationships().end())
        return;

    add(i->second, formatter_name);
}

std::list<std::string> inclusion_dependencies_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Built inclusion dependencies for formatter.";
    BOOST_LOG_SEV(lg, debug) << "Result: " << inclusion_dependencies_;

    return inclusion_dependencies_;
}

} } }
