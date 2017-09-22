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
#ifndef DOGEN_YARN_TYPES_META_MODEL_INTRA_KERNEL_SEGMENT_PROPERTIES_HPP
#define DOGEN_YARN_TYPES_META_MODEL_INTRA_KERNEL_SEGMENT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/meta_model/path_contribution_types.hpp"
#include "dogen/yarn/serialization/meta_model/intra_kernel_segment_properties_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

class intra_kernel_segment_properties final {
public:
    intra_kernel_segment_properties(const intra_kernel_segment_properties&) = default;
    ~intra_kernel_segment_properties() = default;

public:
    intra_kernel_segment_properties();

public:
    intra_kernel_segment_properties(intra_kernel_segment_properties&& rhs);

public:
    intra_kernel_segment_properties(
        const boost::filesystem::path& override_parent_path,
        const boost::filesystem::path& path_segment,
        const dogen::yarn::meta_model::path_contribution_types external_modules,
        const dogen::yarn::meta_model::path_contribution_types model_modules,
        const dogen::yarn::meta_model::path_contribution_types internal_modules,
        const dogen::yarn::meta_model::path_contribution_types facet);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::intra_kernel_segment_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::intra_kernel_segment_properties& v, unsigned int version);

public:
    /**
     * @brief If supplied, this path is used as the parent path instead of the output path.
     *
     * This is useful for example when you want to place the include files outside of the
     * model directory.
     */
    /**@{*/
    const boost::filesystem::path& override_parent_path() const;
    boost::filesystem::path& override_parent_path();
    void override_parent_path(const boost::filesystem::path& v);
    void override_parent_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Path segment to use for this intra-kernel segment.
     */
    /**@{*/
    const boost::filesystem::path& path_segment() const;
    boost::filesystem::path& path_segment();
    void path_segment(const boost::filesystem::path& v);
    void path_segment(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief What kind of contribution do the external modules make to the final path.
     */
    /**@{*/
    dogen::yarn::meta_model::path_contribution_types external_modules() const;
    void external_modules(const dogen::yarn::meta_model::path_contribution_types v);
    /**@}*/

    /**
     * @brief What kind of contribution do the model modules make to the final path.
     */
    /**@{*/
    dogen::yarn::meta_model::path_contribution_types model_modules() const;
    void model_modules(const dogen::yarn::meta_model::path_contribution_types v);
    /**@}*/

    /**
     * @brief What kind of contribution do the internal modules make to the final path.
     */
    /**@{*/
    dogen::yarn::meta_model::path_contribution_types internal_modules() const;
    void internal_modules(const dogen::yarn::meta_model::path_contribution_types v);
    /**@}*/

    /**
     * @brief What kind of contribution does the facet make to the final path.
     */
    /**@{*/
    dogen::yarn::meta_model::path_contribution_types facet() const;
    void facet(const dogen::yarn::meta_model::path_contribution_types v);
    /**@}*/

public:
    bool operator==(const intra_kernel_segment_properties& rhs) const;
    bool operator!=(const intra_kernel_segment_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(intra_kernel_segment_properties& other) noexcept;
    intra_kernel_segment_properties& operator=(intra_kernel_segment_properties other);

private:
    boost::filesystem::path override_parent_path_;
    boost::filesystem::path path_segment_;
    dogen::yarn::meta_model::path_contribution_types external_modules_;
    dogen::yarn::meta_model::path_contribution_types model_modules_;
    dogen::yarn::meta_model::path_contribution_types internal_modules_;
    dogen::yarn::meta_model::path_contribution_types facet_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::intra_kernel_segment_properties& lhs,
    dogen::yarn::meta_model::intra_kernel_segment_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
