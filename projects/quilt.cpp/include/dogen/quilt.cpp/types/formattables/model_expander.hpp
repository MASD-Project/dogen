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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_MODEL_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_MODEL_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/repository.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class model_expander {
private:
    void expand_streaming(const annotations::repository& arp, model& fm) const;

    void expand_profile_groups(
        const std::forward_list<boost::filesystem::path>& dirs,
        const annotations::repository& arp, const annotations::annotation& root,
        const formatters::container& fc, model& fm) const;

    void expand_enablement(const annotations::repository& arp,
        const annotations::annotation& root, const formatters::container& fc,
        model& fm) const;

    void expand_canonical_formatters(const formatters::container& fc,
        model& fm) const;

    void expand_inclusion(
        const annotations::repository& arp, const formatters::container& fc,
        const locator& l, model& fm) const;

    void expand_decoration(
        const dogen::formatters::decoration_properties_factory& dpf,
        model& fm) const;

    void expand_aspects(const annotations::repository& arp, model& fm) const;

    void expand_helpers(const annotations::repository& arp,
        const formatters::container& fc, model& fm) const;

    void reduce(model& fm) const;

    void expand_file_paths_and_guards(const formatters::container& fc,
        const locator& l, model& fm) const;

    void expand_odb(const annotations::repository& arp, model& fm) const;

    void expand_facet_directories(const locator& l, model& fm) const;

public:
    void expand(const std::forward_list<boost::filesystem::path>& dirs,
        const annotations::repository& arp, const annotations::annotation& root,
        const dogen::formatters::decoration_properties_factory& dpf,
        const formatters::container& fc, const locator& l, model& fm) const;
};

} } } }

#endif
