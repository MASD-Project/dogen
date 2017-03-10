#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/test_models/lam_model/serialization/builtins_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::test_models::lam_model::builtins& v,
    const unsigned int /*version*/) {
    ar << make_nvp("prop_0", v.prop_0_);
    ar << make_nvp("prop_1", v.prop_1_);
    ar << make_nvp("prop_2", v.prop_2_);
    ar << make_nvp("prop_3", v.prop_3_);
    ar << make_nvp("prop_4", v.prop_4_);
    ar << make_nvp("prop_5", v.prop_5_);
    ar << make_nvp("prop_6", v.prop_6_);
    ar << make_nvp("prop_7", v.prop_7_);
    ar << make_nvp("prop_8", v.prop_8_);
    ar << make_nvp("prop_9", v.prop_9_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::test_models::lam_model::builtins& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("prop_0", v.prop_0_);
    ar >> make_nvp("prop_1", v.prop_1_);
    ar >> make_nvp("prop_2", v.prop_2_);
    ar >> make_nvp("prop_3", v.prop_3_);
    ar >> make_nvp("prop_4", v.prop_4_);
    ar >> make_nvp("prop_5", v.prop_5_);
    ar >> make_nvp("prop_6", v.prop_6_);
    ar >> make_nvp("prop_7", v.prop_7_);
    ar >> make_nvp("prop_8", v.prop_8_);
    ar >> make_nvp("prop_9", v.prop_9_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::test_models::lam_model::builtins& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::test_models::lam_model::builtins& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::test_models::lam_model::builtins& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::test_models::lam_model::builtins& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::test_models::lam_model::builtins& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::test_models::lam_model::builtins& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::test_models::lam_model::builtins& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::test_models::lam_model::builtins& v, unsigned int version);

} }
