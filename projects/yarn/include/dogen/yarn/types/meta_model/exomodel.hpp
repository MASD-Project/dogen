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
#ifndef DOGEN_YARN_TYPES_META_MODEL_EXOMODEL_HPP
#define DOGEN_YARN_TYPES_META_MODEL_EXOMODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "dogen/yarn/types/meta_model/exoelement.hpp"
#include "dogen/yarn/serialization/meta_model/exomodel_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

class exomodel final {
public:
    exomodel() = default;
    exomodel(const exomodel&) = default;
    exomodel(exomodel&&) = default;
    ~exomodel() = default;

public:
    exomodel(
        const std::string& documentation,
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const std::string& id,
        const std::list<dogen::yarn::meta_model::exoelement>& elements,
        const std::list<std::string>& stereotypes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::exomodel& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::exomodel& v, unsigned int version);

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

    const std::list<std::pair<std::string, std::string> >& tagged_values() const;
    std::list<std::pair<std::string, std::string> >& tagged_values();
    void tagged_values(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values(const std::list<std::pair<std::string, std::string> >&& v);

    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);

    const std::list<dogen::yarn::meta_model::exoelement>& elements() const;
    std::list<dogen::yarn::meta_model::exoelement>& elements();
    void elements(const std::list<dogen::yarn::meta_model::exoelement>& v);
    void elements(const std::list<dogen::yarn::meta_model::exoelement>&& v);

    const std::list<std::string>& stereotypes() const;
    std::list<std::string>& stereotypes();
    void stereotypes(const std::list<std::string>& v);
    void stereotypes(const std::list<std::string>&& v);

public:
    bool operator==(const exomodel& rhs) const;
    bool operator!=(const exomodel& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(exomodel& other) noexcept;
    exomodel& operator=(exomodel other);

private:
    std::string documentation_;
    std::list<std::pair<std::string, std::string> > tagged_values_;
    std::string id_;
    std::list<dogen::yarn::meta_model::exoelement> elements_;
    std::list<std::string> stereotypes_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::exomodel& lhs,
    dogen::yarn::meta_model::exomodel& rhs) {
    lhs.swap(rhs);
}

}

#endif
