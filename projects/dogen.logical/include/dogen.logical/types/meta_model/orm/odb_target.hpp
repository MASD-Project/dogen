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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_ORM_ODB_TARGET_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_ORM_ODB_TARGET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>

namespace dogen::logical::meta_model::orm {

class odb_target final {
public:
    odb_target() = default;
    odb_target(const odb_target&) = default;
    odb_target(odb_target&&) = default;
    ~odb_target() = default;

public:
    odb_target(
        const std::string& name,
        const std::string& comment,
        const std::string& output_directory,
        const std::string& types_file,
        const std::list<std::pair<std::string, std::string> >& move_parameters,
        const std::string& object_odb_options);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& comment() const;
    std::string& comment();
    void comment(const std::string& v);
    void comment(const std::string&& v);

    const std::string& output_directory() const;
    std::string& output_directory();
    void output_directory(const std::string& v);
    void output_directory(const std::string&& v);

    const std::string& types_file() const;
    std::string& types_file();
    void types_file(const std::string& v);
    void types_file(const std::string&& v);

    const std::list<std::pair<std::string, std::string> >& move_parameters() const;
    std::list<std::pair<std::string, std::string> >& move_parameters();
    void move_parameters(const std::list<std::pair<std::string, std::string> >& v);
    void move_parameters(const std::list<std::pair<std::string, std::string> >&& v);

    const std::string& object_odb_options() const;
    std::string& object_odb_options();
    void object_odb_options(const std::string& v);
    void object_odb_options(const std::string&& v);

public:
    bool operator==(const odb_target& rhs) const;
    bool operator!=(const odb_target& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(odb_target& other) noexcept;
    odb_target& operator=(odb_target other);

private:
    std::string name_;
    std::string comment_;
    std::string output_directory_;
    std::string types_file_;
    std::list<std::pair<std::string, std::string> > move_parameters_;
    std::string object_odb_options_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::orm::odb_target& lhs,
    dogen::logical::meta_model::orm::odb_target& rhs) {
    lhs.swap(rhs);
}

}

#endif
