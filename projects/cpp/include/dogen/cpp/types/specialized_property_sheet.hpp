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
#ifndef DOGEN_CPP_TYPES_SPECIALIZED_PROPERTY_SHEET_HPP
#define DOGEN_CPP_TYPES_SPECIALIZED_PROPERTY_SHEET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/cpp/serialization/specialized_property_sheet_fwd_ser.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Property sheet specialised for C++ files.
 */
class specialized_property_sheet final {
public:
    specialized_property_sheet(const specialized_property_sheet&) = default;
    specialized_property_sheet(specialized_property_sheet&&) = default;
    ~specialized_property_sheet() = default;

public:
    specialized_property_sheet();

public:
    specialized_property_sheet(
        const bool generate_header_guards,
        const bool split_project,
        const std::string& source_directory,
        const std::string& include_directory,
        const std::string& header_file_extension,
        const std::string& implementation_file_extension,
        const std::string& forward_declaration_postfix);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const specialized_property_sheet& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, specialized_property_sheet& v, unsigned int version);

public:
    /**
     * @brief If set to true, the file will contain header guards.
     */
    /**@{*/
    bool generate_header_guards() const;
    void generate_header_guards(const bool v);
    /**@}*/

    /**
     * @brief If true, the project will be split.
     *
     * @deprecated used only for backwards compatibility.
     */
    /**@{*/
    bool split_project() const;
    void split_project(const bool v);
    /**@}*/

    /**
     * @brief Name of the directory in which to place the implementation files.
     */
    /**@{*/
    const std::string& source_directory() const;
    std::string& source_directory();
    void source_directory(const std::string& v);
    void source_directory(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the directory in which to place the header files.
     */
    /**@{*/
    const std::string& include_directory() const;
    std::string& include_directory();
    void include_directory(const std::string& v);
    void include_directory(const std::string&& v);
    /**@}*/

    /**
     * @brief Extension to use for header files, including the leading dot.
     *
     * Example: @e .hpp, @e .hxx
     */
    /**@{*/
    const std::string& header_file_extension() const;
    std::string& header_file_extension();
    void header_file_extension(const std::string& v);
    void header_file_extension(const std::string&& v);
    /**@}*/

    /**
     * @brief Extension to use for implementation files, including the leading dot.
     *
     * Example: @e .cpp, @e .cxx.
     */
    /**@{*/
    const std::string& implementation_file_extension() const;
    std::string& implementation_file_extension();
    void implementation_file_extension(const std::string& v);
    void implementation_file_extension(const std::string&& v);
    /**@}*/

    /**
     * @brief Postfix to use for all forward declaration files.
     */
    /**@{*/
    const std::string& forward_declaration_postfix() const;
    std::string& forward_declaration_postfix();
    void forward_declaration_postfix(const std::string& v);
    void forward_declaration_postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const specialized_property_sheet& rhs) const;
    bool operator!=(const specialized_property_sheet& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(specialized_property_sheet& other) noexcept;
    specialized_property_sheet& operator=(specialized_property_sheet other);

private:
    bool generate_header_guards_;
    bool split_project_;
    std::string source_directory_;
    std::string include_directory_;
    std::string header_file_extension_;
    std::string implementation_file_extension_;
    std::string forward_declaration_postfix_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::specialized_property_sheet& lhs,
    dogen::cpp::specialized_property_sheet& rhs) {
    lhs.swap(rhs);
}

}

#endif
