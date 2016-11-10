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
#ifndef DOGEN_OPTIONS_TYPES_TAILORING_OPTIONS_HPP
#define DOGEN_OPTIONS_TYPES_TAILORING_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/options/serialization/tailoring_options_fwd_ser.hpp"

namespace dogen {
namespace options {

class tailoring_options final {
public:
    tailoring_options(const tailoring_options&) = default;
    ~tailoring_options() = default;

public:
    tailoring_options();

public:
    tailoring_options(tailoring_options&& rhs);

public:
    tailoring_options(
        const bool verbose,
        const boost::filesystem::path& target,
        const std::string& output_extension,
        const bool force_write);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::options::tailoring_options& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::options::tailoring_options& v, unsigned int version);

public:
    bool verbose() const;
    void verbose(const bool v);

    const boost::filesystem::path& target() const;
    boost::filesystem::path& target();
    void target(const boost::filesystem::path& v);
    void target(const boost::filesystem::path&& v);

    const std::string& output_extension() const;
    std::string& output_extension();
    void output_extension(const std::string& v);
    void output_extension(const std::string&& v);

    bool force_write() const;
    void force_write(const bool v);

public:
    bool operator==(const tailoring_options& rhs) const;
    bool operator!=(const tailoring_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(tailoring_options& other) noexcept;
    tailoring_options& operator=(tailoring_options other);

private:
    bool verbose_;
    boost::filesystem::path target_;
    std::string output_extension_;
    bool force_write_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::options::tailoring_options& lhs,
    dogen::options::tailoring_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
