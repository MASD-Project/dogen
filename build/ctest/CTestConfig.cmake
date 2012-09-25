# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#

# set the site to the hostname. this shows up in the dashboard.
site_name(DOGEN_SITE)
set(SITE "${DOGEN_SITE}")
set(CTEST_SITE "${DOGEN_SITE}")

# project name
set(CTEST_PROJECT_NAME "dogen")

# kitware dashboard settings
set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "kitanda.linkpc.net/cdash")
set(CTEST_DROP_LOCATION "/submit.php?project=Dogen")
set(CTEST_DROP_SITE_CDASH TRUE)
