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
#ifndef DOGEN_SML_TYPES_META_DATA_READER_HPP
#define DOGEN_SML_TYPES_META_DATA_READER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/property_tree/ptree.hpp>

namespace dogen {
namespace sml {

class meta_data_reader {
public:
    meta_data_reader() = delete;
    ~meta_data_reader() noexcept = default;
    meta_data_reader(const meta_data_reader&) = default;
    meta_data_reader(meta_data_reader&&) = default;

public:
    meta_data_reader(const boost::property_tree::ptree& meta_data);

public:
    /**
     * @brief Returns true if the key exists, false otherwise.
     */
    bool has_key(const std::string& key) const;

    /**
     * @brief Returns true if the key exists and its value is set to
     * boolean true.
     */
    bool is_true(const std::string& key) const;

    /**
     * @brief Returns the negation of @e is_true.
     */
    bool is_false(const std::string& key) const;

    /**
     * @brief Returns the value associated with the key, if it exists.
     */
    std::string get(const std::string& key) const;

    /**
     * @brief Returns true if the key exists and its value is set to
     * supported.
     */
    bool is_supported(const std::string& key) const;

public:
    /**
     * @brief Returns the odb pragmas.
     *
     * @deprecated this method is only needed for the transition to
     * OM.
     */
    std::list<std::pair<std::string,std::string> > odb_pragma() const;

private:
    const boost::property_tree::ptree& meta_data_;
};

} }

#endif
