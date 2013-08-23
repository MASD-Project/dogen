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
#ifndef DOGEN_CPPIM_TYPES_PROJECT_HPP
#define DOGEN_CPPIM_TYPES_PROJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include "dogen/cppim/serialization/project_fwd_ser.hpp"
#include "dogen/cppim/types/text_file.hpp"

namespace dogen {
namespace cppim {

/**
 * @brief Represents a C++ project composed of different kinds of text files.
 */
class project final {
public:
    project() = default;
    project(const project&) = default;
    project(project&&) = default;
    ~project() = default;

public:
    explicit project(const std::list<dogen::cppim::text_file>& files);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const project& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, project& v, unsigned int version);

public:
    /**
     * @brief All files associated with a project.
     */
    /**@{*/
    const std::list<dogen::cppim::text_file>& files() const;
    std::list<dogen::cppim::text_file>& files();
    void files(const std::list<dogen::cppim::text_file>& v);
    void files(const std::list<dogen::cppim::text_file>&& v);
    /**@}*/

public:
    bool operator==(const project& rhs) const;
    bool operator!=(const project& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(project& other) noexcept;
    project& operator=(project other);

private:
    std::list<dogen::cppim::text_file> files_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cppim::project& lhs,
    dogen::cppim::project& rhs) {
    lhs.swap(rhs);
}

}

#endif
