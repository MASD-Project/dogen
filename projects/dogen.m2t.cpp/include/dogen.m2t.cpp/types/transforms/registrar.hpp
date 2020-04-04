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
#ifndef DOGEN_M2T_CPP_TYPES_TRANSFORMS_REGISTRAR_HPP
#define DOGEN_M2T_CPP_TYPES_TRANSFORMS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.physical/types/entities/name_group.hpp"
#include "dogen.physical/types/entities/name_repository_parts.hpp"
#include "dogen.m2t.cpp/types/transforms/repository.hpp"
#include "dogen.m2t.cpp/types/transforms/helper_transform.hpp"
#include "dogen.m2t.cpp/types/transforms/model_to_text_transform.hpp"


namespace dogen::m2t::cpp::transforms {

/**
 * @brief Manages model-to-text transform registration.
 */
class registrar final {
private:
    /**
     * @brief Ensures the transform passes a modicum of sanity checks.
     */
    /**@{*/
    void validate(std::shared_ptr<model_to_text_transform> t) const;
    void validate(std::shared_ptr<helper_transform> ht) const;
    /**@{*/

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Registers a transform.
     */
    void register_transform(std::shared_ptr<model_to_text_transform> t);

    /**
     * @brief Registers a helper transform.
     */
    void register_helper_transform(std::shared_ptr<helper_transform> ht);

public:
    /**
     * @brief Returns all available transforms.
     */
    const repository& formatter_repository() const;

    /**
     * @brief Returns the physical names for the registered
     * transforms.
     */
    const std::forward_list<physical::entities::meta_name>&
    physical_names() const;

    /**
     * @brief Returns the physical names for each meta-type.
     */
    const std::unordered_map<std::string, physical::entities::name_group>&
    physical_names_by_meta_name() const;

    /**
     * @brief Returns the physical names for each family.
     */
    const std::unordered_map<std::string,
                             std::list<physical::entities::meta_name>>&
    physical_names_by_family() const;

    /**
     * @brief Returns the repository parts for the physical names.
     */
    const physical::entities::name_repository_parts&
    physical_name_repository_parts() const;

    /**
     * @brief Returns all of the available helper transforms.
     */
    const std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           std::list<
                               std::shared_ptr<helper_transform>>>>&
    helper_formatters() const;

private:
    repository transform_repository_;
    std::forward_list<physical::entities::meta_name> physical_names_;
    std::unordered_map<std::string, physical::entities::name_group>
    physical_names_by_meta_name_;
    std::unordered_map<std::string, std::list<physical::entities::meta_name>>
    physical_names_by_family_;
    physical::entities::name_repository_parts
    physical_name_repository_parts_;
};

template<typename Transform>
inline void register_formatter(registrar& rg) {
    const auto t(std::make_shared<Transform>());
    rg.register_transform(t);
}

template<typename Transform>
inline void register_formatter(registrar& rg, const std::string& facet_name) {
    const auto t(std::make_shared<Transform>(facet_name));
    rg.register_transform(t);
}

template<typename Formatter>
inline void register_helper_formatter(registrar& rg) {
    const auto f(std::make_shared<Formatter>());
    rg.register_helper_transform(f);
}

}

#endif
