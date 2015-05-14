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
#include "dogen/cpp/types/formattables/inclusion_directives_selector.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_dependencies_builder"));

const auto empty_list = std::list<std::string> {};
const std::string empty_directive("Cannot add empty include directive.");

}

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_dependencies_builder::
inclusion_dependencies_builder(const inclusion_directives_repository& rp)
    : repository_(rp) {}

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
    const inclusion_directives_selector sel(repository_);
    const auto id(sel.select_inclusion_directive(qn, formatter_name));
    if (id)
        add(*id);
}

void inclusion_dependencies_builder::
add(const std::list<sml::qname>& qn, const std::string& formatter_name) {
    for (const auto& n : qn)
        add(n, formatter_name);
}

std::list<std::string> inclusion_dependencies_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Built inclusion dependencies for formatter.";
    BOOST_LOG_SEV(lg, debug) << "Result: " << inclusion_dependencies_;

    return inclusion_dependencies_;
}

} } }
