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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_DECORATION_MODELINE_GROUP_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_DECORATION_MODELINE_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.logical/types/entities/decoration/modeline_fwd.hpp"

namespace dogen::logical::entities::decoration {

/**
 * @brief Group of modelines, logically associated.
 *
 * For example, one may choose to have a set of modelines for @e emacs , or for
 * @e vi, etc.
 */
class modeline_group final : public dogen::logical::entities::element {
public:
    modeline_group() = default;
    modeline_group(const modeline_group&) = default;
    modeline_group(modeline_group&&) = default;

    virtual ~modeline_group() noexcept { }

public:
    modeline_group(
        const dogen::identification::entities::logical_name& name,
        const std::string& documentation,
        const dogen::identification::entities::codec_provenance& provenance,
        const dogen::identification::entities::logical_id& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<dogen::identification::entities::logical_id>& contains,
        const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modelines);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief All elements contained by this element.
     */
    /**@{*/
    const std::list<dogen::identification::entities::logical_id>& contains() const;
    std::list<dogen::identification::entities::logical_id>& contains();
    void contains(const std::list<dogen::identification::entities::logical_id>& v);
    void contains(const std::list<dogen::identification::entities::logical_id>&& v);
    /**@}*/

    /**
     * @brief Modelines that make up the group.
     */
    /**@{*/
    const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modelines() const;
    std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& modelines();
    void modelines(const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >& v);
    void modelines(const std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> >&& v);
    /**@}*/

public:
    bool operator==(const modeline_group& rhs) const;
    bool operator!=(const modeline_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(modeline_group& other) noexcept;
    modeline_group& operator=(modeline_group other);

private:
    std::list<dogen::identification::entities::logical_id> contains_;
    std::list<boost::shared_ptr<dogen::logical::entities::decoration::modeline> > modelines_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::decoration::modeline_group& lhs,
    dogen::logical::entities::decoration::modeline_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
