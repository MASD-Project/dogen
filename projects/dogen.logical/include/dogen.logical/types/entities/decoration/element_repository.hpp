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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_DECORATION_ELEMENT_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_DECORATION_ELEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.logical/types/entities/decoration/licence_fwd.hpp"
#include "dogen.logical/types/entities/decoration/modeline_fwd.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group_fwd.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker_fwd.hpp"

namespace dogen::logical::entities::decoration {

class element_repository final {
public:
    element_repository() = default;
    element_repository(const element_repository&) = default;
    element_repository(element_repository&&) = default;
    ~element_repository() = default;

public:
    element_repository(
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& modeline_groups,
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modelines,
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& licences,
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& generation_markers);

public:
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& modeline_groups() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& modeline_groups();
    void modeline_groups(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >& v);
    void modeline_groups(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> >&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modelines() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modelines();
    void modelines(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& v);
    void modelines(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline> >&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& licences() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& licences();
    void licences(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& v);
    void licences(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::licence> >&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& generation_markers() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& generation_markers();
    void generation_markers(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& v);
    void generation_markers(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >&& v);

public:
    bool operator==(const element_repository& rhs) const;
    bool operator!=(const element_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_repository& other) noexcept;
    element_repository& operator=(element_repository other);

private:
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline_group> > modeline_groups_;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > modelines_;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::licence> > licences_;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> > generation_markers_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::decoration::element_repository& lhs,
    dogen::logical::entities::decoration::element_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
