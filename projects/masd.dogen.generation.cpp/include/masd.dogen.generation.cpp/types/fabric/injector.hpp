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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_INJECTOR_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_INJECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.modeling/types/meta_model/element.hpp"
#include "masd.dogen.modeling/types/meta_model/model.hpp"

namespace masd::dogen::generation::cpp::fabric {

class injector {
public:
    virtual ~injector() noexcept;

private:
    void add_element(const boost::shared_ptr<modeling::meta_model::element>& e,
        modeling::meta_model::model& m) const;

    void add_elements(
        const std::list<boost::shared_ptr<modeling::meta_model::element>>& elements,
        modeling::meta_model::model& m) const;

private:
    void inject_registrar(modeling::meta_model::model& m) const;
    void inject_build_files(modeling::meta_model::model& m) const;
    void inject_odb_options(modeling::meta_model::model& m) const;
    void inject_master_headers(modeling::meta_model::model& m) const;
    void inject_visual_studio(const annotations::type_repository& atrp,
        modeling::meta_model::model& m) const;
    void inject_forward_declarations(
        modeling::meta_model::model& m) const;

public:
    void inject(const annotations::type_repository& atrp,
        modeling::meta_model::model& m) const;
};

}

#endif
