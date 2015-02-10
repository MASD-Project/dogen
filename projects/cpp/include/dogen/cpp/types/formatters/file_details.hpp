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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FILE_DETAILS_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FILE_DETAILS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <string>
#include "dogen/cpp/serialization/formatters/file_details_fwd_ser.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Details required to build both the absolute and relative file paths.
 */
class file_details final {
public:
    file_details(const file_details&) = default;
    ~file_details() = default;

public:
    file_details();

public:
    file_details(file_details&& rhs);

public:
    file_details(
        const bool split_project,
        const dogen::cpp::formatters::file_types& file_type,
        const std::string& facet_directory,
        const std::string& extension,
        const std::string& facet_postfix,
        const std::string& formatter_postfix,
        const boost::filesystem::path& project_directory,
        const boost::filesystem::path& source_directory,
        const boost::filesystem::path& include_directory);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const file_details& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, file_details& v, unsigned int version);

public:
    bool split_project() const;
    void split_project(const bool v);

    dogen::cpp::formatters::file_types file_type() const;
    void file_type(const dogen::cpp::formatters::file_types& v);

    const std::string& facet_directory() const;
    std::string& facet_directory();
    void facet_directory(const std::string& v);
    void facet_directory(const std::string&& v);

    const std::string& extension() const;
    std::string& extension();
    void extension(const std::string& v);
    void extension(const std::string&& v);

    const std::string& facet_postfix() const;
    std::string& facet_postfix();
    void facet_postfix(const std::string& v);
    void facet_postfix(const std::string&& v);

    const std::string& formatter_postfix() const;
    std::string& formatter_postfix();
    void formatter_postfix(const std::string& v);
    void formatter_postfix(const std::string&& v);

    const boost::filesystem::path& project_directory() const;
    boost::filesystem::path& project_directory();
    void project_directory(const boost::filesystem::path& v);
    void project_directory(const boost::filesystem::path&& v);

    const boost::filesystem::path& source_directory() const;
    boost::filesystem::path& source_directory();
    void source_directory(const boost::filesystem::path& v);
    void source_directory(const boost::filesystem::path&& v);

    const boost::filesystem::path& include_directory() const;
    boost::filesystem::path& include_directory();
    void include_directory(const boost::filesystem::path& v);
    void include_directory(const boost::filesystem::path&& v);

public:
    bool operator==(const file_details& rhs) const;
    bool operator!=(const file_details& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file_details& other) noexcept;
    file_details& operator=(file_details other);

private:
    bool split_project_;
    dogen::cpp::formatters::file_types file_type_;
    std::string facet_directory_;
    std::string extension_;
    std::string facet_postfix_;
    std::string formatter_postfix_;
    boost::filesystem::path project_directory_;
    boost::filesystem::path source_directory_;
    boost::filesystem::path include_directory_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formatters::file_details& lhs,
    dogen::cpp::formatters::file_details& rhs) {
    lhs.swap(rhs);
}

}

#endif
