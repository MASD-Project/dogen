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
#ifndef DOGEN_YARN_DIA_TYPES_CONTEXT_HPP
#define DOGEN_YARN_DIA_TYPES_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn_dia/serialization/context_fwd_ser.hpp"

namespace dogen {
namespace yarn_dia {

/**
 * @brief Collects all the information required by the visitor as it traverses the graph.
 */
class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context(
        const std::unordered_map<std::string, std::list<std::string> >& child_id_to_parent_ids,
        const std::unordered_set<std::string>& parent_ids,
        const std::unordered_map<std::string, dogen::yarn::name>& id_to_name,
        const std::unordered_set<std::string>& top_level_module_names,
        const dogen::yarn::model& model);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const context& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, context& v, unsigned int version);

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
     * @brief All dia object IDs of classes that are parents in a generalisation.
     */
    /**@{*/
    const std::unordered_set<std::string>& parent_ids() const;
    std::unordered_set<std::string>& parent_ids();
    void parent_ids(const std::unordered_set<std::string>& v);
    void parent_ids(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief The name corresponding to a dia object ID.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::name>& id_to_name() const;
    std::unordered_map<std::string, dogen::yarn::name>& id_to_name();
    void id_to_name(const std::unordered_map<std::string, dogen::yarn::name>& v);
    void id_to_name(const std::unordered_map<std::string, dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief All modules that sit just below the model.
     */
    /**@{*/
    const std::unordered_set<std::string>& top_level_module_names() const;
    std::unordered_set<std::string>& top_level_module_names();
    void top_level_module_names(const std::unordered_set<std::string>& v);
    void top_level_module_names(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief Yarn model we are currently building.
     */
    /**@{*/
    const dogen::yarn::model& model() const;
    dogen::yarn::model& model();
    void model(const dogen::yarn::model& v);
    void model(const dogen::yarn::model&& v);
    /**@}*/

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    std::unordered_map<std::string, std::list<std::string> > child_id_to_parent_ids_;
    std::unordered_set<std::string> parent_ids_;
    std::unordered_map<std::string, dogen::yarn::name> id_to_name_;
    std::unordered_set<std::string> top_level_module_names_;
    dogen::yarn::model model_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn_dia::context& lhs,
    dogen::yarn_dia::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
