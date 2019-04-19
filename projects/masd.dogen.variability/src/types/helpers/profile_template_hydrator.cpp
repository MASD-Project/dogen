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
#include "masd.dogen.variability/types/helpers/hydration_exception.hpp"
#include "masd.dogen.variability/types/helpers/profile_template_hydrator.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("annotations.type_templates_hydrator"));

const std::string empty;
const std::string name_key("name");
const std::string parents_key("parents");
const std::string labels_key("labels");
const std::string templates_key("templates");
const std::string template_kind_key("template_kind");
const std::string name_simple_key("simple");
const std::string name_qualified_key("qualified");
const std::string archetype_location_key("archetype_location");
const std::string archetype_location_backend_key("backend");
const std::string archetype_location_facet_key("facet");
const std::string archetype_location_archetype_key("archetype");
const std::string untyped_value_key("untyped_value");

const std::string template_kind_instance("instance");
const std::string template_kind_recursive_template("recursive_template");
const std::string template_kind_backend_template("backend_template");
const std::string template_kind_facet_template("facet_template");
const std::string template_kind_archetype_template("archetype_template");

const std::string failed_to_open_file("Failed to open file: ");
const std::string invalid_json_file("Failed to parse JSON file");
const std::string invalid_value_in_json("Failed to read JSON value: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string configuration_template_has_no_name(
    "Configuration_Template has no 'name'.");
const std::string template_has_no_name("Template has no 'name'.");
const std::string template_has_no_hierarchy(
    "Template has no ownership hierarchy.");
const std::string invalid_template_kind(
    "Invalid or unsupported template kind: ");
const std::string template_has_no_untyped_value(
    "Value template has no untyped value:");

}

namespace masd::dogen::variability::helpers {

meta_model::template_kind
profile_template_hydrator::to_template_kind(const std::string& s) const {
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

meta_model::name profile_template_hydrator::
read_name(const boost::property_tree::ptree& pt) const {
    meta_model::name r;
    r.simple(pt.get<std::string>(name_simple_key));

    const auto qualified(pt.get_optional<std::string>(name_qualified_key));
    if (qualified)
        r.qualified(*qualified);

    return r;
}

archetypes::location profile_template_hydrator::
read_archetype_location(const boost::property_tree::ptree& pt) const {
    archetypes::location r;

    r.backend(pt.get<std::string>(archetype_location_backend_key, empty));
    r.facet(pt.get<std::string>(archetype_location_facet_key, empty));
    r.archetype(pt.get<std::string>(archetype_location_archetype_key, empty));

    return r;
}

std::list<meta_model::configuration_point_template>
profile_template_hydrator::
read_templates(const boost::property_tree::ptree& pt) const {
    using meta_model::configuration_point_template;
    std::list<configuration_point_template> r;
    for (auto i(pt.begin()); i != pt.end(); ++i) {
        configuration_point_template cpt;
        const auto& cpt_pt(i->second);

        auto j(cpt_pt.find(name_key));
        if (j == cpt_pt.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << template_has_no_name;
            BOOST_THROW_EXCEPTION(hydration_exception(template_has_no_name));
        }
        cpt.name(read_name(j->second));

        j = cpt_pt.find(archetype_location_key);
        if (j == cpt_pt.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << template_has_no_hierarchy;
            BOOST_THROW_EXCEPTION(
                hydration_exception(template_has_no_hierarchy));
        }
        cpt.location(read_archetype_location(j->second));

        cpt.kind(to_template_kind(cpt_pt.get<std::string>(template_kind_key)));

        j = cpt_pt.find(untyped_value_key);
        if (j == cpt_pt.not_found() || j->second.empty()) {
            const auto qn(cpt.name().qualified());
            BOOST_LOG_SEV(lg, error) << template_has_no_untyped_value + qn;
            BOOST_THROW_EXCEPTION(
                hydration_exception(template_has_no_untyped_value + qn));
        }

        const auto untyped_pt(j->second);
        for (auto k(untyped_pt.begin()); k != untyped_pt.end(); ++k)
            cpt.untyped_value().push_back(k->second.get_value<std::string>());

        r.push_back(cpt);
    }

    return r;
}

meta_model::profile_template
profile_template_hydrator::read_stream(std::istream& s) const {
    using namespace boost::property_tree;
    ptree pt;
    read_json(s, pt);

    meta_model::profile_template r;
    r.name().simple(pt.get<std::string>(name_key));

    auto i = pt.find(parents_key);
    if (i != pt.not_found()) {
        const auto& parents(i->second);
        for (auto j(parents.begin()); j != parents.end(); ++j)
            r.parents().push_back(j->second.get_value<std::string>());
    }

    i = pt.find(labels_key);
    if (i != pt.not_found()) {
        const auto& labels(i->second);
        for (auto j(labels.begin()); j != labels.end(); ++j)
            r.labels()

                .insert(j->second.get_value<std::string>());
    }

    i = pt.find(templates_key);
    if (i != pt.not_found())
        r.templates(read_templates(i->second));

    return r;
}

meta_model::profile_template
profile_template_hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, trace) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
        auto r(read_stream(s));
        BOOST_LOG_SEV(lg, trace) << "Parsed JSON stream successfully.";
        return r;
    } catch (const json_parser_error& e) {
        BOOST_LOG_SEV(lg, error) << invalid_json_file << e.what();
        BOOST_THROW_EXCEPTION(hydration_exception(invalid_json_file + e.what()));
    } catch (const ptree_bad_data& e) {
        BOOST_LOG_SEV(lg, error) << invalid_value_in_json << e.what();
        BOOST_THROW_EXCEPTION(
            hydration_exception(invalid_value_in_json + e.what()));
    } catch (const ptree_bad_path& e) {
        BOOST_LOG_SEV(lg, error) << invalid_path << e.what();
        BOOST_THROW_EXCEPTION(hydration_exception(invalid_path + e.what()));
    }
}

meta_model::profile_template profile_template_hydrator::
hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << p.generic_string();

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
