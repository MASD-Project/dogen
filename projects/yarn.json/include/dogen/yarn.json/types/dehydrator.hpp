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
#ifndef DOGEN_YARN_JSON_TYPES_DEHYDRATOR_HPP
#define DOGEN_YARN_JSON_TYPES_DEHYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <ostream>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>
#include "dogen/annotations/types/scribble.hpp"
#include "dogen/yarn/types/meta_model/exomodel.hpp"

namespace dogen {
namespace yarn {
namespace json {

class dehydrator final {
private:
    static std::string tidy_up_string(std::string s);
    static bool has_elements(const meta_model::exomodel& em);

private:
    static boost::optional<annotations::scribble_group> scribble_group_for_name(
        const meta_model::exomodel& em,
        const meta_model::name& n);
    static boost::optional<annotations::scribble>
    scribble_for_name(const boost::optional<annotations::scribble_group>& sg,
        const meta_model::name& n);
    static void dehydrate_name(
        const meta_model::name& n, std::ostream& s);
    static void dehydrate_names(const std::list<meta_model::name>& names,
        std::ostream& s);
    static void dehydrate_annotations(
        const boost::optional<annotations::scribble>& scribble,
        std::ostream& s);
    static void dehydrate_element(
        const boost::optional<annotations::scribble_group>& sg,
        const meta_model::element& e, std::ostream& s);
    static void dehydrate_attributes(
        const boost::optional<annotations::scribble_group>& sg,
        const std::list<meta_model::attribute>& attrs, std::ostream& s);
    static void dehydrate_objects(const bool requires_leading_comma,
        const meta_model::exomodel& em, std::ostream& s);
    static void dehydrate_object_templates(const bool requires_leading_comma,
        const meta_model::exomodel& em, std::ostream& s);
    static void dehydrate_modules(const bool requires_leading_comma,
        const meta_model::exomodel& em, std::ostream& s);
    static void dehydrate_enumerations(const bool requires_leading_comma,
        const meta_model::exomodel& em, std::ostream& s);
    static void dehydrate_primitives(const bool requires_leading_comma,
        const meta_model::exomodel& em, std::ostream& s);
    static void dehydrate_exceptions(const bool requires_leading_comma,
        const meta_model::exomodel& em, std::ostream& s);

public:
    static std::string dehydrate(const meta_model::exomodel& em);
    static void dehydrate(const meta_model::exomodel& em,
        const boost::filesystem::path& p);
};

} } }

#endif
