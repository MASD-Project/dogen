/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/backends/cpp/cpp_backend.hpp"
#include "dogen/generator/backends/factory.hpp"
#include "dogen/utility/log/logger.hpp"

static dogen::utility::log::logger
lg(dogen::utility::log::logger_factory("backends::factory"));

namespace dogen {
namespace generator {
namespace backends {

void factory::log_cpp_backend_disabled() const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, info) << "C++ backend is disabled, skipping it.";
}

factory::production_type factory::create() const {
    production_type r;

    if (settings_.cpp().disable_backend())
        log_cpp_backend_disabled();
    else
        r.push_back(cpp::cpp_backend::create(model_, settings_.cpp())) ;

    return r;
}

} } }
