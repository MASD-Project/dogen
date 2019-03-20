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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_GLOBAL_DECORATION_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_GLOBAL_DECORATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>

namespace masd::dogen::coding::meta_model {

/**
 * @brief Configuration pertaining to file decoration, applicable to all model elements which
 * do not provide an override.
 */
class global_decoration final {
public:
    global_decoration() = default;
    global_decoration(const global_decoration&) = default;
    global_decoration(global_decoration&&) = default;
    ~global_decoration() = default;

public:
    global_decoration(
        const std::list<std::string>& copyrights,
        const std::string& licence_short_form,
        const std::string& licence_long_form,
        const std::string& generation_marker);

public:
    /**
     * @brief All copyright notices for the current element.
     */
    /**@{*/
    const std::list<std::string>& copyrights() const;
    std::list<std::string>& copyrights();
    void copyrights(const std::list<std::string>& v);
    void copyrights(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Licence to use by default for files in this model, if any.
     */
    /**@{*/
    const std::string& licence_short_form() const;
    std::string& licence_short_form();
    void licence_short_form(const std::string& v);
    void licence_short_form(const std::string&& v);
    /**@}*/

    /**
     * @brief Licence to use in this model, if any.
     */
    /**@{*/
    const std::string& licence_long_form() const;
    std::string& licence_long_form();
    void licence_long_form(const std::string& v);
    void licence_long_form(const std::string&& v);
    /**@}*/

    /**
     * @brief Code generation marker to use for this model, if any.
     */
    /**@{*/
    const std::string& generation_marker() const;
    std::string& generation_marker();
    void generation_marker(const std::string& v);
    void generation_marker(const std::string&& v);
    /**@}*/

public:
    bool operator==(const global_decoration& rhs) const;
    bool operator!=(const global_decoration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(global_decoration& other) noexcept;
    global_decoration& operator=(global_decoration other);

private:
    std::list<std::string> copyrights_;
    std::string licence_short_form_;
    std::string licence_long_form_;
    std::string generation_marker_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::global_decoration& lhs,
    masd::dogen::coding::meta_model::global_decoration& rhs) {
    lhs.swap(rhs);
}

}

#endif
