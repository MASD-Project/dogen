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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_MAPPER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_MAPPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/name_tree.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/helpers/mapping_context.hpp"
#include "dogen.logical/types/helpers/mapping_set_repository.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Responsible for mapping types from a technical space to
 * another. Requires those mappings to exist.
 */
class mapper final {
public:
    explicit mapper(const mapping_set_repository& msrp);

private:
    template<typename Element>
    std::unordered_map<std::string, boost::shared_ptr<Element>>
    clone(const std::unordered_map<std::string,
        boost::shared_ptr<Element>>& src) const {
        std::unordered_map<std::string, boost::shared_ptr<Element>> r;
        for (const auto& pair : src)
            r[pair.first] = boost::make_shared<Element>(*pair.second);
        return r;
    }

    entities::model
    clone(const entities::model& m) const;

private:
    const std::unordered_map<std::string, entities::name>&
    translations_for_technical_space(const mapping_set& ms,
        const identification::entities::technical_space from,
        const identification::entities::technical_space to) const;

    std::unordered_map<std::string, entities::name>
    injections_for_technical_space(const mapping_set& ms,
        const identification::entities::technical_space ts,
        const entities::model& m) const;

    mapping_context create_mapping_context(const mapping_set& ms,
        const identification::entities::technical_space from,
        const identification::entities::technical_space to,
        const entities::model& m) const;

private:
    entities::name_tree walk_name_tree(const mapping_context& mc,
        const entities::name_tree& nt,
        const bool skip_injection = false) const;
    void map_attributes(const mapping_context& mc,
        std::list<entities::attribute>& attrs) const;

public:
    static bool is_mappable(
        const identification::entities::technical_space from,
        const identification::entities::technical_space to);
    entities::model map(
        const identification::entities::technical_space from,
        const identification::entities::technical_space to,
        const entities::model& m) const;

private:
    const mapping_set_repository& mapping_set_repository_;
};

}

#endif
