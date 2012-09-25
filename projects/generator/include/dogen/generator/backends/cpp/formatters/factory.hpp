/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_FACTORY_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/generator/config/cpp_settings.hpp"
#include "dogen/generator/backends/cpp/formatters/file_formatter.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class factory {
public:
    factory() = delete;
    factory(const factory&) = default;
    ~factory() = default;
    factory(factory&&) = default;
    factory& operator=(const factory&) = default;

public:
    typedef file_formatter::shared_ptr production_type;

public:
    factory(config::cpp_settings settings, bool disable_io)
        : settings_(settings), disable_io_(disable_io) { }

public:
    production_type
    create(std::ostream& stream, cpp_facet_types facet_type) const;

    production_type create(std::ostream& stream, cpp_facet_types facet_type,
        cpp_file_types file_type) const;

private:
    const config::cpp_settings settings_;
    const bool disable_io_;
};

} } } } }

#endif
