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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_CONTAINER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <forward_list>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_provider_interface.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class container {
public:
    const std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::object>
            >
        >&
    object_providers() const;

    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::object>
            >
        >&
    object_providers();

    const std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::enumeration>
            >
        >&
    enumeration_providers() const;

    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::enumeration>
            >
        >&
    enumeration_providers();

    const std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::exception>
            >
        >&
    exception_providers() const;

    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::exception>
            >
        >&
    exception_providers();

    const std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::visitor>
            >
        >&
    visitor_providers() const;

    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::visitor>
            >
        >&
    visitor_providers();

    const std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::model>
            >
        >&
    model_providers() const;

    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::model>
            >
        >&
    model_providers();

private:
    std::forward_list<
    boost::shared_ptr<
        inclusion_dependencies_provider_interface<yarn::object>
        >
    > object_providers_;
    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::enumeration>
            >
    > enumeration_providers_;
    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::exception>
            >
    > exception_providers_;
    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::visitor>
            >
    > visitor_providers_;
    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<yarn::model>
            >
    > model_providers_;
};

} } } }

#endif
