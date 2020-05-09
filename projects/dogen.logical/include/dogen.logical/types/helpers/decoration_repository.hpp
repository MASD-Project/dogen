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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_DECORATION_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_DECORATION_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.logical/hash/entities/technical_space_hash.hpp"
#include "dogen.logical/types/entities/decoration/licence_fwd.hpp"
#include "dogen.logical/types/entities/decoration/modeline_fwd.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker_fwd.hpp"

namespace dogen::logical::helpers {

class decoration_repository final {
public:
    decoration_repository() = default;
    decoration_repository(const decoration_repository&) = default;
    decoration_repository(decoration_repository&&) = default;
    ~decoration_repository() = default;

public:
    decoration_repository(
        const std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >& modelines_by_modeline_group_by_technical_space,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& licences_by_name,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& generation_markers_by_name);

public:
    const std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >& modelines_by_modeline_group_by_technical_space() const;
    std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >& modelines_by_modeline_group_by_technical_space();
    void modelines_by_modeline_group_by_technical_space(const std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >& v);
    void modelines_by_modeline_group_by_technical_space(const std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& licences_by_name() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& licences_by_name();
    void licences_by_name(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >& v);
    void licences_by_name(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& generation_markers_by_name() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& generation_markers_by_name();
    void generation_markers_by_name(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >& v);
    void generation_markers_by_name(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> >&& v);

public:
    bool operator==(const decoration_repository& rhs) const;
    bool operator!=(const decoration_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decoration_repository& other) noexcept;
    decoration_repository& operator=(decoration_repository other);

private:
    std::unordered_map<std::string, std::unordered_map<dogen::logical::entities::technical_space, boost::shared_ptr<dogen::logical::entities::decoration::modeline> > > modelines_by_modeline_group_by_technical_space_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::licence> > licences_by_name_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::entities::decoration::generation_marker> > generation_markers_by_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::helpers::decoration_repository& lhs,
    dogen::logical::helpers::decoration_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
