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
#ifndef DOGEN_UTILITY_TEST_SERIALIZATION_HELPER_HPP
#define DOGEN_UTILITY_TEST_SERIALIZATION_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/throw_exception.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/file_not_found.hpp"

template<typename Archive> void register_types(Archive& ar);

namespace dogen::utility::test {

/**
 * @brief Reads in the file given by path and deserialises it.
 */
template<typename Entity>
Entity xml_deserialize(boost::filesystem::path path) {
    using namespace dogen::utility::log;
    logger lg(logger_factory("utility.test.xml_deserialize"));
    BOOST_LOG_SEV(lg, debug) << "Reading file: " << path.string();

    if (!boost::filesystem::exists(path)) {
        BOOST_LOG_SEV(lg, error) << "Could not find file: " << path.string();
        BOOST_THROW_EXCEPTION(utility::filesystem::file_not_found(path.string()));
    }

    boost::filesystem::ifstream input_stream(path);
    boost::archive::xml_iarchive input_archive(input_stream);
    Entity entity;
    ::register_types(input_archive);
    input_archive >> BOOST_SERIALIZATION_NVP(entity);
    BOOST_LOG_SEV(lg, debug) << "Read file.";
    BOOST_LOG_SEV(lg, debug) << entity;
    return entity;
}

/**
 * @brief Serialises the given entity into actual_path and
 * compares the result with the deserialised value of
 * expected_path.
 */
template<typename Entity>
void xml_serialize(boost::filesystem::path path, Entity entity) {
    using namespace dogen::utility::log;
    logger lg(logger_factory("utility.test.xml_serialize"));
    BOOST_LOG_SEV(lg, debug) << "Creating file: " << path.string();

    boost::filesystem::ofstream output_stream(path);
    boost::archive::xml_oarchive input_archive(output_stream);
    ::register_types(input_archive);
    input_archive << BOOST_SERIALIZATION_NVP(entity);
    BOOST_LOG_SEV(lg, debug) << "Created file.";
}

}

#endif
