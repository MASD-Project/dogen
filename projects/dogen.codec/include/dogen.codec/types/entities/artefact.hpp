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
#ifndef DOGEN_CODEC_TYPES_ENTITIES_ARTEFACT_HPP
#define DOGEN_CODEC_TYPES_ENTITIES_ARTEFACT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen::codec::entities {

class artefact final {
public:
    artefact() = default;
    artefact(const artefact&) = default;
    ~artefact() = default;

public:
    artefact(artefact&& rhs);

public:
    artefact(
        const boost::filesystem::path& path,
        const std::string& codec_name,
        const std::string& content);

public:
    /**
     * @brief Path to the file representing this artefact, if any.
     */
    /**@{*/
    const boost::filesystem::path& path() const;
    boost::filesystem::path& path();
    void path(const boost::filesystem::path& v);
    void path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Name of the codec to process this artefact.
     */
    /**@{*/
    const std::string& codec_name() const;
    std::string& codec_name();
    void codec_name(const std::string& v);
    void codec_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Contents of the artefact.
     */
    /**@{*/
    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);
    /**@}*/

public:
    bool operator==(const artefact& rhs) const;
    bool operator!=(const artefact& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact& other) noexcept;
    artefact& operator=(artefact other);

private:
    boost::filesystem::path path_;
    std::string codec_name_;
    std::string content_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::entities::artefact& lhs,
    dogen::codec::entities::artefact& rhs) {
    lhs.swap(rhs);
}

}

#endif
