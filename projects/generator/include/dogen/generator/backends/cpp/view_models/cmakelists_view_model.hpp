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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_CMAKELISTS_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_CMAKELISTS_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class cmakelists_view_model {
public:
    cmakelists_view_model() = default;
    cmakelists_view_model(const cmakelists_view_model&) = default;
    ~cmakelists_view_model() = default;
    cmakelists_view_model(cmakelists_view_model&&) = default;
    cmakelists_view_model& operator=(const cmakelists_view_model&) = default;

public:
    cmakelists_view_model(boost::filesystem::path file_path,
        std::string model_name) :
        file_path_(file_path), model_name_(model_name) {}

public:
    std::string model_name() const { return(model_name_); }
    void model_name(const std::string& value) { model_name_ = value; }

    void file_path(boost::filesystem::path value) { file_path_ = value; }
    boost::filesystem::path file_path() const { return file_path_; }

    std::string file_name() const;

private:
    boost::filesystem::path file_path_;
    std::string model_name_;
};

} } } } }

#endif
