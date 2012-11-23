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
#ifndef DOGEN_SML_DOMAIN_REFERENCE_HPP
#define DOGEN_SML_DOMAIN_REFERENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>

namespace dogen {
namespace sml {

class reference_serializer;

class reference {
public:
    reference(const reference&) = default;
    ~reference() = default;
    reference(reference&&) = default;
    reference& operator=(const reference&) = default;

private:
    friend class reference_serializer;

public:
    reference() : is_system_(false) { }

    reference(std::string model_name,
        std::list<std::string> external_package_path,
        bool is_system) :
        model_name_(model_name),
        external_package_path_(external_package_path),
        is_system_(is_system) { }

public:
    /**
     * @brief Model which we depend on.
     */
    std::string model_name() const { return(model_name_); }
    void model_name(std::string value) { model_name_ = value; }

    /**
     * @brief Path of packages that contain the dependent model.
     */
    std::list<std::string> external_package_path() const {
        return(external_package_path_);
    }
    void external_package_path(std::list<std::string> value) {
        external_package_path_ = value;
    }

    /**
     * @brief If true, the dependent model is a system model.
     */
    bool is_system() const { return(is_system_); }
    void is_system(bool value) { is_system_ = value; }

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const reference& rhs) const;

    bool operator!=(const reference& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    std::string model_name_;
    std::list<std::string> external_package_path_;
    bool is_system_;
};

} }

#endif
