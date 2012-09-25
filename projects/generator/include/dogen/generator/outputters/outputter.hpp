/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_OUTPUTTERS_OUTPUTTER_HPP
#define DOGEN_GENERATOR_OUTPUTTERS_OUTPUTTER_HPP

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
namespace outputters {

class outputter {
public:
    outputter(const outputter&) = default;
    outputter(outputter&&) = default;
    outputter& operator=(const outputter&) = default;
    virtual ~outputter() = default;

protected:
    outputter() = default;

public:
    typedef std::shared_ptr<outputter> ptr;
    typedef std::map<boost::filesystem::path, std::string> value_type;
    typedef std::pair<boost::filesystem::path, std::string> value_entry_type;

public:
    /**
     * @brief Write input to output medium.
     */
    virtual void output(value_type value) const = 0;
};

} } }

#endif
