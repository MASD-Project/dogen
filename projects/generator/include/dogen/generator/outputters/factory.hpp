/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_OUTPUTTERS_OUTPUTTER_FACTORY_HPP
#define DOGEN_GENERATOR_OUTPUTTERS_OUTPUTTER_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <functional>
#include "dogen/generator/config/output_settings.hpp"
#include "dogen/generator/outputters/outputter.hpp"

namespace dogen {
namespace generator {
namespace outputters {

class factory {
public:
    factory() = delete;
    factory(const factory&) = default;
    ~factory() = default;
    factory(factory&&) = default;
    factory& operator=(const factory&) = default;

public:
    typedef std::function<std::ostream& ()> function_type;
    typedef std::vector<outputter::ptr> production_type;

private:
    void log_output_disabled(std::string name) const;

public:
    factory(config::output_settings settings, function_type stream_fn)
        : settings_(settings), stream_fn_(stream_fn) { }

public:
    production_type create() const;

private:
    const config::output_settings settings_;
    const function_type stream_fn_;
};

} } }

#endif
