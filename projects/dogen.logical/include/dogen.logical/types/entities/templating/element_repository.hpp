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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_TEMPLATING_ELEMENT_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_TEMPLATING_ELEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.logical/types/entities/templating/logic_less_template_fwd.hpp"

namespace dogen::logical::entities::templating {

class element_repository final {
public:
    element_repository() = default;
    element_repository(const element_repository&) = default;
    element_repository(element_repository&&) = default;
    ~element_repository() = default;

public:
    explicit element_repository(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::templating::logic_less_template> >& logic_less_templates);

public:
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::templating::logic_less_template> >& logic_less_templates() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::templating::logic_less_template> >& logic_less_templates();
    void logic_less_templates(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::templating::logic_less_template> >& v);
    void logic_less_templates(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::templating::logic_less_template> >&& v);

public:
    bool operator==(const element_repository& rhs) const;
    bool operator!=(const element_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_repository& other) noexcept;
    element_repository& operator=(element_repository other);

private:
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::templating::logic_less_template> > logic_less_templates_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::templating::element_repository& lhs,
    dogen::logical::entities::templating::element_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
