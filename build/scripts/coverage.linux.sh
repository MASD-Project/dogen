#!/bin/bash
#
# Copyright (C) 2012-2016 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be  useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#
stage_dir="$1";
kcov_path="$2";

#
# Note that this script has a bit of a weird logic: we want to submit
# to coveralls or to codecov, but not to both at the same time. This
# is because our nightly builds include generated tests and thus
# provide a different "kind" of coverage. The regular CI builds only
# have manually crafted tests, checking for the domain. Both of these
# numbers are useful but must be interpreted in isolation.
#
coveralls_id="$3";
if [ -z "$coveralls_id" ]
then
    coveralls_args=""
else
    coveralls_args="--coveralls-id=${coveralls_id}"
fi

patterns="--exclude-pattern=/tests/ --include-pattern=/projects/"
tests="`'ls' ${stage_dir}/bin/*tests`";
for t in ${tests}; do
    ${kcov_path} ${patterns} ${coveralls_args} ${stage_dir}/coverage ${t};
    if [ $? -eq 0 ]
    then
        echo "Created coverage for: $t"
    else
        echo "Error whilst creating coverage for: $t" >&2
    fi
done;

#
# Submit to codecov if we didn't already submit to coveralls.
#
if [ -z "$coveralls_id" ]
then
    bash <(curl -s https://codecov.io/bash) -s ${stage_dir}/coverage;
fi
