/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_MODELING_SML_BUILDER_HPP
#define DOGEN_GENERATOR_MODELING_SML_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/sml/domain/model.hpp"

namespace dogen {
namespace generator {
namespace modeling {

class sml_builder {
public:
    sml_builder() = delete;
    sml_builder(const sml_builder&) = default;
    ~sml_builder() = default;
    sml_builder(sml_builder&&) = default;
    sml_builder& operator=(const sml_builder&) = default;

public:
    sml_builder(bool verbose, std::string schema_name);

private:
    std::vector<sml::property>
    resolve_properties(sml::pod pod);
    void resolve_parent(sml::pod pod);
    void resolve();
    void merge();

public:
    void add_target(sml::model model);
    void add(sml::model model);
    sml::model build();

private:
    std::string name_;
    std::list<sml::model> models_;
    sml::model merged_model_;
    const bool verbose_;
    bool has_target_;
    std::list<std::string> external_package_path_;
    const std::string schema_name_;
};

} } }

#endif
