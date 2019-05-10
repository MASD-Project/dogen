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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.variability/io/meta_model/value_type_io.hpp"
#include "masd.dogen.variability/io/meta_model/template_kind_io.hpp"
#include "masd.dogen.variability/types/helpers/value_factory.hpp"
#include "masd.dogen.variability/types/helpers/hydration_exception.hpp"
#include "masd.dogen.variability/types/helpers/feature_template_hydrator.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("variability.helpers.feature_template_hydrator"));

const std::string empty;
const std::string name_key("name");
const std::string name_simple_key("simple");
const std::string name_qualified_key("qualified");
const std::string archetype_location_key("archetype_location");
const std::string archetype_location_kernel_key("kernel");
const std::string archetype_location_backend_key("backend");
const std::string archetype_location_facet_key("facet");
const std::string archetype_location_archetype_key("archetype");
const std::string value_type_key("value_type");
const std::string template_kind_key("template_kind");
const std::string scope_key("scope");
const std::string default_value_key("default_value");

const std::string scope_any("any");
const std::string scope_any_module("any");
const std::string scope_root_module("root_module");
const std::string scope_entity("entity");
const std::string scope_property("property");
const std::string scope_operation("operation");

const std::string value_type_text("text");
const std::string value_type_text_collection("text_collection");
const std::string value_type_number("number");
const std::string value_type_boolean("boolean");
const std::string value_type_kvp("key_value_pair");

const std::string template_kind_instance("instance");
const std::string template_kind_recursive_template("recursive_template");
const std::string template_kind_backend_template("backend_template");
const std::string template_kind_facet_template("facet_template");
const std::string template_kind_archetype_template("archetype_template");

const std::string failed_to_open_file("Failed to open file: ");
const std::string invalid_json_file("Failed to parse JSON file");
const std::string invalid_value_in_json("Failed to value in JSON: ");
const std::string invalid_path("Failed to find path: ");
const std::string template_has_no_name("Template has no 'name'.");
const std::string template_has_no_hierarchy(
    "Template has no ownership hierarchy.");
const std::string invalid_scope("Invalid or unsupported scope type: ");
const std::string invalid_value_type("Invalid or unsupported value type: ");
const std::string invalid_template_kind(
    "Invalid or unsupported template kind: ");

}

namespace masd::dogen::variability::helpers {

meta_model::binding_point
feature_template_hydrator::to_binding_point(const std::string& s) const {
    using meta_model::binding_point;
    if (s == scope_any)
        return binding_point::any;
    else if (s == scope_root_module)
        return binding_point::global;
    else if (s == scope_any_module)
        return binding_point::element;
    else if (s == scope_entity)
        return binding_point::element;
    else if (s == scope_property)
        return binding_point::property;
    else if (s == scope_operation)
        return binding_point::operation;

    BOOST_LOG_SEV(lg, error) << invalid_scope << "'" << s << "'";
    BOOST_THROW_EXCEPTION(hydration_exception(invalid_scope + s));
}

meta_model::value_type
feature_template_hydrator::to_value_type(const std::string& s) const {
    using meta_model::value_type;
    if (s == value_type_text)
        return value_type::text;
    else if (s == value_type_text_collection)
        return value_type::text_collection;
    else if (s == value_type_number)
        return value_type::number;
    else if (s == value_type_boolean)
        return value_type::boolean;
    else if (s == value_type_kvp)
        return value_type::key_value_pair;

    BOOST_LOG_SEV(lg, error) << invalid_value_type << "'" << s << "'";
    BOOST_THROW_EXCEPTION(hydration_exception(invalid_value_type + s));
}

meta_model::template_kind
feature_template_hydrator::to_template_kind(const std::string& s) const {
    using meta_model::template_kind;
    if (s == template_kind_instance)
        return template_kind::instance;
    if (s == template_kind_recursive_template)
        return template_kind::recursive_template;
    if (s == template_kind_backend_template)
        return template_kind::backend_template;
    if (s == template_kind_facet_template)
        return template_kind::facet_template;
    if (s == template_kind_archetype_template)
        return template_kind::archetype_template;

    BOOST_LOG_SEV(lg, error) << invalid_template_kind << "'" << s << "'";
    BOOST_THROW_EXCEPTION(hydration_exception(invalid_template_kind + s));
}

boost::shared_ptr<meta_model::value> feature_template_hydrator::
create_value(const meta_model::value_type vt, const std::string& v) const {
    value_factory f;

    using meta_model::value_type;
    switch (vt) {
    case value_type::text: return f.make_text(v);
    case value_type::boolean: return f.make_boolean(v);
    case value_type::number: return f.make_number(v);
    default: {
        const auto s(boost::lexical_cast<std::string>(vt));
        BOOST_LOG_SEV(lg, error) << invalid_value_type << "'" << s << "'";
        BOOST_THROW_EXCEPTION(hydration_exception(invalid_value_type + s));
    } }
}

meta_model::name feature_template_hydrator::
read_name(const boost::property_tree::ptree& pt) const {
    meta_model::name r;
    r.simple(pt.get<std::string>(name_simple_key));

    const auto qualified(pt.get_optional<std::string>(name_qualified_key));
    if (qualified)
        r.qualified(*qualified);

    return r;
}

archetypes::location feature_template_hydrator::
read_archetype_location(const boost::property_tree::ptree& pt) const {
    archetypes::location r;
    r.kernel(pt.get<std::string>(archetype_location_kernel_key, empty));
    r.backend(pt.get<std::string>(archetype_location_backend_key, empty));
    r.facet(pt.get<std::string>(archetype_location_facet_key, empty));
    r.archetype(pt.get<std::string>(archetype_location_archetype_key, empty));
    return r;
}

std::list<meta_model::feature_template>
feature_template_hydrator::read_stream(std::istream& s) const {
    boost::property_tree::ptree pt;
    read_json(s, pt);

    std::list<meta_model::feature_template> r;
    for (auto i(pt.begin()); i != pt.end(); ++i) {
        meta_model::feature_template ft ;
        const auto& tt_pt(i->second);

        auto j(tt_pt.find(name_key));
        if (j == tt_pt.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << template_has_no_name;
            BOOST_THROW_EXCEPTION(hydration_exception(template_has_no_name));
        }
        ft.name(read_name(j->second));

        j = tt_pt.find(archetype_location_key);
        if (j == tt_pt.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << template_has_no_hierarchy;
            BOOST_THROW_EXCEPTION(
                hydration_exception(template_has_no_hierarchy));
        }
        ft.location(read_archetype_location(j->second));
        ft.value_type(to_value_type(tt_pt.get<std::string>(value_type_key)));
        ft.kind(to_template_kind(tt_pt.get<std::string>(template_kind_key)));
        ft.binding_point(to_binding_point(tt_pt.get<std::string>(scope_key)));

        const auto dv(tt_pt.get_optional<std::string>(default_value_key));
        if (dv)
            ft.default_value(create_value(ft.value_type(), *dv));

        r.push_front(ft);
    }
    return r;
}

std::list<meta_model::feature_template>
feature_template_hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, trace) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
        const std::list<meta_model::feature_template> r(read_stream(s));
        BOOST_LOG_SEV(lg, trace) << "Parsed JSON stream successfully.";
        return r;
    } catch (const json_parser_error& e) {
        const auto w(e.what());
        BOOST_LOG_SEV(lg, error) << invalid_json_file << w;
        BOOST_THROW_EXCEPTION(hydration_exception(invalid_json_file + w));
    } catch (const ptree_bad_data& e) {
        BOOST_LOG_SEV(lg, error) << invalid_value_in_json << e.what();
        BOOST_THROW_EXCEPTION(
            hydration_exception(invalid_value_in_json + e.what()));
    } catch (const ptree_bad_path& e) {
        BOOST_LOG_SEV(lg, error) << invalid_path << e.what();
        BOOST_THROW_EXCEPTION(hydration_exception(invalid_path + e.what()));
    }
}

std::list<meta_model::feature_template> feature_template_hydrator::
hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << gs;

    boost::filesystem::ifstream s(p);
    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << gs;
        BOOST_THROW_EXCEPTION(hydration_exception(failed_to_open_file + gs));
    }

    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
}

}
