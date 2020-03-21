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
#include "dogen.m2t.cpp/types/formatters/inclusion_constants.hpp"

namespace dogen::m2t::cpp::formatters {

std::string inclusion_constants::std::list() {
    static ::std::string r("<list>");
    return r;
}

std::string inclusion_constants::std::string() {
    static ::std::string r("<string>");
    return r;
}

std::string inclusion_constants::std::iosfwd() {
    static ::std::string r("<iosfwd>");
    return r;
}

std::string inclusion_constants::std::algorithm() {
    static ::std::string r("<algorithm>");
    return r;
}

std::string inclusion_constants::std::ostream() {
    static ::std::string r("<ostream>");
    return r;
}

std::string inclusion_constants::std::iostream() {
    static ::std::string r("<iostream>");
    return r;
}

std::string inclusion_constants::std::sstream() {
    static ::std::string r("<sstream>");
    return r;
}

std::string inclusion_constants::std::functional() {
    static ::std::string r("<functional>");
    return r;
}

std::string inclusion_constants::std::stdexcept() {
    static ::std::string r("<stdexcept>");
    return r;
}

std::string inclusion_constants::boost::shared_ptr() {
    static ::std::string r("<boost/shared_ptr.hpp>");
    return r;
}

std::string inclusion_constants::boost::lexical_cast() {
    static ::std::string r("<boost/lexical_cast.hpp>");
    return r;
}

std::string inclusion_constants::boost::predef() {
    static ::std::string r("<boost/predef.h>");
    return r;
}

std::string inclusion_constants::boost::property_tree::ptree() {
    static ::std::string r("<boost/property_tree/ptree.hpp>");
    return r;
}

std::string inclusion_constants::boost::property_tree::json_parser() {
    static ::std::string r("<boost/property_tree/json_parser.hpp>");
    return r;
}

std::string inclusion_constants::boost::type_traits::is_virtual_base_of() {
    static ::std::string r("<boost/type_traits/is_virtual_base_of.hpp>");
    return r;
}

std::string inclusion_constants::boost::archive::xml_iarchive() {
    static ::std::string r("<boost/archive/xml_iarchive.hpp>");
    return r;
}

std::string inclusion_constants::boost::archive::xml_oarchive() {
    static ::std::string r("<boost/archive/xml_oarchive.hpp>");
    return r;
}

std::string inclusion_constants::boost::archive::text_iarchive() {
    static ::std::string r("<boost/archive/text_iarchive.hpp>");
    return r;
}

std::string inclusion_constants::boost::archive::text_oarchive() {
    static ::std::string r("<boost/archive/text_oarchive.hpp>");
    return r;
}

std::string inclusion_constants::boost::archive::binary_iarchive() {
    static ::std::string r("<boost/archive/binary_iarchive.hpp>");
    return r;
}

std::string inclusion_constants::boost::archive::binary_oarchive() {
    static ::std::string r("<boost/archive/binary_oarchive.hpp>");
    return r;
}

std::string inclusion_constants::boost::archive::polymorphic_iarchive() {
    static ::std::string r("<boost/archive/polymorphic_iarchive.hpp>");
    return r;
}

std::string inclusion_constants::boost::archive::polymorphic_oarchive() {
    static ::std::string r("<boost/archive/polymorphic_oarchive.hpp>");
    return r;
}

std::string inclusion_constants::boost::serialization::nvp() {
    static ::std::string r("<boost/serialization/nvp.hpp>");
    return r;
}

std::string inclusion_constants::boost::serialization::split_free() {
    static ::std::string r("<boost/serialization/split_free.hpp>");
    return r;
}

std::string inclusion_constants::boost::serialization::assume_abstract() {
    static ::std::string r("<boost/serialization/assume_abstract.hpp>");
    return r;
}

std::string inclusion_constants::boost::serialization::shared_ptr() {
    static ::std::string r("<boost/serialization/shared_ptr.hpp>");
    return r;
}

std::string inclusion_constants::boost::exception::info() {
    static ::std::string r("<boost/exception/info.hpp>");
    return r;
}

std::string inclusion_constants::boost::exception::diagnostic_information() {
    static ::std::string r("<boost/exception/diagnostic_information.hpp>");
    return r;
}

std::string inclusion_constants::boost::test::unit_test() {
    static ::std::string r("<boost/test/unit_test.hpp>");
    return r;
}

std::string inclusion_constants::boost::test::unit_test_monitor() {
    static ::std::string r("<boost/test/unit_test_monitor.hpp>");
    return r;
}

}
