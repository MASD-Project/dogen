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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_KNIT_TYPES_BACKENDS_CPP_BACKEND_HPP
#define DOGEN_KNIT_TYPES_BACKENDS_CPP_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <utility>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/model.hpp"
#include "dogen/cpp_formatters/types/workflow.hpp"
#include "dogen/sml_to_cpp/types/workflow.hpp"
#include "dogen/knit/types/backends/backend.hpp"
#include "dogen/backend/types/workflow.hpp" // FIXME

namespace dogen {
namespace knit {
namespace backends {

class cpp_backend : public backend {
public:
    cpp_backend() = delete;
    cpp_backend(const cpp_backend&) = default;
    cpp_backend(cpp_backend&&) = default;
    cpp_backend& operator=(const cpp_backend&) = default;

public:
    cpp_backend(const sml::model& model, const config::knitting_options& o);
    virtual ~cpp_backend() noexcept {}

public:
    static backend::ptr
    create(const sml::model& model, const config::knitting_options& o);

public:
    backend::value_type generate() override;
    std::forward_list<boost::filesystem::path>
    managed_directories() const override;

private:
    sml_to_cpp::workflow transformer_;
    cpp_formatters::workflow formatter_;
    const sml::model& model_; // FIXME
    dogen::backend::workflow backend_workflow_; // FIXME
};

} } }

#endif
