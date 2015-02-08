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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/io/formattables/includes_io.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/includes_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formattables.includes_factory"));

const std::string duplicate_formatter_name("Formatter name already inserted: ");
const std::string formatter_not_found("Formatter not found: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

std::unordered_map<sml::qname,
                   std::unordered_map<std::string, includes>
                   >
includes_factory::make(
    const settings::selector& /*s*/, const provider_selector_interface& /*ps*/,
    const std::unordered_map<sml::qname,
    std::unordered_map<std::string, file_properties>
    >& /*file_properties_by_formatter_name*/,
    const sml::model& /*m*/) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining includes.";

    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, includes>
        > r;
/*
    const auto includes_factories(create_includes_factories(c));
    for (const auto pair : file_properties_by_formatter_name) {
        const auto& qn(pair.first);
        std::unordered_map<std::string, formattables::file_properties> fp;
        for (const auto other_pair : pair.second) {
            formattables::file_properties fp;
            fp.relative_path(other_pair.second.relative_path());

            const auto& formatter_name(other_pair.first);
            const auto i(includes_factories.find(formatter_name));
            if (i == includes_factories.end()) {
                BOOST_LOG_SEV(lg, error) << formatter_not_found
                                         << formatter_name;
                BOOST_THROW_EXCEPTION(building_error(formatter_not_found +
                        formatter_name));
            }

            const auto& f(*(i->second));
            auto inc(f.make(m, qn, file_names));
            fp.includes(inc);
            all_props[formatter_name] = fp;
        }
        r[qn] = all_props;
    }
*/
    BOOST_LOG_SEV(lg, debug) << "Includes: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining includes.";
    return r;
}

} } }
