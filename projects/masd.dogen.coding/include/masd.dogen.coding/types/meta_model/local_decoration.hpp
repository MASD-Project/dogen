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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_LOCAL_DECORATION_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_LOCAL_DECORATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>

namespace masd::dogen::coding::meta_model {

/**
 * @brief Configuration pertaining to file decoration at the elment level.
 */
class local_decoration final {
public:
    local_decoration() = default;
    local_decoration(const local_decoration&) = default;
    local_decoration(local_decoration&&) = default;
    ~local_decoration() = default;

public:
    local_decoration(
        const std::string& top_modeline,
        const std::string& bottom_modeline,
        const std::list<std::string>& copyrights,
        const std::string& licence_short_form,
        const std::string& generation_marker);

public:
    /**
     * @brief Modeline to use in this file, if any.
     */
    /**@{*/
    const std::string& top_modeline() const;
    std::string& top_modeline();
    void top_modeline(const std::string& v);
    void top_modeline(const std::string&& v);
    /**@}*/

    const std::string& bottom_modeline() const;
    std::string& bottom_modeline();
    void bottom_modeline(const std::string& v);
    void bottom_modeline(const std::string&& v);

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
     * @brief Licence to use in this file, if any.
     */
    /**@{*/
    const std::string& licence_short_form() const;
    std::string& licence_short_form();
    void licence_short_form(const std::string& v);
    void licence_short_form(const std::string&& v);
    /**@}*/

    /**
     * @brief Code generation marker to use for this element, if any.
     */
    /**@{*/
    const std::string& generation_marker() const;
    std::string& generation_marker();
    void generation_marker(const std::string& v);
    void generation_marker(const std::string&& v);
    /**@}*/

public:
    bool operator==(const local_decoration& rhs) const;
    bool operator!=(const local_decoration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(local_decoration& other) noexcept;
    local_decoration& operator=(local_decoration other);

private:
    std::string top_modeline_;
    std::string bottom_modeline_;
    std::list<std::string> copyrights_;
    std::string licence_short_form_;
    std::string generation_marker_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::local_decoration& lhs,
    masd::dogen::coding::meta_model::local_decoration& rhs) {
    lhs.swap(rhs);
}

}

#endif
