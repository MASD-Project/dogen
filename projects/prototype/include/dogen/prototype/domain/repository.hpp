/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_PROTOTYPE_DOMAIN_REPOSITORY_HPP
#define DOGEN_PROTOTYPE_DOMAIN_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen/prototype/domain/currency.hpp"
#include "dogen/prototype/hash/unversioned_key_hash.hpp"
#include "dogen/prototype/hash/currency_hash.hpp"

namespace dogen {
namespace prototype {

class repository_serializer;

/**
 * @brief Repository of the object model.
 */
class repository {
private:
    friend class repository_serializer;

public:
    typedef std::unordered_map<unversioned_key, currency> currency_map;
    typedef boost::shared_ptr<currency_map> currency_map_ptr;

public:
    typedef std::vector<currency> currency_vector;

public:
    repository() { }

public:
    boost::optional<currency> get_currency(unversioned_key uk) const {
        currency_map_ptr currencies(currencies_);
        const auto i(currencies->find(uk));

        boost::optional<currency> currency;
        if (i != currencies->end()) {
            currency = i->second;
        }
        return(currency);
    }

    void update_currencies(currency_vector changes) {
        currency_map_ptr
            new_state(currencies_ ?
                      currency_map_ptr(new currency_map(*currencies_)) :
                      currency_map_ptr(new currency_map));

        for (auto c : changes) {
            const auto uv(static_cast<unversioned_key>(c.versioned_key()));
            (*new_state)[uv] = c;
        }
        currencies_.swap(new_state);
    }

    currency_map currencies() const {
        if (!currencies_.get()) {
            return (currency_map());
        } else {
            return (*currencies_.get());
        }
    }

public:
    bool operator==(const repository& rhs) const {
        return (*currencies_ == rhs.currencies());
    }

private:
    currency_map_ptr currencies_;
};

} }

#endif
