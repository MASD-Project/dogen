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
#ifndef DOGEN_SML_TO_CPP_TYPES_BOOST_TYPES_HPP
#define DOGEN_SML_TO_CPP_TYPES_BOOST_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml_to_cpp {

/**
 * @brief Available types in the boost model
 */
enum class boost_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    optional = 1, ///< boost optional
    format = 2, ///< boost formatting library
    shared_ptr = 3, ///< boost shared pointer
    nvp = 4, ///< name value pair
    split_free = 5, ///< split load from save
    assume_abstract = 6, ///< assume class is abstract
    is_virtual_base_of = 7, ///< ensure class is virtual base
    xml_oarchive = 8, ///< XML output archive
    xml_iarchive = 9, ///< XML input archive
    text_oarchive = 10, ///< text output archive
    text_iarchive = 11, ///< text input archive
    binary_oarchive = 12, ///< binary output archive
    binary_iarchive = 13, ///< binary input archive
    polymorphic_iarchive = 14, ///< polymorphic input archive
    polymorphic_oarchive = 15, ///< polymorphic output archive
    serialization_export = 16, ///< export type
    string = 17, ///< std::string support
    vector = 18, ///< std::vector support
    set = 19, ///< std::set support
    deque = 20, ///< std::deque support
    list = 21, ///< std::list support
    serialization_shared_ptr = 22, ///< boost::shared_ptr support
    serialization_optional = 23, ///< boost::optional support
    exception_info = 24, ///< boost exeption base class
    io_ios_state = 25, ///< IO state savers
    string_algorithm = 26, ///< string algorithms
    variant = 27, ///< boost variant
    serialization_variant = 28, ///< variant support
    apply_visitor = 29, ///< Apply visitor
    filesystem_path = 30, ///< filesystem path
    gregorian_date = 31, ///< Boost date time gregorian date
    ptime = 32, ///< Boost date time posix time
    time_duration = 33, ///< Boost date time durantion
    serialization_gregorian_date = 34, ///< Serialisation support forgregorian date
    serialization_ptime = 35, ///< Serialisation support for posix time
    serialization_time_duration = 36, ///< Serialisation support for time durantion
    io_gregorian_date = 37, ///< IO support for date
    io_time = 38, ///< IO support for time and time_duration
    serialization_pair = 39, ///< Serialisation support for std::pair
    ptree = 40,
    serialization_ptree = 41,
    io_ptree = 42,
    eos_oarchive = 43, ///< EOS output archive
    eos_iarchive = 44 ///< EOS input archive
};

} }

#endif
