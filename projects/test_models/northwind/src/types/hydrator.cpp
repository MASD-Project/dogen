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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/test_models/northwind/types/hydration_error.hpp"
#include "dogen/test_models/northwind/types/hydrator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("test_models::northwind"));

const std::string insert_line("INSERT ");

const std::string invalid_path("Failed to find JSON path: ");
const std::string failed_to_open_file("Failed to open file: ");
const std::string invalid_json_file("Failed to parse JSON file: ");
const std::string invalid_option_in_json_file("Failed to read value in JSON: ");
const std::string insert_line_missing_start_bracket(
    "Insert line does not have the expected start bracket '('");
const std::string insert_line_missing_end_bracket(
    "Insert line does not have the expected end bracket ')'");
const std::string mismatch_between_keys_and_values(
    "Keys and values containers do not having matching sizes");

}

namespace dogen {
namespace test_models {
namespace northwind {

void hydrator::
log_tuple(const std::tuple<std::string, std::string, std::string>& t) const {
    BOOST_LOG_SEV(lg, debug) << "First: '" << std::get<0>(t) << "'";
    BOOST_LOG_SEV(lg, debug) << "Second: '" << std::get<1>(t) << "'";
    BOOST_LOG_SEV(lg, debug) << "Third: '" << std::get<2>(t) << "'";
}

std::tuple<std::string, std::string, std::string>
hydrator::section_insert_line(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "Started sectioning line.";

    const auto first_start_bracket(s.find_first_of("("));
    if (first_start_bracket == std::string::npos) {
        BOOST_LOG_SEV(lg, error) << insert_line_missing_start_bracket;
        BOOST_THROW_EXCEPTION(
            hydration_error(insert_line_missing_start_bracket));
    }

    std::tuple<std::string, std::string, std::string> r;

    /*
     * We subtract one to miss the start bracket.
     */
    std::get<0>(r) = s.substr(0, first_start_bracket - 1);

    const auto first_end_bracket(s.find_first_of(")"));
    if (first_end_bracket == std::string::npos) {
        BOOST_LOG_SEV(lg, error) << insert_line_missing_end_bracket;
        BOOST_THROW_EXCEPTION(hydration_error(insert_line_missing_end_bracket));
    }

    /*
     * We add and subtract one to miss the start and end brackets
     * respectively.
     */
    std::get<1>(r) = s.substr(first_start_bracket + 1,
        first_end_bracket - first_start_bracket - 1);

    const auto second_start_bracket(s.find_first_of("(", first_end_bracket));
    if (second_start_bracket == std::string::npos) {
        BOOST_LOG_SEV(lg, error) << insert_line_missing_start_bracket;
        BOOST_THROW_EXCEPTION(
            hydration_error(insert_line_missing_start_bracket));
    }

    const auto second_end_bracket(s.find_last_of(")", second_start_bracket));
    if (first_end_bracket == std::string::npos) {
        BOOST_LOG_SEV(lg, error) << insert_line_missing_end_bracket;
        BOOST_THROW_EXCEPTION(hydration_error(insert_line_missing_end_bracket));
    }
    std::get<2>(r) = s.substr(second_start_bracket + 1,
        second_end_bracket - second_start_bracket - 1);

    log_tuple(r);

    BOOST_LOG_SEV(lg, debug) << "Finished sectioning line.";
    return r;
}

void hydrator::
scrub_tuple(std::tuple<std::string, std::string, std::string>& t) const {
    BOOST_LOG_SEV(lg, debug) << "Started scrubbing tuple.";

    boost::erase_first(std::get<0>(t), insert_line);
    boost::erase_all(std::get<0>(t), "[dbo].");
    boost::erase_all(std::get<0>(t), "[");
    boost::erase_all(std::get<0>(t), "]");

    boost::erase_all(std::get<1>(t), "[");
    boost::erase_all(std::get<1>(t), "]");

    boost::replace_all(std::get<2>(t), ", N'", ", ");

    log_tuple(t);
    BOOST_LOG_SEV(lg, debug) << "Finished scrubbing tuple.";
}

std::unordered_map<std::string, std::string> hydrator::map_keys_to_values(
    const std::string& keys, const std::string& values) const {
    BOOST_LOG_SEV(lg, debug) << "Started mapping keys to values.";

    using dogen::utility::string::splitter;
    const auto k(splitter::split_csv(keys));
    const auto v(splitter::split_csv(values));

    if (k.size() != v.size()) {
        BOOST_LOG_SEV(lg, error) << mismatch_between_keys_and_values
                                 << " keys size: " << k.size()
                                 << " values size: " << v.size();
        BOOST_THROW_EXCEPTION(
            hydration_error(mismatch_between_keys_and_values));
    }

    std::unordered_map<std::string, std::string> r;
    for (auto i(k.begin()), j(v.begin()); i != k.end(); ++i, ++j)
        r[*i] = *j;

    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finished mapping keys to values.";
    return r;
}

repository hydrator::read_stream(std::istream& s) const {
    repository r;

    std::string line;
    while (std::getline(s, line)) {
        BOOST_LOG_SEV(lg, debug) << "Line: " << line;

        if (!boost::starts_with(line, insert_line))
            continue;

        auto t(section_insert_line(line));
        scrub_tuple(t);

        const auto entity(std::get<0>(t));
        const auto keys(std::get<1>(t));
        const auto values(std::get<2>(t));
        const auto map(map_keys_to_values(keys, values));
    }

    return r;
}

repository hydrator::hydrate(std::istream& s) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing stream.";
    using namespace boost::property_tree;

    auto r(read_stream(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed stream successfully.";

    return r;
}

repository hydrator::hydrate(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Parsing file: " << gs;

    boost::filesystem::ifstream s(p);
    if (s.fail()) {
        BOOST_LOG_SEV(lg, error) << failed_to_open_file << gs;
        BOOST_THROW_EXCEPTION(hydration_error(failed_to_open_file + gs));
    }

    const auto r(hydrate(s));
    BOOST_LOG_SEV(lg, debug) << "Parsed file successfully.";
    return r;
}

} } }
