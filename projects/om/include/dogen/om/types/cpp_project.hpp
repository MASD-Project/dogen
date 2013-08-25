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
#ifndef DOGEN_OM_TYPES_CPP_PROJECT_HPP
#define DOGEN_OM_TYPES_CPP_PROJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <list>
#include "dogen/om/serialization/cpp_project_fwd_ser.hpp"
#include "dogen/om/types/cmake_file.hpp"
#include "dogen/om/types/cpp_file.hpp"
#include "dogen/om/types/odb_options_file.hpp"

namespace dogen {
namespace om {

/**
 * @brief Represents a C++ project composed of different kinds of text files.
 */
class cpp_project final {
public:
    cpp_project() = default;
    cpp_project(const cpp_project&) = default;
    ~cpp_project() = default;

public:
    cpp_project(cpp_project&& rhs);

public:
    cpp_project(
        const std::list<dogen::om::cmake_file>& makefiles,
        const boost::optional<dogen::om::odb_options_file>& odb_options,
        const std::list<dogen::om::cpp_file>& cpp_files);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_project& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_project& v, unsigned int version);

public:
    /**
     * @brief All CMake make files associated with a project.
     */
    /**@{*/
    const std::list<dogen::om::cmake_file>& makefiles() const;
    std::list<dogen::om::cmake_file>& makefiles();
    void makefiles(const std::list<dogen::om::cmake_file>& v);
    void makefiles(const std::list<dogen::om::cmake_file>&& v);
    /**@}*/

    const boost::optional<dogen::om::odb_options_file>& odb_options() const;
    boost::optional<dogen::om::odb_options_file>& odb_options();
    void odb_options(const boost::optional<dogen::om::odb_options_file>& v);
    void odb_options(const boost::optional<dogen::om::odb_options_file>&& v);

    /**
     * @brief All C++ files associated with the project.
     */
    /**@{*/
    const std::list<dogen::om::cpp_file>& cpp_files() const;
    std::list<dogen::om::cpp_file>& cpp_files();
    void cpp_files(const std::list<dogen::om::cpp_file>& v);
    void cpp_files(const std::list<dogen::om::cpp_file>&& v);
    /**@}*/

public:
    bool operator==(const cpp_project& rhs) const;
    bool operator!=(const cpp_project& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cpp_project& other) noexcept;
    cpp_project& operator=(cpp_project other);

private:
    std::list<dogen::om::cmake_file> makefiles_;
    boost::optional<dogen::om::odb_options_file> odb_options_;
    std::list<dogen::om::cpp_file> cpp_files_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_project& lhs,
    dogen::om::cpp_project& rhs) {
    lhs.swap(rhs);
}

}

#endif
