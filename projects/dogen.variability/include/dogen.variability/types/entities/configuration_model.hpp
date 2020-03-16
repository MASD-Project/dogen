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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_MODEL_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_CONFIGURATION_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.variability/types/entities/configuration_fwd.hpp"

namespace dogen::variability::entities {

class configuration_model final {
public:
    configuration_model() = default;
    configuration_model(const configuration_model&) = default;
    configuration_model(configuration_model&&) = default;
    ~configuration_model() = default;

public:
    configuration_model(
        const boost::shared_ptr<dogen::variability::entities::configuration>& global,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >& local);

public:
    const boost::shared_ptr<dogen::variability::entities::configuration>& global() const;
    boost::shared_ptr<dogen::variability::entities::configuration>& global();
    void global(const boost::shared_ptr<dogen::variability::entities::configuration>& v);
    void global(const boost::shared_ptr<dogen::variability::entities::configuration>&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >& local() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >& local();
    void local(const std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >& v);
    void local(const std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >&& v);

public:
    bool operator==(const configuration_model& rhs) const;
    bool operator!=(const configuration_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration_model& other) noexcept;
    configuration_model& operator=(configuration_model other);

private:
    boost::shared_ptr<dogen::variability::entities::configuration> global_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> > local_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::configuration_model& lhs,
    dogen::variability::entities::configuration_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
