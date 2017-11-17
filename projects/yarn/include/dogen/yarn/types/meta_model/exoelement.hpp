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
#ifndef DOGEN_YARN_TYPES_META_MODEL_EXOELEMENT_HPP
#define DOGEN_YARN_TYPES_META_MODEL_EXOELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "dogen/yarn/types/meta_model/exoattribute.hpp"
#include "dogen/yarn/types/meta_model/well_known_stereotypes.hpp"
#include "dogen/yarn/serialization/meta_model/exoelement_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

class exoelement final {
public:
    exoelement() = default;
    exoelement(const exoelement&) = default;
    exoelement(exoelement&&) = default;
    ~exoelement() = default;

public:
    exoelement(
        const std::string& documentation,
        const std::list<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes,
        const std::list<std::string>& unknown_stereotypes,
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const std::string& name,
        const std::list<std::string>& parents,
        const std::list<dogen::yarn::meta_model::exoattribute>& attributes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::exoelement& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::exoelement& v, unsigned int version);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are part of the yarn UML profile, and so are well-known to the
     * model.
     */
    /**@{*/
    const std::list<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes() const;
    std::list<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes();
    void well_known_stereotypes(const std::list<dogen::yarn::meta_model::well_known_stereotypes>& v);
    void well_known_stereotypes(const std::list<dogen::yarn::meta_model::well_known_stereotypes>&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are not part of the yarn UML profile.
     */
    /**@{*/
    const std::list<std::string>& unknown_stereotypes() const;
    std::list<std::string>& unknown_stereotypes();
    void unknown_stereotypes(const std::list<std::string>& v);
    void unknown_stereotypes(const std::list<std::string>&& v);
    /**@}*/

    const std::list<std::pair<std::string, std::string> >& tagged_values() const;
    std::list<std::pair<std::string, std::string> >& tagged_values();
    void tagged_values(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values(const std::list<std::pair<std::string, std::string> >&& v);

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

    const std::list<dogen::yarn::meta_model::exoattribute>& attributes() const;
    std::list<dogen::yarn::meta_model::exoattribute>& attributes();
    void attributes(const std::list<dogen::yarn::meta_model::exoattribute>& v);
    void attributes(const std::list<dogen::yarn::meta_model::exoattribute>&& v);

public:
    bool operator==(const exoelement& rhs) const;
    bool operator!=(const exoelement& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(exoelement& other) noexcept;
    exoelement& operator=(exoelement other);

private:
    std::string documentation_;
    std::list<dogen::yarn::meta_model::well_known_stereotypes> well_known_stereotypes_;
    std::list<std::string> unknown_stereotypes_;
    std::list<std::pair<std::string, std::string> > tagged_values_;
    std::string name_;
    std::list<std::string> parents_;
    std::list<dogen::yarn::meta_model::exoattribute> attributes_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::exoelement& lhs,
    dogen::yarn::meta_model::exoelement& rhs) {
    lhs.swap(rhs);
}

}

#endif
