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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/io/formattables/inclusion_io.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_dependencies_factory"));

const std::string duplicate_formatter_name("Formatter name already inserted: ");
const std::string formatter_not_found("Formatter not found: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

std::unordered_map<sml::qname,
                   std::unordered_map<std::string, std::list<inclusion> > >
inclusion_dependencies_factory::make(
    const settings::selector& /*s*/, const provider_selector_interface& /*ps*/,
    const std::unordered_map<sml::qname,
    std::unordered_map<std::string, file_properties>
    >& /*file_properties_by_formatter_name*/,
    const sml::model& /*m*/) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining inclusion dependencies.";

    std::unordered_map<sml::qname,
                       std::unordered_map<std::string,
                                          std::list<inclusion>
                                          >
                       > r;
    BOOST_LOG_SEV(lg, debug) << "Inclusion dependencies: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining inclusion dependencies.";
    return r;
}

} } }
