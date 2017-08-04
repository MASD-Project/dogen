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
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/module_fwd.hpp"
#include "dogen/yarn.dia/serialization/context_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Collects all the information required by the builder and the transformer.
 */
class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context(
        const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& dia_id_to_module,
        const std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >& child_dia_id_to_parent_names);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::dia::context& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::dia::context& v, unsigned int version);

public:
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& dia_id_to_module() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& dia_id_to_module();
    void dia_id_to_module(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& v);
    void dia_id_to_module(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >&& v);

    const std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >& child_dia_id_to_parent_names() const;
    std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >& child_dia_id_to_parent_names();
    void child_dia_id_to_parent_names(const std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >& v);
    void child_dia_id_to_parent_names(const std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >&& v);

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> > dia_id_to_module_;
    std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> > child_dia_id_to_parent_names_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::dia::context& lhs,
    dogen::yarn::dia::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
