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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_CONFIGURATION_ENTRY_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_CONFIGURATION_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "masd.dogen.annotations/types/annotation.hpp"

namespace masd::dogen::coding::meta_model {

class configuration_entry final {
public:
    configuration_entry() = default;
    configuration_entry(const configuration_entry&) = default;
    configuration_entry(configuration_entry&&) = default;
    ~configuration_entry() = default;

public:
    configuration_entry(
        const masd::dogen::annotations::annotation& annotation,
        const std::string& name,
        const std::list<std::string>& value);

public:
    /**
     * @brief Annotation for this element.
     */
    /**@{*/
    const masd::dogen::annotations::annotation& annotation() const;
    masd::dogen::annotations::annotation& annotation();
    void annotation(const masd::dogen::annotations::annotation& v);
    void annotation(const masd::dogen::annotations::annotation&& v);
    /**@}*/

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::list<std::string>& value() const;
    std::list<std::string>& value();
    void value(const std::list<std::string>& v);
    void value(const std::list<std::string>&& v);

public:
    bool operator==(const configuration_entry& rhs) const;
    bool operator!=(const configuration_entry& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration_entry& other) noexcept;
    configuration_entry& operator=(configuration_entry other);

private:
    masd::dogen::annotations::annotation annotation_;
    std::string name_;
    std::list<std::string> value_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::configuration_entry& lhs,
    masd::dogen::coding::meta_model::configuration_entry& rhs) {
    lhs.swap(rhs);
}

}

#endif
