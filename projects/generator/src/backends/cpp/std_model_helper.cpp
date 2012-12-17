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
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/std_model_helper.hpp"
#include "dogen/utility/log/logger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("serialization_implementation"));

const std::string model("std");

const std::string shared_ptr_type("shared_ptr");
const std::string string_type("string");
const std::string int8_t_type("int8_t");
const std::string int16_t_type("int16_t");
const std::string int32_t_type("int32_t");
const std::string int64_t_type("int64_t");
const std::string uint8_t_type("uint8_t");
const std::string uint16_t_type("uint16_t");
const std::string uint32_t_type("uint32_t");
const std::string uint64_t_type("uint64_t");
const std::string array_type("array");
const std::string forward_list_type("forward_list");
const std::string vector_type("vector");
const std::string set_type("set");
const std::string multiset_type("multiset");
const std::string map_type("map");
const std::string multimap_type("multimap");
const std::string deque_type("deque");
const std::string list_type("list");
const std::string unordered_map_type("unordered_map");
const std::string unordered_set_type("unordered_set");
const std::string ostream_type("ostream");
const std::string sstream_type("sstream");

const std::string stdexcept_type("stdexcept");
const std::string functional_type("functional");

const std::string string_include("string");
const std::string cstdint_include("cstdint");
const std::string array_include("array");
const std::string forward_list_include("forward_list");
const std::string vector_include("vector");
const std::string set_include("set");
const std::string multiset_include("multiset");
const std::string map_include("map");
const std::string multimap_include("multimap");
const std::string deque_include("deque");
const std::string list_include("list");
const std::string unordered_map_include("unordered_map");
const std::string unordered_set_include("unordered_set");
const std::string algorithm_include("algorithm");
const std::string ostream_include("ostream");
const std::string iosfwd_include("iosfwd");
const std::string sstream_include("sstream");
const std::string stdexcept_include("stdexcept");
const std::string functional_include("functional");

const std::string error_message("Invalid or unexpected std type");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

std::string std_model_helper::model() const {
    return ::model;
}

bool std_model_helper::is_primitive(const std::string s) const {
    return
        s == int8_t_type || s == int16_t_type ||
        s == int32_t_type || s == int64_t_type ||
        s == uint8_t_type || s == uint16_t_type ||
        s == uint32_t_type || s == uint64_t_type;
}

std_types std_model_helper::string_to_type(const std::string type) const {

    if (type == string_type) return std_types::string;
    if (type == int8_t_type) return std_types::int8_t;
    if (type == int16_t_type) return std_types::int16_t;
    if (type == int32_t_type) return std_types::int32_t;
    if (type == int64_t_type) return std_types::int64_t;
    if (type == uint8_t_type) return std_types::uint8_t;
    if (type == uint16_t_type) return std_types::uint16_t;
    if (type == uint32_t_type) return std_types::uint32_t;
    if (type == uint64_t_type) return std_types::uint64_t;
    if (type == array_type) return std_types::array;
    if (type == forward_list_type) return std_types::forward_list;
    if (type == vector_type) return std_types::vector;
    if (type == set_type) return std_types::set;
    if (type == multiset_type) return std_types::multiset;
    if (type == map_type) return std_types::map;
    if (type == multimap_type) return std_types::multimap;
    if (type == deque_type) return std_types::deque;
    if (type == list_type) return std_types::list;
    if (type == unordered_map_type) return std_types::unordered_map;
    if (type == unordered_set_type) return std_types::unordered_set;
    if (type == ostream_type) return std_types::ostream;
    if (type == sstream_type) return std_types::sstream;
    if (type == stdexcept_type) return std_types::stdexcept;
    if (type == functional_type) return std_types::functional;
    BOOST_LOG_SEV(lg, error) << error_message;
    BOOST_THROW_EXCEPTION(utility::exception::invalid_enum_value(error_message));
}

std::string std_model_helper::type(const std_types t) const {
    switch (t) {
    case std_types::string: return string_type;
    case std_types::int8_t: return int8_t_type;
    case std_types::int16_t: return int16_t_type;
    case std_types::int32_t: return int32_t_type;
    case std_types::int64_t: return int64_t_type;
    case std_types::uint8_t: return uint8_t_type;
    case std_types::uint16_t: return uint16_t_type;
    case std_types::uint32_t: return uint32_t_type;
    case std_types::uint64_t: return uint64_t_type;
    case std_types::array: return array_type;
    case std_types::forward_list: return forward_list_type;
    case std_types::vector: return vector_type;
    case std_types::set: return set_type;
    case std_types::multiset: return multiset_type;
    case std_types::map: return map_type;
    case std_types::multimap: return multimap_type;
    case std_types::deque: return deque_type;
    case std_types::list: return list_type;
    case std_types::unordered_map: return unordered_map_type;
    case std_types::unordered_set: return unordered_set_type;
    case std_types::ostream: return ostream_type;
    case std_types::sstream: return sstream_type;
    case std_types::stdexcept: return stdexcept_type;
    case std_types::functional: return functional_type;
    default: break;
    }
    BOOST_LOG_SEV(lg, error) << error_message;
    BOOST_THROW_EXCEPTION(utility::exception::invalid_enum_value(error_message));
}

std::string std_model_helper::include(const std_types type) const {
    switch (type) {
    case std_types::string: return string_include;
    case std_types::int8_t: return cstdint_include;
    case std_types::int16_t: return cstdint_include;
    case std_types::int32_t: return cstdint_include;
    case std_types::int64_t: return cstdint_include;
    case std_types::uint8_t: return cstdint_include;
    case std_types::uint16_t: return cstdint_include;
    case std_types::uint32_t: return cstdint_include;
    case std_types::uint64_t: return cstdint_include;
    case std_types::array: return array_include;
    case std_types::forward_list: return forward_list_include;
    case std_types::vector: return vector_include;
    case std_types::set: return set_include;
    case std_types::multiset: return multiset_include;
    case std_types::map: return map_include;
    case std_types::multimap: return multimap_include;
    case std_types::deque: return deque_include;
    case std_types::list: return list_include;
    case std_types::unordered_map: return unordered_map_include;
    case std_types::unordered_set: return unordered_set_include;
    case std_types::algorithm: return algorithm_include;
    case std_types::ostream: return ostream_include;
    case std_types::iosfwd: return iosfwd_include;
    case std_types::sstream: return sstream_include;
    case std_types::stdexcept: return stdexcept_include;
    case std_types::functional: return functional_include;
    default: break;
    }
    BOOST_LOG_SEV(lg, error) << error_message;
    BOOST_THROW_EXCEPTION(utility::exception::invalid_enum_value(error_message));
}

} } } }
