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
#ifndef DOGEN_CLI_TYPES_APPLICATION_HPP
#define DOGEN_CLI_TYPES_APPLICATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <ostream>
#include "dogen/types/converter.hpp"
#include "dogen/types/generator.hpp"
#include "dogen/types/spec_dumper.hpp"
#include "dogen.cli/types/configuration.hpp"

namespace dogen::cli {

/**
 * Entry point for the dogen command line application.
 */
class application final {
public:
    application() = delete;
    application(const application&) = delete;
    application(application&&) = delete;
    ~application() = default;
    application& operator=(const application&) = delete;

public:
    application(const converter& c, const generator& g, const spec_dumper& sd);

public:
    /**
     * Executes the application.
     *
     * @param cfg Application configuration.
     */
    void run(const configuration& cfg) const;

private:
    const converter& converter_;
    const generator& generator_;
    const spec_dumper& dumper_;
};

}

#endif
