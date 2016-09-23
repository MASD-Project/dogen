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
#ifndef DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_PATH_ANNOTATIONS_HPP
#define DOGEN_QUILT_CPP_TYPES_ANNOTATIONS_PATH_ANNOTATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/annotations/path_annotations_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

class path_annotations final {
public:
    path_annotations(const path_annotations&) = default;
    path_annotations(path_annotations&&) = default;
    ~path_annotations() = default;

public:
    path_annotations();

public:
    path_annotations(
        const std::string& facet_directory,
        const std::string& facet_postfix,
        const std::string& formatter_postfix,
        const std::string& include_directory_name,
        const std::string& source_directory_name,
        const bool disable_facet_directories,
        const std::string& header_file_extension,
        const std::string& implementation_file_extension);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::annotations::path_annotations& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::annotations::path_annotations& v, unsigned int version);

public:
    const std::string& facet_directory() const;
    std::string& facet_directory();
    void facet_directory(const std::string& v);
    void facet_directory(const std::string&& v);

    const std::string& facet_postfix() const;
    std::string& facet_postfix();
    void facet_postfix(const std::string& v);
    void facet_postfix(const std::string&& v);

    const std::string& formatter_postfix() const;
    std::string& formatter_postfix();
    void formatter_postfix(const std::string& v);
    void formatter_postfix(const std::string&& v);

    const std::string& include_directory_name() const;
    std::string& include_directory_name();
    void include_directory_name(const std::string& v);
    void include_directory_name(const std::string&& v);

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    bool disable_facet_directories() const;
    void disable_facet_directories(const bool v);

    const std::string& header_file_extension() const;
    std::string& header_file_extension();
    void header_file_extension(const std::string& v);
    void header_file_extension(const std::string&& v);

    const std::string& implementation_file_extension() const;
    std::string& implementation_file_extension();
    void implementation_file_extension(const std::string& v);
    void implementation_file_extension(const std::string&& v);

public:
    bool operator==(const path_annotations& rhs) const;
    bool operator!=(const path_annotations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_annotations& other) noexcept;
    path_annotations& operator=(path_annotations other);

private:
    std::string facet_directory_;
    std::string facet_postfix_;
    std::string formatter_postfix_;
    std::string include_directory_name_;
    std::string source_directory_name_;
    bool disable_facet_directories_;
    std::string header_file_extension_;
    std::string implementation_file_extension_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::annotations::path_annotations& lhs,
    dogen::quilt::cpp::annotations::path_annotations& rhs) {
    lhs.swap(rhs);
}

}

#endif
