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
#ifndef DOGEN_GENERATOR_CONFIG_REFERENCE_HPP
#define DOGEN_GENERATOR_CONFIG_REFERENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace generator {
namespace config {

class reference {
public:
    reference() = default;
    reference(const reference&) = default;
    ~reference() = default;
    reference& operator=(const reference&) = default;

public:
    reference(const reference&& rhs)
    : path_(std::move(rhs.path_)),
      external_package_path_(std::move(rhs.external_package_path_)) { }

public:
    /**
     * @brief Path to the model we're referring to.
     */
    /**@{*/
    boost::filesystem::path path() const { return path_; }
    reference& path(boost::filesystem::path v) {
        path_ = v;
        return *this;
    }
    /**@}*/

    /**
     * @brief External package path to dependent model.
     */
    /**@{*/
    std::string external_package_path() const {
        return external_package_path_;
    }
    reference& external_package_path(std::string v) {
        external_package_path_ = v;
        return *this;
    }
    /**@}*/

private:
    boost::filesystem::path path_;
    std::string external_package_path_;
};

std::ostream& operator<<(std::ostream& stream, reference value);

} } }

#endif
