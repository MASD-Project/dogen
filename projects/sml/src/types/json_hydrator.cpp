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
#include <istream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/tag_router.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/hydration_error.hpp"
#include "dogen/sml/types/json_hydrator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.json_hydrator"));

const std::string model_name_key("model_name");
const std::string documentation_key("documentation");
const std::string origin_key("origin");
const std::string origin_system_value("system");
const std::string origin_user_value("user");
const std::string types_key("types");

const std::string meta_type_key("meta_type");
const std::string meta_type_value_object_value("value_object");
const std::string meta_type_primitive_value("primitive");

const std::string simple_name_key("simple_name");
const std::string module_path_key("module_path");

const std::string tags_key("tags");

const std::string invalid_json_file("Failed to parse JSON file: ");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string invalid_origin("Invalid value for origin: ");
const std::string invalid_meta_type("Invalid value for meta type: ");
const std::string model_has_no_types("Did not find any types in model");

}

namespace dogen {
namespace sml {

void json_hydrator::
read_type(const boost::property_tree::ptree& pt, model& m) const {
    qname qn;
    qn.model_name(m.name().model_name());

    const auto simple_name_value(pt.get<std::string>(simple_name_key));
    qn.simple_name(simple_name_value);

    const auto documentation(pt.get_optional<std::string>(documentation_key));

    const auto i(pt.find(module_path_key));
    if (i != pt.not_found()) {
        for (auto j(i->second.begin()); j != i->second.end(); ++j)
            qn.module_path().push_back(j->second.get_value<std::string>());
    }

    const auto lambda([&](type& t) {
            t.name(qn);
            t.generation_type(generation_types::no_generation);
            if (documentation)
                t.documentation(*documentation);
            read_tags<type>(pt, t);
        });

    const auto meta_type_value(pt.get<std::string>(meta_type_key));
    if (meta_type_value == meta_type_value_object_value) {
        auto vo(boost::make_shared<sml::value_object>());
        lambda(*vo);
        m.objects().insert(std::make_pair(qn, vo));
    } else if (meta_type_value == meta_type_primitive_value) {
        primitive p;
        lambda(p);
        m.primitives().insert(std::make_pair(qn, p));
    }
    else {
        BOOST_LOG_SEV(lg, error) << invalid_meta_type << meta_type_value;
        BOOST_THROW_EXCEPTION(
            hydration_error(invalid_meta_type + meta_type_value));
    }
}

model json_hydrator::read_stream(std::istream& s) const {
    model r;
    r.generation_type(generation_types::no_generation);

    using namespace boost::property_tree;
    ptree pt;
    read_json(s, pt);

    read_tags(pt, r);
    r.name().model_name(pt.get<std::string>(model_name_key));

    auto i(pt.find(module_path_key));
    if (i != pt.not_found()) {
        for (auto j(i->second.begin()); j != i->second.end(); ++j)
            r.name().module_path().push_back(j->second.get_value<std::string>());
    }

    const auto documentation(pt.get_optional<std::string>(documentation_key));
    if (documentation)
        r.documentation(*documentation);

    const auto origin_value(pt.get<std::string>(origin_key));
    if (origin_value == origin_system_value)
        r.origin_type(origin_types::system);
    else if (origin_value == origin_user_value)
        r.origin_type(origin_types::system);
    else {
        BOOST_LOG_SEV(lg, error) << invalid_origin << origin_value;
        BOOST_THROW_EXCEPTION(hydration_error(invalid_origin + origin_value));
    }

    i = pt.find(types_key);
    if (i == pt.not_found() || i->second.empty()) {
        BOOST_LOG_SEV(lg, error) << model_has_no_types;
        BOOST_THROW_EXCEPTION(hydration_error(model_has_no_types));
    }

    for (auto j(i->second.begin()); j != i->second.end(); ++j)
        read_type(j->second, r);

    return r;
}

model json_hydrator::hydrate(std::istream& s) const {
    using namespace boost::property_tree;
    try {
        return read_stream(s);
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

} }
