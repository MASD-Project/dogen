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
#ifndef DOGEN_CPP_TYPES_SETTINGS_CPP_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_CPP_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <string>
#include "dogen/cpp/serialization/settings/cpp_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class cpp_settings final {
public:
    cpp_settings(const cpp_settings&) = default;
    ~cpp_settings() = default;

public:
    cpp_settings();

public:
    cpp_settings(cpp_settings&& rhs);

public:
    cpp_settings(
        const bool enabled,
        const bool split_project,
        const std::string& source_directory_name,
        const std::string& include_directory_name,
        const std::string& header_file_extension,
        const std::string& implementation_file_extension,
        const bool enable_facet_folders,
        const bool enable_unique_file_names,
        const boost::filesystem::path& project_directory_path,
        const boost::filesystem::path& source_directory_path,
        const boost::filesystem::path& include_directory_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_settings& v, unsigned int version);

public:
    bool enabled() const;
    void enabled(const bool v);

    bool split_project() const;
    void split_project(const bool v);

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    const std::string& include_directory_name() const;
    std::string& include_directory_name();
    void include_directory_name(const std::string& v);
    void include_directory_name(const std::string&& v);

    const std::string& header_file_extension() const;
    std::string& header_file_extension();
    void header_file_extension(const std::string& v);
    void header_file_extension(const std::string&& v);

    const std::string& implementation_file_extension() const;
    std::string& implementation_file_extension();
    void implementation_file_extension(const std::string& v);
    void implementation_file_extension(const std::string&& v);

    bool enable_facet_folders() const;
    void enable_facet_folders(const bool v);

    bool enable_unique_file_names() const;
    void enable_unique_file_names(const bool v);

    const boost::filesystem::path& project_directory_path() const;
    boost::filesystem::path& project_directory_path();
    void project_directory_path(const boost::filesystem::path& v);
    void project_directory_path(const boost::filesystem::path&& v);

    const boost::filesystem::path& source_directory_path() const;
    boost::filesystem::path& source_directory_path();
    void source_directory_path(const boost::filesystem::path& v);
    void source_directory_path(const boost::filesystem::path&& v);

    const boost::filesystem::path& include_directory_path() const;
    boost::filesystem::path& include_directory_path();
    void include_directory_path(const boost::filesystem::path& v);
    void include_directory_path(const boost::filesystem::path&& v);

public:
    bool operator==(const cpp_settings& rhs) const;
    bool operator!=(const cpp_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cpp_settings& other) noexcept;
    cpp_settings& operator=(cpp_settings other);

private:
    bool enabled_;
    bool split_project_;
    std::string source_directory_name_;
    std::string include_directory_name_;
    std::string header_file_extension_;
    std::string implementation_file_extension_;
    bool enable_facet_folders_;
    bool enable_unique_file_names_;
    boost::filesystem::path project_directory_path_;
    boost::filesystem::path source_directory_path_;
    boost::filesystem::path include_directory_path_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::cpp_settings& lhs,
    dogen::cpp::settings::cpp_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
