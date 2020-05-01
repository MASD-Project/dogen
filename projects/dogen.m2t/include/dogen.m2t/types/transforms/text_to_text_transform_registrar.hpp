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
#ifndef DOGEN_M2T_TYPES_TRANSFORMS_TEXT_TO_TEXT_TRANSFORM_REGISTRAR_HPP
#define DOGEN_M2T_TYPES_TRANSFORMS_TEXT_TO_TEXT_TRANSFORM_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <string>
#include <algorithm>
#include <unordered_map>

namespace dogen::m2t::transforms {

class text_to_text_transform_registrar final {
public:
    text_to_text_transform_registrar() = default;
    text_to_text_transform_registrar(const text_to_text_transform_registrar&) = default;
    text_to_text_transform_registrar(text_to_text_transform_registrar&&) = default;
    ~text_to_text_transform_registrar() = default;

public:
    explicit text_to_text_transform_registrar(const std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >& transforms_for_logical_element_);

public:
    const std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >& transforms_for_logical_element_() const;
    std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >& transforms_for_logical_element_();
    void transforms_for_logical_element_(const std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >& v);
    void transforms_for_logical_element_(const std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> >&& v);

public:
    bool operator==(const text_to_text_transform_registrar& rhs) const;
    bool operator!=(const text_to_text_transform_registrar& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_to_text_transform_registrar& other) noexcept;
    text_to_text_transform_registrar& operator=(text_to_text_transform_registrar other);

private:
    std::unordered_map<std::string, std::shared_ptr<dogen::m2t::transforms::text_to_text_transform> > transforms_for_logical_element__;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::transforms::text_to_text_transform_registrar& lhs,
    dogen::m2t::transforms::text_to_text_transform_registrar& rhs) {
    lhs.swap(rhs);
}

}

#endif
