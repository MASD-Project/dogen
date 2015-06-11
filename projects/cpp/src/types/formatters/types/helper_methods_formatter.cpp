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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/types/smart_pointer_helper_stitch.hpp"
#include "dogen/cpp/types/formatters/types/helper_methods_formatter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cpp.formatters.io.helper_methods_formatter"));

const std::string invalid_smart_pointer(
    "Smart pointers have exactly one type argument");

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

helper_methods_formatter::helper_methods_formatter(
  const std::list<formattables::property_info>& properties)
  : properties_(properties) {}

void helper_methods_formatter::smart_pointer_helper(
    formatters::nested_type_formatting_assistant& fa,
    const formattables::nested_type_info& t) const {
    const auto children(t.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_smart_pointer));
    }
    smart_pointer_helper_stitch(fa, t);
}

void helper_methods_formatter::recursive_helper_method_creator(
    formatters::nested_type_formatting_assistant& fa,
    const formattables::nested_type_info& t,
    std::unordered_set<std::string>& types_done) const {

    if (types_done.find(t.complete_identifiable_name()) != types_done.end())
        return;

    for (const auto c : t.children())
        recursive_helper_method_creator(fa, c, types_done);

    if (t.is_smart_pointer())
        smart_pointer_helper(fa, t);

    types_done.insert(t.complete_identifiable_name());
}

void helper_methods_formatter::format(std::ostream& s) const {
    BOOST_LOG_SEV(lg, error) << "Creating helper methods.";
    if (properties_.empty()) {
        BOOST_LOG_SEV(lg, error) << "No properties found.";
        return;
    }

    BOOST_LOG_SEV(lg, error) << "Properties found: " << properties_.size();

    formatters::nested_type_formatting_assistant fa(s);
    std::unordered_set<std::string> types_done;
    for (const auto p : properties_)
        recursive_helper_method_creator(fa, p.type(), types_done);
}

} } } }
