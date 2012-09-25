/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_BACKEND_HPP
#define DOGEN_GENERATOR_BACKENDS_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <ostream>
#include <memory>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace generator {
namespace backends {

class backend {
public:
    backend(const backend&) = default;
    virtual ~backend() noexcept = default;
    backend(backend&&) = default;
    backend& operator=(const backend&) = default;

protected:
    backend() = default;

public:
    typedef std::shared_ptr<backend> ptr;
    typedef std::map<boost::filesystem::path, std::string> value_type;
    typedef std::pair<boost::filesystem::path, std::string> value_entry_type;

public:
    /**
     * @brief Generate code for this backend.
     */
    virtual value_type generate() = 0;

    /**
     * @brief Get all directories managed by this backend.
     */
    virtual std::vector<boost::filesystem::path> managed_directories() const = 0;
};

} } }

#endif
