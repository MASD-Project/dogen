/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <utility>
#include <unordered_map>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/repository.hpp"
#include "dogen/options/types/cpp_options.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class workflow {
private:
    /**
     * @brief Retrieves the ids of all the modules in the model.
     */
    std::unordered_set<std::string>
    obtain_module_ids(const yarn::model& m) const;

    model
    make_model(const formatters::container& fc, const yarn::model& m) const;

    void expand_model(
        const std::forward_list<boost::filesystem::path>& data_directories,
        const annotations::repository& drp, const annotations::annotation& root,
        const dogen::formatters::decoration_properties_factory& dpf,
        const formatters::container& fc, const locator& l, model& fm) const;

public:
    model execute(
        const std::forward_list<boost::filesystem::path>& data_directories,
        const options::cpp_options& opts,
        const annotations::repository& drp, const annotations::annotation& root,
        const dogen::formatters::decoration_properties_factory& dpf,
        const formatters::container& fc, const yarn::model& m) const;
};

} } } }

#endif
