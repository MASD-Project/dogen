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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_REGISTRAR_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/formattables/provider_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/container.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class registrar {
public:
    const formattables::container& container() const;

public:
    void register_provider(
        boost::shared_ptr<provider_interface<yarn::object>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<yarn::enumeration>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<yarn::exception>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<yarn::visitor>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<yarn::module>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<yarn::primitive>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<fabric::registrar>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<fabric::master_header>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<fabric::forward_declarations>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<fabric::cmakelists>> p);

    void register_provider(
        boost::shared_ptr<provider_interface<fabric::odb_options>> p);

private:
    formattables::container container_;
};

/*
 * Helper method to register providers.
 */
template<typename T>
inline void register_provider(registrar& rg, const T& t) {
    t.register_provider(rg);
}

} } } }

#endif
