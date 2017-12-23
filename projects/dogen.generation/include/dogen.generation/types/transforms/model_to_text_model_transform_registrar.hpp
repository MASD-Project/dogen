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
#ifndef DOGEN_GENERATION_TYPES_TRANSFORMS_MODEL_TO_TEXT_MODEL_TRANSFORM_REGISTRAR_HPP
#define DOGEN_GENERATION_TYPES_TRANSFORMS_MODEL_TO_TEXT_MODEL_TRANSFORM_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <algorithm>
#include <unordered_map>
#include "dogen.modeling/types/meta_model/languages.hpp"
#include "dogen.modeling/hash/meta_model/languages_hash.hpp"
#include "dogen.generation/types/transforms/model_to_text_model_transform_interface_fwd.hpp"

namespace dogen {
namespace generation {
namespace transforms {

class model_to_text_model_transform_registrar final {
public:
    model_to_text_model_transform_registrar() = default;
    model_to_text_model_transform_registrar(const model_to_text_model_transform_registrar&) = default;
    model_to_text_model_transform_registrar(model_to_text_model_transform_registrar&&) = default;
    ~model_to_text_model_transform_registrar() = default;

public:
    explicit model_to_text_model_transform_registrar(const std::unordered_map<dogen::modeling::meta_model::languages, std::shared_ptr<dogen::generation::transforms::model_to_text_model_transform_interface> >& transforms_by_language_);

public:
    const std::unordered_map<dogen::modeling::meta_model::languages, std::shared_ptr<dogen::generation::transforms::model_to_text_model_transform_interface> >& transforms_by_language_() const;
    std::unordered_map<dogen::modeling::meta_model::languages, std::shared_ptr<dogen::generation::transforms::model_to_text_model_transform_interface> >& transforms_by_language_();
    void transforms_by_language_(const std::unordered_map<dogen::modeling::meta_model::languages, std::shared_ptr<dogen::generation::transforms::model_to_text_model_transform_interface> >& v);
    void transforms_by_language_(const std::unordered_map<dogen::modeling::meta_model::languages, std::shared_ptr<dogen::generation::transforms::model_to_text_model_transform_interface> >&& v);

public:
    bool operator==(const model_to_text_model_transform_registrar& rhs) const;
    bool operator!=(const model_to_text_model_transform_registrar& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model_to_text_model_transform_registrar& other) noexcept;
    model_to_text_model_transform_registrar& operator=(model_to_text_model_transform_registrar other);

private:
    std::unordered_map<dogen::modeling::meta_model::languages, std::shared_ptr<dogen::generation::transforms::model_to_text_model_transform_interface> > transforms_by_language__;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::generation::transforms::model_to_text_model_transform_registrar& lhs,
    dogen::generation::transforms::model_to_text_model_transform_registrar& rhs) {
    lhs.swap(rhs);
}

}

#endif
