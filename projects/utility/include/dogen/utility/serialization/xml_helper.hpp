/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_SERIALIZATION_XML_HELPER_HPP
#define DOGEN_UTILITY_SERIALIZATION_XML_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

namespace dogen {
namespace utility {
namespace serialization {

/**
 * @brief Reads in the file given by path and deserialises it.
 */
template<typename Entity>
Entity xml_deserialize(boost::filesystem::path path) {
    boost::filesystem::ifstream input_stream(path);
    boost::archive::xml_iarchive input_archive(input_stream);
    Entity entity;
    input_archive >> BOOST_SERIALIZATION_NVP(entity);
    return entity;
}

/**
 * @brief Serialises the given entity into actual_path and
 * compares the result with the deserialised value of
 * expected_path.
 */
template<typename Entity>
void xml_serialize(boost::filesystem::path path, Entity entity) {
    boost::filesystem::ofstream output_stream(path);
    boost::archive::xml_oarchive input_archive(output_stream);
    input_archive << BOOST_SERIALIZATION_NVP(entity);
}

} } }

#endif
