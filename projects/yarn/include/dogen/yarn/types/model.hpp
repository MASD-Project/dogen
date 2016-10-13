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
#ifndef DOGEN_YARN_TYPES_MODEL_HPP
#define DOGEN_YARN_TYPES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/element_fwd.hpp"
#include "dogen/yarn/serialization/model_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Yarn model.
 */
class model final {
public:
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model();

public:
    model(
        const dogen::yarn::name& name,
        const std::vector<boost::shared_ptr<dogen::yarn::element> >& elements,
        const dogen::yarn::module& root_module,
        const bool has_generatable_types);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::model& v, unsigned int version);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::yarn::name& name() const;
    dogen::yarn::name& name();
    void name(const dogen::yarn::name& v);
    void name(const dogen::yarn::name&& v);
    /**@}*/

    const std::vector<boost::shared_ptr<dogen::yarn::element> >& elements() const;
    std::vector<boost::shared_ptr<dogen::yarn::element> >& elements();
    void elements(const std::vector<boost::shared_ptr<dogen::yarn::element> >& v);
    void elements(const std::vector<boost::shared_ptr<dogen::yarn::element> >&& v);

    /**
     * @brief The module that represents the model.
     */
    /**@{*/
    const dogen::yarn::module& root_module() const;
    dogen::yarn::module& root_module();
    void root_module(const dogen::yarn::module& v);
    void root_module(const dogen::yarn::module&& v);
    /**@}*/

    /**
     * @brief If true the intermediate model has at least one generable type, false otherwise.
     */
    /**@{*/
    bool has_generatable_types() const;
    void has_generatable_types(const bool v);
    /**@}*/

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::yarn::name name_;
    std::vector<boost::shared_ptr<dogen::yarn::element> > elements_;
    dogen::yarn::module root_module_;
    bool has_generatable_types_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::model& lhs,
    dogen::yarn::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
