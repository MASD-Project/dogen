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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_ODB_TARGET_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_ODB_TARGET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/fabric/odb_target_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

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
        const std::string& pragmas_file,
        const std::string& types_file,
        const std::list<std::string>& include_regexes,
        const std::string& header_guard_prefix,
        const std::list<std::pair<std::string, std::string> >& move_parameters);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::odb_target& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::odb_target& v, unsigned int version);

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

    const std::string& pragmas_file() const;
    std::string& pragmas_file();
    void pragmas_file(const std::string& v);
    void pragmas_file(const std::string&& v);

    const std::string& types_file() const;
    std::string& types_file();
    void types_file(const std::string& v);
    void types_file(const std::string&& v);

    const std::list<std::string>& include_regexes() const;
    std::list<std::string>& include_regexes();
    void include_regexes(const std::list<std::string>& v);
    void include_regexes(const std::list<std::string>&& v);

    const std::string& header_guard_prefix() const;
    std::string& header_guard_prefix();
    void header_guard_prefix(const std::string& v);
    void header_guard_prefix(const std::string&& v);

    const std::list<std::pair<std::string, std::string> >& move_parameters() const;
    std::list<std::pair<std::string, std::string> >& move_parameters();
    void move_parameters(const std::list<std::pair<std::string, std::string> >& v);
    void move_parameters(const std::list<std::pair<std::string, std::string> >&& v);

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
    std::string pragmas_file_;
    std::string types_file_;
    std::list<std::string> include_regexes_;
    std::string header_guard_prefix_;
    std::list<std::pair<std::string, std::string> > move_parameters_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::odb_target& lhs,
    dogen::quilt::cpp::fabric::odb_target& rhs) {
    lhs.swap(rhs);
}

}

#endif
