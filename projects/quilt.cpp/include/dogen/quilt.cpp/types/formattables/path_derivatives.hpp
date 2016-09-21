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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PATH_DERIVATIVES_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PATH_DERIVATIVES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/quilt.cpp/serialization/formattables/path_derivatives_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Properties that derive from the path.
 */
class path_derivatives final {
public:
    path_derivatives() = default;
    path_derivatives(const path_derivatives&) = default;
    ~path_derivatives() = default;

public:
    path_derivatives(path_derivatives&& rhs);

public:
    path_derivatives(
        const boost::filesystem::path& file_path,
        const std::string& header_guard);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::path_derivatives& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::path_derivatives& v, unsigned int version);

public:
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);

public:
    bool operator==(const path_derivatives& rhs) const;
    bool operator!=(const path_derivatives& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_derivatives& other) noexcept;
    path_derivatives& operator=(path_derivatives other);

private:
    boost::filesystem::path file_path_;
    std::string header_guard_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::path_derivatives& lhs,
    dogen::quilt::cpp::formattables::path_derivatives& rhs) {
    lhs.swap(rhs);
}

}

#endif
