/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_TYPES_BOOST_MODEL_FACTORY_HPP
#define DOGEN_SML_TYPES_BOOST_MODEL_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/value.hpp"
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

class boost_model_factory {
public:
    boost_model_factory() = delete;
    boost_model_factory(const boost_model_factory&) = delete;
    ~boost_model_factory() = delete;
    boost_model_factory(boost_model_factory&&) = delete;
    boost_model_factory& operator=(const boost_model_factory&) = delete;

private:
    static module create_module(const std::string& name,
        std::list<std::string> module_path);
    static pod create_pod(const std::string& name, pod_types pt,
        std::list<std::string> module_path);

public:
    static model create();
};

} }

#endif
