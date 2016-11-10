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
#ifndef DOGEN_YARN_TYPES_DESCRIPTOR_HPP
#define DOGEN_YARN_TYPES_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/yarn/serialization/descriptor_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Describes the location of a model input.
 */
class descriptor final {
public:
    descriptor(const descriptor&) = default;
    ~descriptor() = default;

public:
    descriptor();

public:
    descriptor(descriptor&& rhs);

public:
    descriptor(
        const boost::filesystem::path& path,
        const std::string& extension,
        const bool is_target);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::descriptor& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::descriptor& v, unsigned int version);

public:
    /**
     * @brief Location of the input.
     */
    /**@{*/
    const boost::filesystem::path& path() const;
    boost::filesystem::path& path();
    void path(const boost::filesystem::path& v);
    void path(const boost::filesystem::path&& v);
    /**@}*/

    const std::string& extension() const;
    std::string& extension();
    void extension(const std::string& v);
    void extension(const std::string&& v);

    /**
     * @brief If true, the input contains the intermediate target model.
     */
    /**@{*/
    bool is_target() const;
    void is_target(const bool v);
    /**@}*/

public:
    bool operator==(const descriptor& rhs) const;
    bool operator!=(const descriptor& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(descriptor& other) noexcept;
    descriptor& operator=(descriptor other);

private:
    boost::filesystem::path path_;
    std::string extension_;
    bool is_target_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::descriptor& lhs,
    dogen::yarn::descriptor& rhs) {
    lhs.swap(rhs);
}

}

#endif
