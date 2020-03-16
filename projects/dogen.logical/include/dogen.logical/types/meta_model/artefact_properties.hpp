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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_ARTEFACT_PROPERTIES_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_ARTEFACT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen.logical/types/meta_model/formatting_styles.hpp"

namespace dogen::logical::meta_model {

class artefact_properties final {
public:
    artefact_properties(const artefact_properties&) = default;
    ~artefact_properties() = default;

public:
    artefact_properties();

public:
    artefact_properties(artefact_properties&& rhs);

public:
    artefact_properties(
        const bool enabled,
        const bool overwrite,
        const boost::filesystem::path& file_path,
        const dogen::logical::meta_model::formatting_styles formatting_style,
        const std::string& formatting_input);

public:
    bool enabled() const;
    void enabled(const bool v);

    bool overwrite() const;
    void overwrite(const bool v);

    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

    dogen::logical::meta_model::formatting_styles formatting_style() const;
    void formatting_style(const dogen::logical::meta_model::formatting_styles v);

    const std::string& formatting_input() const;
    std::string& formatting_input();
    void formatting_input(const std::string& v);
    void formatting_input(const std::string&& v);

public:
    bool operator==(const artefact_properties& rhs) const;
    bool operator!=(const artefact_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact_properties& other) noexcept;
    artefact_properties& operator=(artefact_properties other);

private:
    bool enabled_;
    bool overwrite_;
    boost::filesystem::path file_path_;
    dogen::logical::meta_model::formatting_styles formatting_style_;
    std::string formatting_input_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::artefact_properties& lhs,
    dogen::logical::meta_model::artefact_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
