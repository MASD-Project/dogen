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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_ODB_TARGETS_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_ODB_TARGETS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/types/fabric/odb_target.hpp"
#include "dogen/quilt.cpp/serialization/fabric/odb_targets_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class odb_targets final {
public:
    odb_targets() = default;
    odb_targets(const odb_targets&) = default;
    odb_targets(odb_targets&&) = default;
    ~odb_targets() = default;

public:
    odb_targets(
        const std::string& main_target_name,
        const std::string& options_file,
        const std::list<dogen::quilt::cpp::fabric::odb_target>& targets);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::odb_targets& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::odb_targets& v, unsigned int version);

public:
    const std::string& main_target_name() const;
    std::string& main_target_name();
    void main_target_name(const std::string& v);
    void main_target_name(const std::string&& v);

    const std::string& options_file() const;
    std::string& options_file();
    void options_file(const std::string& v);
    void options_file(const std::string&& v);

    const std::list<dogen::quilt::cpp::fabric::odb_target>& targets() const;
    std::list<dogen::quilt::cpp::fabric::odb_target>& targets();
    void targets(const std::list<dogen::quilt::cpp::fabric::odb_target>& v);
    void targets(const std::list<dogen::quilt::cpp::fabric::odb_target>&& v);

public:
    bool operator==(const odb_targets& rhs) const;
    bool operator!=(const odb_targets& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(odb_targets& other) noexcept;
    odb_targets& operator=(odb_targets other);

private:
    std::string main_target_name_;
    std::string options_file_;
    std::list<dogen::quilt::cpp::fabric::odb_target> targets_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::odb_targets& lhs,
    dogen::quilt::cpp::fabric::odb_targets& rhs) {
    lhs.swap(rhs);
}

}

#endif
