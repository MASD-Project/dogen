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
#ifndef DOGEN_EXTERNAL_TYPES_META_MODEL_MODEL_HPP
#define DOGEN_EXTERNAL_TYPES_META_MODEL_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "dogen/external/types/meta_model/element.hpp"
#include "dogen/external/serialization/meta_model/model_fwd_ser.hpp"

namespace dogen {
namespace external {
namespace meta_model {

/**
 * @brief Represents an external model.
 */
class model final {
public:
    model() = default;
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model(
        const std::string& name,
        const std::string& documentation,
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const std::list<std::string>& stereotypes,
        const std::list<dogen::external::meta_model::element>& elements);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::external::meta_model::model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::external::meta_model::model& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

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

    const std::list<std::string>& stereotypes() const;
    std::list<std::string>& stereotypes();
    void stereotypes(const std::list<std::string>& v);
    void stereotypes(const std::list<std::string>&& v);

    const std::list<dogen::external::meta_model::element>& elements() const;
    std::list<dogen::external::meta_model::element>& elements();
    void elements(const std::list<dogen::external::meta_model::element>& v);
    void elements(const std::list<dogen::external::meta_model::element>&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    std::string name_;
    std::string documentation_;
    std::list<std::pair<std::string, std::string> > tagged_values_;
    std::list<std::string> stereotypes_;
    std::list<dogen::external::meta_model::element> elements_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::external::meta_model::model& lhs,
    dogen::external::meta_model::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
