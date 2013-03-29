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
#ifndef DOGEN_GENERATOR_OUTPUTTERS_OUTPUTTER_FACTORY_HPP
#define DOGEN_GENERATOR_OUTPUTTERS_OUTPUTTER_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <functional>
#include "dogen/config/types/output_settings.hpp"
#include "dogen/engine/outputters/outputter.hpp"

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
