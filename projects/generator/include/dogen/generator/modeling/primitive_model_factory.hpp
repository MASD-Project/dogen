/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_MODELING_PRIMITIVE_MODEL_FACTORY_HPP
#define DOGEN_GENERATOR_MODELING_PRIMITIVE_MODEL_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/sml/domain/model.hpp"

namespace dogen {
namespace generator {
namespace modeling {

class primitive_model_factory {
public:
    primitive_model_factory() = delete;
    primitive_model_factory(const primitive_model_factory&) = delete;
    ~primitive_model_factory() = delete;
    primitive_model_factory(primitive_model_factory&&) = delete;
    primitive_model_factory& operator=(const primitive_model_factory&) = delete;

private:
    static sml::primitive create(std::string name);

public:
    static sml::model create();
};

} } }

#endif
