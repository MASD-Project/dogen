/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_CMAKELISTS_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_CMAKELISTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/backends/cpp/view_models/cmakelists_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_cmakelists {
public:
    cpp_cmakelists() = delete;
    cpp_cmakelists(const cpp_cmakelists&) = default;
    ~cpp_cmakelists() noexcept = default;
    cpp_cmakelists(cpp_cmakelists&&) = default;
    cpp_cmakelists& operator=(const cpp_cmakelists&) = default;

public:
    explicit cpp_cmakelists(std::ostream& stream);

public:
    void format(view_models::cmakelists_view_model vm);

private:
    std::ostream& stream_;
};

} } } } }

#endif
