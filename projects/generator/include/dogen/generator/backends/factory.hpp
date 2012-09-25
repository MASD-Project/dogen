/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_FACTORY_HPP
#define DOGEN_GENERATOR_BACKENDS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/generator/config/settings.hpp"
#include "dogen/generator/backends/backend.hpp"
#include "dogen/sml/domain/model.hpp"

namespace dogen {
namespace generator {
namespace backends {

class factory {
public:
    factory() = delete;
    factory(const factory&) = default;
    ~factory() = default;
    factory(factory&&) = default;
    factory& operator=(const factory&) = default;

public:
    typedef std::vector<backend::ptr> production_type;

public:
    factory(sml::model model, config::settings settings)
        : settings_(settings), model_(model) { }

private:
    void log_cpp_backend_disabled() const;

public:
    production_type create() const;

private:
    const config::settings settings_;
    const sml::model model_;
};

} } }

#endif
