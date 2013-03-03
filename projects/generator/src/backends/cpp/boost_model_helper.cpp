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
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/backends/cpp/boost_model_helper.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("boost_model_helper"));

const std::string model("boost");

const std::string shared_ptr_type("shared_ptr");
const std::string optional_type("optional");
const std::string variant_type("variant");
const std::string filesystem_path_type("path");
const std::string gregorian_date_type("date");
const std::string ptime_type("ptime");
const std::string time_duration_type("time_duration");

const std::string optional_include("boost/optional.hpp");
const std::string variant_include("boost/variant.hpp");
const std::string format_include("boost/format.hpp");
const std::string nvp_include("boost/serialization/nvp.hpp");
const std::string split_free_include("boost/serialization/split_free.hpp");
const std::string assume_abstract_include(
    "boost/serialization/assume_abstract.hpp");
const std::string is_virtual_base_of_include(
    "boost/type_traits/is_virtual_base_of.hpp");
const std::string xml_oarchive_include("boost/archive/xml_oarchive.hpp");
const std::string xml_iarchive_include("boost/archive/xml_iarchive.hpp");
const std::string text_oarchive_include("boost/archive/text_oarchive.hpp");
const std::string text_iarchive_include("boost/archive/text_iarchive.hpp");
const std::string binary_oarchive_include("boost/archive/binary_oarchive.hpp");
const std::string binary_iarchive_include("boost/archive/binary_iarchive.hpp");
const std::string poly_iarchive_include(
    "boost/archive/polymorphic_iarchive.hpp");
const std::string poly_oarchive_include(
    "boost/archive/polymorphic_oarchive.hpp");
const std::string export_include("boost/serialization/export.hpp");
const std::string string_include("boost/serialization/string.hpp");
const std::string vector_include("boost/serialization/vector.hpp");
const std::string set_include("boost/serialization/set.hpp");
const std::string deque_include("boost/serialization/deque.hpp");
const std::string list_include("boost/serialization/list.hpp");
const std::string serialization_shared_ptr_include(
    "boost/serialization/shared_ptr.hpp");
const std::string serialization_optional_include(
    "boost/serialization/optional.hpp");
const std::string serialization_variant_include(
    "boost/serialization/variant.hpp");
const std::string shared_ptr_include("boost/shared_ptr.hpp");
const std::string exception_info_include("boost/exception/info.hpp");
const std::string state_saver_include("boost/io/ios_state.hpp");
const std::string string_algorithm_include("boost/algorithm/string.hpp");
const std::string apply_visitor_include("boost/variant/apply_visitor.hpp");
const std::string filesystem_path_include("boost/filesystem/path.hpp");
const std::string gregorian_date_include(
    "boost/date_time/gregorian/gregorian_types.hpp");
const std::string ptime_include(
    "boost/date_time/posix_time/posix_time_types.hpp");
const std::string time_duration_include(
    "boost/date_time/posix_time/posix_time_types.hpp");
const std::string serialization_gregorian_date_include(
    "boost/date_time/gregorian/greg_serialize.hpp");
const std::string serialization_ptime_include(
    "boost/date_time/posix_time/time_serialize.hpp");
const std::string serialization_time_duration_include(
    "boost/date_time/posix_time/time_serialize.hpp");
const std::string io_date_include("boost/date_time/gregorian/gregorian.hpp");
const std::string io_time_include("boost/date_time/posix_time/posix_time.hpp");

const std::string error_message("Invalid or unexpected boost type");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

std::string boost_model_helper::model() const {
    return ::model;
}

std::string boost_model_helper::type(const boost_types t) const {
    switch (t) {
    case boost_types::shared_ptr: return shared_ptr_type;
    case boost_types::optional: return optional_type;
    case boost_types::variant: return variant_type;
    case boost_types::filesystem_path: return filesystem_path_type;
    case boost_types::gregorian_date: return gregorian_date_type;
    case boost_types::ptime: return ptime_type;
    case boost_types::time_duration: return time_duration_type;
    default: break;
    }
    BOOST_LOG_SEV(lg, error) << error_message;
    BOOST_THROW_EXCEPTION(
        utility::exception::invalid_enum_value(error_message));
}

std::string boost_model_helper::include(const boost_types type) const {
    switch (type) {
    case boost_types::shared_ptr: return shared_ptr_include;
    case boost_types::optional: return optional_include;
    case boost_types::format: return format_include;
    case boost_types::nvp: return nvp_include;
    case boost_types::split_free: return split_free_include;
    case boost_types::assume_abstract:
        return assume_abstract_include;
    case boost_types::is_virtual_base_of:
        return is_virtual_base_of_include;
    case boost_types::xml_oarchive:
        return xml_oarchive_include;
    case boost_types::xml_iarchive:
        return xml_iarchive_include;
    case boost_types::text_oarchive:
        return text_oarchive_include;
    case boost_types::text_iarchive:
        return text_iarchive_include;
    case boost_types::binary_oarchive:
        return binary_oarchive_include;
    case boost_types::binary_iarchive:
        return binary_iarchive_include;
    case boost_types::polymorphic_iarchive:
        return poly_iarchive_include;
    case boost_types::polymorphic_oarchive:
        return poly_oarchive_include;
    case boost_types::serialization_export: return export_include;
    case boost_types::string: return string_include;
    case boost_types::vector: return vector_include;
    case boost_types::set: return set_include;
    case boost_types::deque: return deque_include;
    case boost_types::list: return list_include;
    case boost_types::serialization_shared_ptr:
        return serialization_shared_ptr_include;
    case boost_types::serialization_optional:
        return serialization_optional_include;
    case boost_types::exception_info: return exception_info_include;
    case boost_types::io_ios_state: return state_saver_include;
    case boost_types::string_algorithm: return string_algorithm_include;
    case boost_types::variant: return variant_include;
    case boost_types::serialization_variant:
        return serialization_variant_include;
    case boost_types::apply_visitor: return apply_visitor_include;
    case boost_types::filesystem_path: return filesystem_path_include;
    case boost_types::gregorian_date: return gregorian_date_include;
    case boost_types::ptime: return ptime_include;
    case boost_types::time_duration: return time_duration_include;
    case boost_types::serialization_gregorian_date:
        return serialization_gregorian_date_include;
    case boost_types::serialization_ptime: return serialization_ptime_include;
    case boost_types::serialization_time_duration:
        return serialization_time_duration_include;
    case boost_types::io_gregorian_date: return io_date_include;
    case boost_types::io_time: return io_time_include;
    default: break;
    }

    BOOST_LOG_SEV(lg, error) << error_message;
    BOOST_THROW_EXCEPTION(
        utility::exception::invalid_enum_value(error_message));
}

} } } }
