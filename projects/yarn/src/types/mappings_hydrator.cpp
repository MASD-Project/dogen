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
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/hydration_error.hpp"
#include "dogen/yarn/types/mappings_hydrator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.mapping_hydrator"));

const std::string empty;
const std::string id_key("id");
const std::string language_key("language");
const std::string names_by_language_key("names_by_language");
const std::string name_key("name");
const std::string simple_name_key("simple_name");
const std::string internal_modules_key("internal_modules");
const std::string model_modules_key("model_modules");

const std::string cpp_language("cpp");
const std::string csharp_language("csharp");
const std::string la_language("language_agnostic");
const std::string upsilon_language("upsilon");

const std::string invalid_json_file("Failed to parse JSON file");
const std::string invalid_option_in_json_file(
    "Failed to read option in JSON file: ");
const std::string invalid_path("Failed to find JSON path: ");
const std::string failed_to_open_file("Failed to open file: ");
const std::string unsupported_lanugage("Language is not supported: ");
const std::string missing_names("Could not find names by language in JSON.");
const std::string duplicate_language("Language mapped more than once: ");
const std::string missing_name("JSON element name is mandatory.");

}

namespace dogen {
namespace yarn {

languages mappings_hydrator::to_language(const std::string& s) const {
    if (s == cpp_language)
        return languages::cpp;
    else if (s == csharp_language)
        return languages::csharp;
    else if (s == la_language)
        return languages::language_agnostic;
    else if (s == upsilon_language)
        return languages::upsilon;

    BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
    BOOST_THROW_EXCEPTION(hydration_error(unsupported_lanugage + s));
}

name mappings_hydrator::read_name(const boost::property_tree::ptree& pt) const {
    yarn::name_builder b;
    const auto sn(pt.get<std::string>(simple_name_key));
    b.simple_name(sn);

    const auto im(pt.get<std::string>(internal_modules_key, empty));
    if (!im.empty())
        b.internal_modules(im);

    const auto mm(pt.get<std::string>(model_modules_key, empty));
    if (!mm.empty())
        b.internal_modules(mm);

    const auto r(b.build());
    return r;
}
/*
std::unordered_map<languages, name> mappings_hydrator::
read_names_by_language(const boost::property_tree::ptree& pt) const {
    std::unordered_map<languages, name> r;

    for (auto i(pt.begin()); i != pt.end(); ++i) {
        const auto s(i->second.get<std::string>(language_key));
        const auto l(to_language(s));

        const auto j(i->second.find(name_key));
        if (j == i->second.not_found()) {
            BOOST_LOG_SEV(lg, error) << missing_name;
            BOOST_THROW_EXCEPTION(hydration_error(missing_name));
        }

        const auto n(read_name(j->second));
        const auto pair(std::make_pair(l, n));
        const auto inserted(r.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_language << s;
            BOOST_THROW_EXCEPTION(hydration_error(duplicate_language + s));
        }
    }
    return r;
}

std::list<element_mapping>
mappings_hydrator::read_stream(std::istream& s) const {
    std::list<element_mapping> r;
    boost::property_tree::ptree pt;
    read_json(s, pt);

    for (auto i(pt.begin()); i != pt.end(); ++i) {
        element_mapping em;
        em.id(i->second.get<std::string>(id_key));

        const auto j(i->second.find(names_by_language_key));
        if (j == i->second.not_found() || j->second.empty()) {
            BOOST_LOG_SEV(lg, error) << missing_names;
            BOOST_THROW_EXCEPTION(hydration_error(missing_names));
        }
        em.names_by_language(read_names_by_language(j->second));
        r.push_back(em);
    }

    return r;
}

std::list<element_mapping> mappings_hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON stream.";
    using namespace boost::property_tree;
    try {
        auto r(read_stream(s));
        BOOST_LOG_SEV(lg, debug) << "Parsed JSON stream successfully.";
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
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON stream successfully.";
}
*/
std::list<mapping>
mappings_hydrator::hydrate(const boost::filesystem::path& /*p*/) const {
    std::list<mapping> r;
    return r;
    /*
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing JSON file: " << gs;
    boost::filesystem::ifstream s(p);

    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << ": " << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed JSON file successfully.";
    return r;
    */
}

} }
