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
#ifndef DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_REGISTRAR_HPP
#define DOGEN_TEXT_CSHARP_TYPES_TRANSFORMS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.physical/types/entities/meta_name_group.hpp"
#include "dogen.text.csharp/types/transforms/repository.hpp"
#include "dogen.text.csharp/types/transforms/helper_transform.hpp"
#include "dogen.text.csharp/types/transforms/model_to_text_transform.hpp"

namespace dogen::text::csharp::transforms {

/**
 * @brief Manages model-to-text transform registration.
 */
class registrar final {
public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Registers a transform.
     */
    void register_transform(std::shared_ptr<model_to_text_transform> f);

    /**
     * @brief Registers a helper transform.
     */
    void register_helper_transform(std::shared_ptr<helper_transform> fh);

public:
    /**
     * @brief Returns all available transforms.
     */
    const repository& formatter_repository() const;

public:
    /**
     * @brief Returns the physical meta-names for each logical
     * meta-type.
     */
    const std::unordered_map<std::string, physical::entities::meta_name_group>&
    physical_meta_names_by_logical_meta_name() const;

private:
    repository transform_repository_;
    std::unordered_map<std::string,
                       physical::entities::meta_name_group>
    physical_meta_names_by_logical_meta_name_;
};

template<typename Transform>
inline void register_formatter(registrar& rg) {
    const auto t(std::make_shared<Transform>());
    rg.register_transform(t);
}

template<typename Transform>
inline void register_formatter_helper(registrar& rg) {
    const auto t(std::make_shared<Transform>());
    rg.register_helper_transform(t);
}

}

#endif
