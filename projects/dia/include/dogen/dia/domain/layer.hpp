/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_LAYER_HPP
#define DOGEN_DIA_DOMAIN_LAYER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include "dogen/dia/domain/object.hpp"

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class layer_serializer; } }

/**
 * @brief Represents a layer in a Dia diagram
 */
class layer {
public:
    layer(const layer&) = default;
    ~layer() = default;
    layer(layer&&) = default;
    layer& operator=(const layer&) = default;

private:
    friend class dogen::dia::serialization::detail::layer_serializer;

public:
    layer() : visible_(), active_() { }
    layer(std::string name, bool visible, bool active,
        std::vector<object> objects)
        : name_(name), visible_(visible), active_(active), objects_(objects) { }

public:
    /**
     * @brief Name of the layer
     */
    /**@{*/
    std::string name() const { return(name_); }
    void name(std::string value) { name_ = value; }
    /**@}*/

    /**
     * @brief Whether the layer is visible on screen or not.
     */
    /**@{*/
    bool visible() const { return(visible_); }
    void visible(bool value) { visible_ = value; }
    /**@}*/

    /**
     * @brief Whether the layer is active or not.
     */
    /**@{*/
    bool active() const { return(active_); }
    void active(bool value) { active_ = value; }
    /**@}*/

    /**
     * @brief Dia objects contained in layer.
     */
    /**@{*/
    std::vector<object> objects() const { return(objects_); }
    void objects(std::vector<object> value) { objects_ = value; }
    /**@}*/

public:
    bool operator==(const dogen::dia::layer& value) const;

    bool operator!=(const dogen::dia::layer& value) const {
        return(!this->operator==(value));
    }

private:
    std::string name_;
    bool visible_;
    bool active_;
    std::vector<object> objects_;
};

} }

#endif
