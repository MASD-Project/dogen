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
#ifndef DOGEN_YARN_DIA_TYPES_REPOSITORY_HPP
#define DOGEN_YARN_DIA_TYPES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/yarn.dia/serialization/repository_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Collects all the information required by the builder.
 */
class repository final {
public:
    repository() = default;
    repository(const repository&) = default;
    repository(repository&&) = default;
    ~repository() = default;

public:
    repository(
        const std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids,
        const std::unordered_map<std::string, dogen::yarn::meta_model::name>& id_to_name,
        const dogen::yarn::meta_model::intermediate_model& model);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::dia::repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::dia::repository& v, unsigned int version);

public:
    /**
     * @brief List of parent object IDs for a given child ID.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids() const;
    std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids();
    void child_id_to_parent_ids(const std::unordered_map<std::string, std::list<std::string> >& v);
    void child_id_to_parent_ids(const std::unordered_map<std::string, std::list<std::string> >&& v);
    /**@}*/

    /**
     * @brief The name corresponding to a dia object ID.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::meta_model::name>& id_to_name() const;
    std::unordered_map<std::string, dogen::yarn::meta_model::name>& id_to_name();
    void id_to_name(const std::unordered_map<std::string, dogen::yarn::meta_model::name>& v);
    void id_to_name(const std::unordered_map<std::string, dogen::yarn::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Intermediate yarn model we are currently building.
     */
    /**@{*/
    const dogen::yarn::meta_model::intermediate_model& model() const;
    dogen::yarn::meta_model::intermediate_model& model();
    void model(const dogen::yarn::meta_model::intermediate_model& v);
    void model(const dogen::yarn::meta_model::intermediate_model&& v);
    /**@}*/

public:
    bool operator==(const repository& rhs) const;
    bool operator!=(const repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(repository& other) noexcept;
    repository& operator=(repository other);

private:
    std::unordered_map<std::string, std::list<std::string> > child_id_to_parent_ids_;
    std::unordered_map<std::string, dogen::yarn::meta_model::name> id_to_name_;
    dogen::yarn::meta_model::intermediate_model model_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::dia::repository& lhs,
    dogen::yarn::dia::repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
