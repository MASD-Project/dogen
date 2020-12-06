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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_TEXT_TRANSFORM_REPOSITORY_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_TEXT_TRANSFORM_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <string>
#include <algorithm>
#include <forward_list>
#include <unordered_map>
#include "dogen.text/types/transforms/model_to_text_transform_fwd.hpp"

namespace dogen::text::transforms {

class text_transform_repository final {
public:
    text_transform_repository() = default;
    text_transform_repository(const text_transform_repository&) = default;
    text_transform_repository(text_transform_repository&&) = default;
    ~text_transform_repository() = default;

public:
    explicit text_transform_repository(const std::unordered_map<std::string, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& model_to_text_transforms_by_meta_name);

public:
    const std::unordered_map<std::string, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& model_to_text_transforms_by_meta_name() const;
    std::unordered_map<std::string, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& model_to_text_transforms_by_meta_name();
    void model_to_text_transforms_by_meta_name(const std::unordered_map<std::string, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >& v);
    void model_to_text_transforms_by_meta_name(const std::unordered_map<std::string, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > >&& v);

public:
    bool operator==(const text_transform_repository& rhs) const;
    bool operator!=(const text_transform_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_transform_repository& other) noexcept;
    text_transform_repository& operator=(text_transform_repository other);

private:
    std::unordered_map<std::string, std::forward_list<std::shared_ptr<dogen::text::transforms::model_to_text_transform> > > model_to_text_transforms_by_meta_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::transforms::text_transform_repository& lhs,
    dogen::text::transforms::text_transform_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
