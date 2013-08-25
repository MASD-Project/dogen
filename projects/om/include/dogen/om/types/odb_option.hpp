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
#ifndef DOGEN_OM_TYPES_ODB_OPTION_HPP
#define DOGEN_OM_TYPES_ODB_OPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include "dogen/om/serialization/odb_option_fwd_ser.hpp"

namespace dogen {
namespace om {

/**
 * @brief Command line options for ODB.
 */
class odb_option {
public:
    odb_option() = default;
    odb_option(const odb_option&) = default;
    odb_option(odb_option&&) = default;

    virtual ~odb_option() noexcept = 0;

public:
    explicit odb_option(const std::string& comment);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const odb_option& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, odb_option& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    const std::string& comment() const;
    std::string& comment();
    void comment(const std::string& v);
    void comment(const std::string&& v);

protected:
    bool compare(const odb_option& rhs) const;
public:
    virtual bool equals(const odb_option& other) const = 0;

protected:
    void swap(odb_option& other) noexcept;

private:
    std::string comment_;
};

inline odb_option::~odb_option() noexcept { }

inline bool operator==(const odb_option& lhs, const odb_option& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
