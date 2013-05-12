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
#ifndef DOGEN_CPP_TYPES_CMAKELISTS_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_CMAKELISTS_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <string>
#include "dogen/cpp/serialization/cmakelists_view_model_fwd_ser.hpp"

namespace dogen {
namespace cpp {

class cmakelists_view_model final {
public:
    cmakelists_view_model() = default;
    cmakelists_view_model(const cmakelists_view_model&) = default;
    ~cmakelists_view_model() = default;

public:
    cmakelists_view_model(cmakelists_view_model&& rhs);

public:
    cmakelists_view_model(
        const boost::filesystem::path& file_path,
        const std::string& model_name,
        const std::string& product_name,
        const std::string& file_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cmakelists_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cmakelists_view_model& v, unsigned int version);

public:
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);

    const std::string& product_name() const;
    std::string& product_name();
    void product_name(const std::string& v);
    void product_name(const std::string&& v);

    const std::string& file_name() const;
    std::string& file_name();
    void file_name(const std::string& v);
    void file_name(const std::string&& v);

public:
    bool operator==(const cmakelists_view_model& rhs) const;
    bool operator!=(const cmakelists_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cmakelists_view_model& other) noexcept;
    cmakelists_view_model& operator=(cmakelists_view_model other);

private:
    boost::filesystem::path file_path_;
    std::string model_name_;
    std::string product_name_;
    std::string file_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::cmakelists_view_model& lhs,
    dogen::cpp::cmakelists_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
