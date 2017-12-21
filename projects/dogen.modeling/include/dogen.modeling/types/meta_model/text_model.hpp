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
#ifndef DOGEN_MODELING_TYPES_META_MODEL_TEXT_MODEL_HPP
#define DOGEN_MODELING_TYPES_META_MODEL_TEXT_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen.modeling/types/meta_model/artefact.hpp"
#include "dogen.modeling/serialization/meta_model/text_model_fwd_ser.hpp"

namespace dogen {
namespace modeling {
namespace meta_model {

class text_model final {
public:
    text_model() = default;
    text_model(const text_model&) = default;
    text_model(text_model&&) = default;
    ~text_model() = default;

public:
    text_model(
        const std::list<dogen::modeling::meta_model::artefact>& artefacts,
        const std::list<boost::filesystem::path>& managed_directories);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::modeling::meta_model::text_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::modeling::meta_model::text_model& v, unsigned int version);

public:
    const std::list<dogen::modeling::meta_model::artefact>& artefacts() const;
    std::list<dogen::modeling::meta_model::artefact>& artefacts();
    void artefacts(const std::list<dogen::modeling::meta_model::artefact>& v);
    void artefacts(const std::list<dogen::modeling::meta_model::artefact>&& v);

    const std::list<boost::filesystem::path>& managed_directories() const;
    std::list<boost::filesystem::path>& managed_directories();
    void managed_directories(const std::list<boost::filesystem::path>& v);
    void managed_directories(const std::list<boost::filesystem::path>&& v);

public:
    bool operator==(const text_model& rhs) const;
    bool operator!=(const text_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_model& other) noexcept;
    text_model& operator=(text_model other);

private:
    std::list<dogen::modeling::meta_model::artefact> artefacts_;
    std::list<boost::filesystem::path> managed_directories_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::modeling::meta_model::text_model& lhs,
    dogen::modeling::meta_model::text_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
