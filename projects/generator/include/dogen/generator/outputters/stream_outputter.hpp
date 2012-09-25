/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_OUTPUTTERS_STREAM_OUTPUTTER_HPP
#define DOGEN_GENERATOR_OUTPUTTERS_STREAM_OUTPUTTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <ostream>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/outputters/outputter.hpp"

namespace dogen {
namespace generator {
namespace outputters {

class stream_outputter : public outputter {
public:
    stream_outputter() = default;
    stream_outputter(const stream_outputter&) = default;
    stream_outputter(stream_outputter&&) = default;
    stream_outputter& operator=(const stream_outputter&) = default;

public:
    stream_outputter(std::ostream& stream);
    virtual ~stream_outputter() noexcept {}

public:
    /**
     * @brief Name of the outputter for logging purposes
     */
    static std::string outputter_name();

    void output(outputter::value_type value) const override;

private:
    std::ostream& stream_;
};

} } }

#endif
