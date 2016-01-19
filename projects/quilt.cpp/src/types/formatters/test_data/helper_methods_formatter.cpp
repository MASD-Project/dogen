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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/char_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/int_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/bool_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/string_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/composite_type_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/domain_type_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/associative_container_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/sequence_container_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/smart_pointer_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/pair_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/optional_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/variant_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/date_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/ptime_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/time_duration_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/ptree_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/path_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/helper_methods_formatter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory(
        "quilt.cpp.formatters.test_data.helper_methods_formatter"));

const std::string invalid_associative_container(
    "Associative containers have one or two type arguments");
const std::string invalid_sequence_container(
    "Sequence containers have exactly one type argument");
const std::string invalid_smart_pointer(
    "Smart pointers have exactly one type argument");
const std::string invalid_pair_type(
    "Pair types have exactly two type arguments");
const std::string invalid_optional_type(
    "Optional types have exactly one type argument");
const std::string invalid_variant("Variants should have at least one type");
const std::string invalid_date("Date should have no type arguments");
const std::string invalid_ptime("Ptime should have no type arguments");
const std::string invalid_time_duration(
    "Time duration should have no type arguments");
const std::string invalid_ptree("Ptree's should have no type arguments");
const std::string invalid_path("Paths should have no type arguments");

const std::string bool_type("bool");
const std::string string_type("std::string");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

helper_methods_formatter::helper_methods_formatter(
    const std::string& owner_name,
    const std::list<formattables::property_info>& properties)
    : owner_name_(owner_name), properties_(properties) {}

void helper_methods_formatter::char_helper(
  formatters::nested_type_formatting_assistant& a,
  const formattables::nested_type_info& t) const {
    char_helper_stitch(a, t);
}

void helper_methods_formatter::int_helper(
  formatters::nested_type_formatting_assistant& a,
  const formattables::nested_type_info& t) const {
    int_helper_stitch(a, t);
}

void helper_methods_formatter::bool_helper(
  formatters::nested_type_formatting_assistant& a,
  const formattables::nested_type_info& t) const {
    bool_helper_stitch(a, t);
}

void helper_methods_formatter::sequence_container_helper(
    formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {

    if (t.children().size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_sequence_container;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container));
    }
    sequence_container_helper_stitch(a, t);
}

void helper_methods_formatter::associative_container_helper(
    formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {

    if (t.children().size() != 1 && t.children().size() != 2) {
        BOOST_LOG_SEV(lg, error) << invalid_associative_container;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_associative_container));
    }
    associative_container_helper_stitch(a, t);
}

void helper_methods_formatter::smart_pointer_helper(
    formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {

    if (t.children().size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_smart_pointer));
    }
    smart_pointer_helper_stitch(a, t);
}

void helper_methods_formatter::optional_helper(
  formatters::nested_type_formatting_assistant& a,
  const formattables::nested_type_info& t) const {
  if (t.children().size() != 1) {
    BOOST_LOG_SEV(lg, error) << invalid_optional_type;
    BOOST_THROW_EXCEPTION(formatting_error(invalid_optional_type));
  }

  optional_helper_stitch(a, t);
}

void helper_methods_formatter::
pair_helper(formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {
    if (t.children().size() != 2) {
        BOOST_LOG_SEV(lg, error) << invalid_pair_type;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_pair_type));
    }

    pair_helper_stitch(a, t);
}

void helper_methods_formatter::
variant_helper(formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {
    if (t.children().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_variant;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_variant));
    }

    variant_helper_stitch(a, t);
}

void helper_methods_formatter::path_helper(
  formatters::nested_type_formatting_assistant& a,
  const formattables::nested_type_info& t) const {
  if (!t.children().empty()) {
    BOOST_LOG_SEV(lg, error) << invalid_path;
    BOOST_THROW_EXCEPTION(formatting_error(invalid_path));
  }

  path_helper_stitch(a, t);
}

void helper_methods_formatter::date_helper(
    formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {
    if (!t.children().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_date;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_date));
    }

    date_helper_stitch(a, t);
}
void helper_methods_formatter::ptime_helper(
    formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {
    if (!t.children().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_ptime;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_ptime));
    }

    ptime_helper_stitch(a, t);
}
void helper_methods_formatter::time_duration_helper(
    formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {
    if (!t.children().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_time_duration;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_time_duration));
    }

    time_duration_helper_stitch(a, t);
}

void helper_methods_formatter::ptree_helper(
    formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t) const {
    if (!t.children().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_ptree;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_ptree));
    }

    ptree_helper_stitch(a, t);
}

void helper_methods_formatter::string_helper(
  formatters::nested_type_formatting_assistant& a,
  const formattables::nested_type_info& t) const {
    string_helper_stitch(a, t);
}

void helper_methods_formatter::composite_type_helper(
  formatters::nested_type_formatting_assistant& a,
  const formattables::nested_type_info& t,
  const bool as_pointer) const {
    composite_type_helper_stitch(a, t, as_pointer);
}

void helper_methods_formatter::domain_type_helper(
  formatters::nested_type_formatting_assistant& a,
  const formattables::nested_type_info& t,
  const bool as_pointer) const {
    domain_type_helper_stitch(a, t, as_pointer);
}

void helper_methods_formatter::recursive_helper_method_creator(
    formatters::nested_type_formatting_assistant& a,
    const formattables::nested_type_info& t,
    std::unordered_set<std::string>& types_done,
    const bool as_pointer) const {

    std::string type_name(t.complete_identifiable_name());
    if (as_pointer)
        type_name += "_ptr";

    if (types_done.find(type_name) != types_done.end()) {
        BOOST_LOG_SEV(lg, debug) << "Type already done: " << type_name;
        return;
    }

    for (const auto c : t.children()) {
        recursive_helper_method_creator(a, c, types_done,
            t.is_smart_pointer());
    }

    if (t.is_char_like())
        char_helper(a, t);
    else if (t.is_int_like())
        int_helper(a, t);
    else if (t.name() == bool_type)
        bool_helper(a, t);
    else if (t.is_sequence_container())
        sequence_container_helper(a, t);
    else if (t.is_associative_container())
        associative_container_helper(a, t);
    else if (t.is_smart_pointer())
        smart_pointer_helper(a, t);
    else if (t.is_optional_like())
        optional_helper(a, t);
    else if (t.is_pair())
        pair_helper(a, t);
    else if (t.is_variant_like())
        variant_helper(a, t);
    else if (t.is_filesystem_path())
        path_helper(a, t);
    else if (t.is_date())
        date_helper(a, t);
    else if (t.is_ptime())
        ptime_helper(a, t);
    else if (t.is_time_duration())
        time_duration_helper(a, t);
    else if (t.is_ptree())
        ptree_helper(a, t);
    else if (t.name() == string_type)
        string_helper(a, t);
    else {
        if (boost::algorithm::ends_with(t.name(), "::" + owner_name_))
            composite_type_helper(a, t, as_pointer);
        else
            domain_type_helper(a, t, as_pointer);
    }
    types_done.insert(type_name);
}

void helper_methods_formatter::format(std::ostream& s) const {
    BOOST_LOG_SEV(lg, debug) << "Creating helper methods.";
    if (properties_.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No properties found.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Properties found: " << properties_.size();

    formatters::nested_type_formatting_assistant a(s);
    std::unordered_set<std::string> types_done;
    for (const auto p : properties_)
        recursive_helper_method_creator(a, p.type(), types_done,
            false/*as pointer*/);
}

} } } } }
