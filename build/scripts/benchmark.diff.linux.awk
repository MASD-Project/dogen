# -*- mode: awk; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#

function print_array(v) {
     size = length(v);
     for (i = 0; i < size; i++) {
          print v[i];
     }
}

function average(v) {
     size = length(v);
     avg = 0;
     for (i = 0; i < size; i++) {
          avg = avg + v[i];
     }
     avg = avg / size;
     return avg;
}

function std_dev(v, avg) {
     size = length(v);
     dev = 0;
     for (i = 0; i < size; i++) {
          dev = avg - v[i];
          dev = dev * dev;
     }
     dev = dev / size;
     dev = sqrt(dev);
     return dev;
}

function stats(global_label, label, lhs, rhs) {
     lhs_avg = average(lhs);
     rhs_avg = average(rhs);
     delta_pct_avg = rhs_avg - lhs_avg;
     if (lhs_avg != 0)
          delta_pct_avg = (delta_pct_avg / lhs_avg) * 100;

     lhs_dev = std_dev(lhs);
     rhs_dev = std_dev(rhs);
     delta_pct_dev = rhs_dev - lhs_dev;
     if (lhs_dev != 0)
          delta_pct_dev = (delta_pct_dev / lhs_dev) * 100;

     print global_label ", " label ", " delta_pct_avg "%, " lhs_avg ", " rhs_avg ", " delta_pct_dev "%, " lhs_dev ", " rhs_dev;
}

BEGIN {
     FS = ",";
     rhs = 0;
     global_label = ARGV[1];
     delete ARGV[1]
}

FNR >= 2 {
     if (FNR != NR) {
          rhs = 1;
     }

     idx = FNR - 2;
     if (rhs == 0) {
          elapsed_real_time_lhs[idx] = $1;
          filesystem_inputs_lhs[idx] = $2;
          filesystem_outputs_lhs[idx] = $3;
          max_rss_lhs[idx] = $4;
          avg_rss_lhs[idx] = $5;
          avg_total_memory_lhs[idx] = $6;
          avg_unshared_memory_lhs[idx] = $7;
          avg_shared_memory_lhs[idx] = $8;
          total_page_faults_lhs[idx] = $9;
          total_soft_page_faults_lhs[idx] = $10;
     } else {
          elapsed_real_time_rhs[idx] = $1;
          filesystem_inputs_rhs[idx] = $2;
          filesystem_outputs_rhs[idx] = $3;
          max_rss_rhs[idx] = $4;
          avg_rss_rhs[idx] = $5;
          avg_total_memory_rhs[idx] = $6;
          avg_unshared_memory_rhs[idx] = $7;
          avg_shared_memory_rhs[idx] = $8;
          total_page_faults_rhs[idx] = $9;
          total_soft_page_faults_rhs[idx] = $10;
     }
}

END {
     # print_array(elapsed_real_time_lhs);
     # print_array(elapsed_real_time_rhs);

     stats(global_label, "elapsed_real_time", elapsed_real_time_lhs, elapsed_real_time_rhs);
     stats(global_label, "filesystem_inputs", filesystem_inputs_lhs, filesystem_inputs_rhs);
     stats(global_label, "filesystem_outputs", filesystem_outputs_lhs, filesystem_outputs_rhs);
     stats(global_label, "max_rss", max_rss_lhs, max_rss_rhs);
     stats(global_label, "avg_rss", avg_rss_lhs, avg_rss_rhs);
     stats(global_label, "avg_unshared_memory", avg_unshared_memory_lhs, avg_unshared_memory_rhs)
     stats(global_label, "avg_shared_memory", avg_shared_memory_lhs, avg_shared_memory_rhs);
     stats(global_label, "avg_total_memory", avg_total_memory_lhs, avg_total_memory_rhs)
     stats(global_label, "total_page_faults", total_page_faults_lhs, total_page_faults_rhs);
     stats(global_label, "total_soft_page_faults", total_soft_page_faults_lhs, total_soft_page_faults_rhs);
}
