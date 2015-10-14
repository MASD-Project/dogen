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
#ifndef DOGEN_UTILITY_SERIALIZATION_XML_HELPER_HPP
#define DOGEN_UTILITY_SERIALIZATION_XML_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/filesystem/file_not_found.hpp"

namespace dogen {
namespace utility {
namespace serialization {

/**
 * @brief Reads in the file given by path and deserialises it.
 */
template<typename Entity>
Entity xml_deserialize(boost::filesystem::path path) {
    if (!boost::filesystem::exists(path))
        BOOST_THROW_EXCEPTION(utility::filesystem::file_not_found(path.string()));

    boost::filesystem::ifstream input_stream(path);
    boost::archive::xml_iarchive input_archive(input_stream);
    Entity entity;
    input_archive >> BOOST_SERIALIZATION_NVP(entity);
    return entity;
}

/**
 * @brief Serialises entity into the file given by path.
 */
template<typename Entity>
void xml_serialize(boost::filesystem::path path, Entity entity) {
    boost::filesystem::ofstream output_stream(path);
    boost::archive::xml_oarchive input_archive(output_stream);
    input_archive << BOOST_SERIALIZATION_NVP(entity);
}

} } }

#endif
