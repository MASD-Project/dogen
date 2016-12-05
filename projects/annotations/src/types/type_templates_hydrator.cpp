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
#include <istream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/value_types_io.hpp"
#include "dogen/annotations/io/template_kinds_io.hpp"
#include "dogen/annotations/types/value_factory.hpp"
#include "dogen/annotations/types/hydration_error.hpp"
#include "dogen/annotations/types/type_templates_hydrator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("annotations.type_templates_hydrator"));

const std::string empty;
const std::string name_key("name");
const std::string name_simple_key("simple");
const std::string name_qualified_key("qualified");
const std::string archetype_location_key("archetype_location");
const std::string archetype_location_kernel_key("kernel");
const std::string archetype_location_facet_key("facet");
const std::string archetype_location_archetype_key("archetype");
const std::string value_type_key("value_type");
const std::string template_kind_key("template_kind");
const std::string scope_key("scope");
const std::string default_value_key("default_value");

const std::string scope_any("any");
const std::string scope_not_applicable("not_applicable");
const std::string scope_root_module("root_module");
const std::string scope_any_module("any_module");
const std::string scope_entity("entity");
const std::string scope_property("property");
const std::string scope_operation("operation");

const std::string value_type_text("text");
const std::string value_type_text_collection("text_collection");
const std::string value_type_number("number");
const std::string value_type_boolean("boolean");
const std::string value_type_kvp("key_value_pair");

const std::string template_kind_instance("instance");
const std::string template_kind_global_template("global_template");
const std::string template_kind_kernel_template("kernel_template");
const std::string template_kind_facet_template("facet_template");
const std::string template_kind_formatter_template(
    "formatter_template");

const std::string invalid_json_file("Failed to parse JSON file");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string template_has_no_name("Template has no 'name'.");
const std::string template_has_no_hierarchy(
    "Template has no ownership hierarchy.");
const std::string invalid_scope("Invalid or unsupported scope type: ");
const std::string invalid_value_type("Invalid or unsupported value type: ");
const std::string invalid_template_kind(
    "Invalid or unsupported template kind: ");

}

namespace dogen {
namespace annotations {

scope_types type_templates_hydrator::to_scope_type(const std::string& s) const {
    if (s == scope_any)
        return scope_types::any;
    else if (s == scope_not_applicable)
        return scope_types::not_applicable;
    else if (s == scope_root_module)
        return scope_types::root_module;
    else if (s == scope_any_module)
        return scope_types::any_module;
    else if (s == scope_entity)
        return scope_types::entity;
    else if (s == scope_property)
        return scope_types::property;
    else if (s == scope_operation)
        return scope_types::operation;

    BOOST_LOG_SEV(lg, error) << invalid_scope << "'" << s << "'";
    BOOST_THROW_EXCEPTION(hydration_error(invalid_scope + s));
}

value_types type_templates_hydrator::to_value_type(const std::string& s) const {
    if (s == value_type_text)
        return value_types::text;
    else if (s == value_type_text_collection)
        return value_types::text_collection;
    else if (s == value_type_number)
        return value_types::number;
    else if (s == value_type_boolean)
        return value_types::boolean;
    else if (s == value_type_kvp)
        return value_types::key_value_pair;

    BOOST_LOG_SEV(lg, error) << invalid_value_type << "'" << s << "'";
    BOOST_THROW_EXCEPTION(hydration_error(invalid_value_type + s));
}

template_kinds
type_templates_hydrator::to_template_kind(const std::string& s) const {
    if (s == template_kind_instance)
        return template_kinds::instance;
    if (s == template_kind_global_template)
        return template_kinds::global_template;
    if (s == template_kind_kernel_template)
        return template_kinds::kernel_template;
    if (s == template_kind_facet_template)
        return template_kinds::facet_template;
    if (s == template_kind_formatter_template)
        return template_kinds::formatter_template;

    BOOST_LOG_SEV(lg, error) << invalid_template_kind << "'" << s << "'";
    BOOST_THROW_EXCEPTION(hydration_error(invalid_template_kind + s));
}

boost::shared_ptr<value>
type_templates_hydrator::create_value(const value_types vt,
    const std::string& v) const {

    value_factory f;
    switch (vt) {
    case value_types::text: return f.make_text(v);
    case value_types::boolean: return f.make_boolean(v);
    case value_types::number: return f.make_number(v);
    default:
        BOOST_LOG_SEV(lg, error) << invalid_value_type << "'" << vt << "'";
        BOOST_THROW_EXCEPTION(hydration_error(invalid_value_type +
                boost::lexical_cast<std::string>(vt)));
    }
}

name type_templates_hydrator::
read_name(const boost::property_tree::ptree& pt) const {
    name r;
    r.simple(pt.get<std::string>(name_simple_key));

    const auto qualified(pt.get_optional<std::string>(name_qualified_key));
    if (qualified)
        r.qualified(*qualified);

    return r;
}

archetype_location type_templates_hydrator::
read_archetype_location(const boost::property_tree::ptree& pt) const {
    archetype_location r;

    r.kernel(pt.get<std::string>(archetype_location_kernel_key, empty));
    r.facet(pt.get<std::string>(archetype_location_facet_key, empty));
    r.archetype(pt.get<std::string>(archetype_location_archetype_key, empty));
    return r;
}

std::list<type_template>
type_templates_hydrator::read_stream(std::istream& s) const {
    using namespace boost::property_tree;
    ptree pt;
    read_json(s, pt);

    std::list<type_template> r;
    for (auto i(pt.begin()); i != pt.end(); ++i) {
        type_template tt ;
        const auto& tt_pt(i->second);

        auto j(tt_pt.find(name_key));
        if (j == tt_pt.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << template_has_no_name;
            BOOST_THROW_EXCEPTION(hydration_error(template_has_no_name));
        }
        tt.name(read_name(j->second));

        j = tt_pt.find(archetype_location_key);
        if (j == tt_pt.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << template_has_no_hierarchy;
            BOOST_THROW_EXCEPTION(hydration_error(template_has_no_hierarchy));
        }
        tt.archetype_location(read_archetype_location(j->second));
        tt.value_type(to_value_type(tt_pt.get<std::string>(value_type_key)));
        tt.kind(to_template_kind(tt_pt.get<std::string>(template_kind_key)));
        tt.scope(to_scope_type(tt_pt.get<std::string>(scope_key)));

        const auto dv(tt_pt.get_optional<std::string>(default_value_key));
        if (dv)
            tt.default_value(create_value(tt.value_type(), *dv));

        r.push_front(tt);
    }
    return r;
}

std::list<type_template>
type_templates_hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, trace) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
        auto r(read_stream(s));
        BOOST_LOG_SEV(lg, trace) << "Parsed JSON stream successfully.";
        return r;
    } catch (const json_parser_error& e) {
        BOOST_LOG_SEV(lg, error) << invalid_json_file << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_json_file + e.what()));
    } catch (const ptree_bad_data& e) {
        BOOST_LOG_SEV(lg, error) << invalid_option_in_json_file << ": "
                                 << e.what();
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_option_in_json_file + e.what()));
    } catch (const ptree_bad_path& e) {
        BOOST_LOG_SEV(lg, error) << invalid_path << ": " << e.what();
        BOOST_THROW_EXCEPTION(hydration_error(invalid_path + e.what()));
    }
}

std::list<type_template> type_templates_hydrator::
hydrate(const boost::filesystem::path& p) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << p.generic_string();
    boost::filesystem::ifstream s(p);
    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
}

} }
