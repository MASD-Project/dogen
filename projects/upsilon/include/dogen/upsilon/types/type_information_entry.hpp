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
#ifndef DOGEN_UPSILON_TYPES_TYPE_INFORMATION_ENTRY_HPP
#define DOGEN_UPSILON_TYPES_TYPE_INFORMATION_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/upsilon/serialization/type_information_entry_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class type_information_entry final {
public:
    type_information_entry() = default;
    type_information_entry(const type_information_entry&) = default;
    ~type_information_entry() = default;

public:
    type_information_entry(type_information_entry&& rhs);

public:
    type_information_entry(
        const std::string& name,
        const std::string& pof_id,
        const boost::filesystem::path& file_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::type_information_entry& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::type_information_entry& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& pof_id() const;
    std::string& pof_id();
    void pof_id(const std::string& v);
    void pof_id(const std::string&& v);

    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

public:
    bool operator==(const type_information_entry& rhs) const;
    bool operator!=(const type_information_entry& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_information_entry& other) noexcept;
    type_information_entry& operator=(type_information_entry other);

private:
    std::string name_;
    std::string pof_id_;
    boost::filesystem::path file_path_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::type_information_entry& lhs,
    dogen::upsilon::type_information_entry& rhs) {
    lhs.swap(rhs);
}

}

#endif
