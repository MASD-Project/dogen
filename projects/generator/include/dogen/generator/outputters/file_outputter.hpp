/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_OUTPUTTERS_FILE_OUTPUTTER_HPP
#define DOGEN_GENERATOR_OUTPUTTERS_FILE_OUTPUTTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/outputters/outputter.hpp"

namespace dogen {
namespace generator {
namespace outputters {

class file_outputter : public outputter {
public:
    file_outputter() = default;
    file_outputter(const file_outputter&) = default;
    file_outputter(file_outputter&&) = default;
    file_outputter& operator=(const file_outputter&) = default;

public:
    file_outputter(bool verbose, bool force_write);
    virtual ~file_outputter() noexcept {}

private:
    /**
     * @brief Log output to standard output.
     */
    /**@{*/
    void log_writing_file(boost::filesystem::path path) const;
    void log_wrote_file(boost::filesystem::path path) const;
    void log_created_directories(bool created,
        boost::filesystem::path directory) const;
    void log_no_content_changes() const;
    void log_content_changes() const;
    /**@}*/

private:
    bool writing_needed(outputter::value_entry_type value) const;

    /**
     * @brief Outputs the pair passed in to a file.
     */
    void to_file(outputter::value_entry_type value) const;

public:
    /**
     * @brief Name of the outputter for logging purposes
     */
    static std::string outputter_name();

    /**
     * @brief Outputs all of the generated code to files.
     */
    void output(outputter::value_type value) const override;

private:
    const bool verbose_;
    const bool force_write_;
};

} } }

#endif
