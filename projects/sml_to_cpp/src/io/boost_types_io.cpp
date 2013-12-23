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
#include <ostream>
#include <stdexcept>
#include "dogen/sml_to_cpp/io/boost_types_io.hpp"

namespace dogen {
namespace sml_to_cpp {

std::ostream& operator<<(std::ostream& s, const boost_types& v) {
    s << "{ " << "\"__type__\": " << "\"boost_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case boost_types::invalid:
        attr = "\"invalid\"";
        break;
    case boost_types::optional:
        attr = "\"optional\"";
        break;
    case boost_types::format:
        attr = "\"format\"";
        break;
    case boost_types::shared_ptr:
        attr = "\"shared_ptr\"";
        break;
    case boost_types::nvp:
        attr = "\"nvp\"";
        break;
    case boost_types::split_free:
        attr = "\"split_free\"";
        break;
    case boost_types::assume_abstract:
        attr = "\"assume_abstract\"";
        break;
    case boost_types::is_virtual_base_of:
        attr = "\"is_virtual_base_of\"";
        break;
    case boost_types::xml_oarchive:
        attr = "\"xml_oarchive\"";
        break;
    case boost_types::xml_iarchive:
        attr = "\"xml_iarchive\"";
        break;
    case boost_types::text_oarchive:
        attr = "\"text_oarchive\"";
        break;
    case boost_types::text_iarchive:
        attr = "\"text_iarchive\"";
        break;
    case boost_types::binary_oarchive:
        attr = "\"binary_oarchive\"";
        break;
    case boost_types::binary_iarchive:
        attr = "\"binary_iarchive\"";
        break;
    case boost_types::polymorphic_iarchive:
        attr = "\"polymorphic_iarchive\"";
        break;
    case boost_types::polymorphic_oarchive:
        attr = "\"polymorphic_oarchive\"";
        break;
    case boost_types::serialization_export:
        attr = "\"serialization_export\"";
        break;
    case boost_types::string:
        attr = "\"string\"";
        break;
    case boost_types::vector:
        attr = "\"vector\"";
        break;
    case boost_types::set:
        attr = "\"set\"";
        break;
    case boost_types::deque:
        attr = "\"deque\"";
        break;
    case boost_types::list:
        attr = "\"list\"";
        break;
    case boost_types::serialization_shared_ptr:
        attr = "\"serialization_shared_ptr\"";
        break;
    case boost_types::serialization_optional:
        attr = "\"serialization_optional\"";
        break;
    case boost_types::exception_info:
        attr = "\"exception_info\"";
        break;
    case boost_types::io_ios_state:
        attr = "\"io_ios_state\"";
        break;
    case boost_types::string_algorithm:
        attr = "\"string_algorithm\"";
        break;
    case boost_types::variant:
        attr = "\"variant\"";
        break;
    case boost_types::serialization_variant:
        attr = "\"serialization_variant\"";
        break;
    case boost_types::apply_visitor:
        attr = "\"apply_visitor\"";
        break;
    case boost_types::filesystem_path:
        attr = "\"filesystem_path\"";
        break;
    case boost_types::gregorian_date:
        attr = "\"gregorian_date\"";
        break;
    case boost_types::ptime:
        attr = "\"ptime\"";
        break;
    case boost_types::time_duration:
        attr = "\"time_duration\"";
        break;
    case boost_types::serialization_gregorian_date:
        attr = "\"serialization_gregorian_date\"";
        break;
    case boost_types::serialization_ptime:
        attr = "\"serialization_ptime\"";
        break;
    case boost_types::serialization_time_duration:
        attr = "\"serialization_time_duration\"";
        break;
    case boost_types::io_gregorian_date:
        attr = "\"io_gregorian_date\"";
        break;
    case boost_types::io_time:
        attr = "\"io_time\"";
        break;
    case boost_types::serialization_pair:
        attr = "\"serialization_pair\"";
        break;
    case boost_types::ptree:
        attr = "\"ptree\"";
        break;
    case boost_types::serialization_ptree:
        attr = "\"serialization_ptree\"";
        break;
    case boost_types::io_ptree:
        attr = "\"io_ptree\"";
        break;
    case boost_types::eos_oarchive:
        attr = "\"eos_oarchive\"";
        break;
    case boost_types::eos_iarchive:
        attr = "\"eos_iarchive\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for boost_types");
    }
    s << attr << " }";
    return s;
}

} }