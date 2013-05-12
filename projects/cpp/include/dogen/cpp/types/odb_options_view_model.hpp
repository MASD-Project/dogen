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
#ifndef DOGEN_CPP_TYPES_ODB_OPTIONS_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_ODB_OPTIONS_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <string>
#include "dogen/cpp/serialization/odb_options_view_model_fwd_ser.hpp"

namespace dogen {
namespace cpp {

class odb_options_view_model final {
public:
    odb_options_view_model() = default;
    odb_options_view_model(const odb_options_view_model&) = default;
    ~odb_options_view_model() = default;

public:
    odb_options_view_model(odb_options_view_model&& rhs);

public:
    odb_options_view_model(
        const std::string& model_name,
        const std::string& product_name,
        const boost::filesystem::path& file_path,
        const std::string& file_name,
        const std::string& odb_folder);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const odb_options_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, odb_options_view_model& v, unsigned int version);

public:
    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);

    const std::string& product_name() const;
    std::string& product_name();
    void product_name(const std::string& v);
    void product_name(const std::string&& v);

    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

    const std::string& file_name() const;
    std::string& file_name();
    void file_name(const std::string& v);
    void file_name(const std::string&& v);

    const std::string& odb_folder() const;
    std::string& odb_folder();
    void odb_folder(const std::string& v);
    void odb_folder(const std::string&& v);

public:
    bool operator==(const odb_options_view_model& rhs) const;
    bool operator!=(const odb_options_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(odb_options_view_model& other) noexcept;
    odb_options_view_model& operator=(odb_options_view_model other);

private:
    std::string model_name_;
    std::string product_name_;
    boost::filesystem::path file_path_;
    std::string file_name_;
    std::string odb_folder_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::odb_options_view_model& lhs,
    dogen::cpp::odb_options_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
