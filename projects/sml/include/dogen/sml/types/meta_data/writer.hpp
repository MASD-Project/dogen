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
#ifndef DOGEN_SML_TYPES_META_DATA_WRITER_HPP
#define DOGEN_SML_TYPES_META_DATA_WRITER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif
#include <list>
#include <boost/property_tree/ptree.hpp>

namespace dogen {
namespace sml {
namespace meta_data {

/**
 * @brief Given one or more key-value pairs, adds them to the
 * meta-data container.
 */
class writer {
public:
    writer() = delete;
    ~writer() noexcept = default;
    writer(const writer&) = default;
    writer(writer&&) = default;

public:
    writer(boost::property_tree::ptree& meta_data);

private:
    /**
     * @brief Returns true if the supplied key should have a container
     * value.
     */
    bool is_container(const std::string& key) const;

    /**
     * @brief Returns true if the key exists, false otherwise.
     */
    bool has_key(const std::string& key) const;

public:
    /**
     * @brief Adds the key-value pair.
     *
     * If the key implies a container, generates the appropriate
     * structure.
     */
    void add(const std::string& key, const std::string& value);

    /**
     * @brief Adds all key-value pairs.
     */
    void add(const std::list<std::pair<std::string, std::string> >& kvps);

    /**
     * @brief Adds only if @e marker is found in the input kvp
     * container, as a key.
     *
     * @return true if added, false otherwise.
     */
    bool add_if_marker_found(const std::string& marker,
        const std::list<std::pair<std::string, std::string> >& kvps);

    /**
     * @brief Adds only if @e key is not in the simple meta_data
     * container.
     *
     * @return true if added, false otherwise.
     */
    bool add_if_key_not_found(const std::string& key, const std::string& value);

private:
    boost::property_tree::ptree& meta_data_;
};

} } }

#endif
