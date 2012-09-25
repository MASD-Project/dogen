/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
