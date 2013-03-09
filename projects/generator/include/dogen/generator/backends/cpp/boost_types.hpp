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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_BOOST_TYPES_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_BOOST_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

/**
 * @brief Available types in the boost model
 */
enum class boost_types : unsigned int {
    invalid = 0, ///< not a valid boost type
    optional, ///< boost optional
    format, ///< boost formatting library
    shared_ptr, ///< boost shared pointer
    nvp, ///< name value pair
    split_free, ///< split load from save
    assume_abstract, ///< assume class is abstract
    is_virtual_base_of, ///< ensure class is virtual base
    xml_oarchive, ///< XML output archive
    xml_iarchive, ///< XML input archive
    text_oarchive, ///< text output archive
    text_iarchive, ///< text input archive
    binary_oarchive, ///< binary output archive
    binary_iarchive, ///< binary input archive
    polymorphic_iarchive, ///< polymorphic input archive
    polymorphic_oarchive, ///< polymorphic output archive
    serialization_export, ///< export type
    string, ///< std::string support
    vector, ///< std::vector support
    set, ///< std::set support
    deque, ///< std::deque support
    list, ///< std::list support
    serialization_shared_ptr, ///< boost::shared_ptr support
    serialization_optional, ///< boost::optional support
    exception_info, ///< boost exeption base class
    io_ios_state, ///< IO state savers
    string_algorithm, ///< string algorithms
    variant, ///< boost variant
    serialization_variant, ///< variant support
    apply_visitor, ///< Apply visitor
    filesystem_path, ///< filesystem path
    gregorian_date, ///< Boost date time gregorian date
    ptime, ///< Boost date time posix time
    time_duration, ///< Boost date time durantion
    serialization_gregorian_date, ///< Serialisation support forgregorian date
    serialization_ptime, ///< Serialisation support for posix time
    serialization_time_duration, ///< Serialisation support for time durantion
    io_gregorian_date, ///< IO support for date
    io_time, ///< IO support for time and time_duration
    serialization_pair ///< Serialisation support for std::pair
};

} } } }

#endif
