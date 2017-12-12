;;; poly-stitch.el
;;
;; Filename: poly-stitch.el
;; Author: Marco Craveiro
;; Maintainer: Marco Craveiro
;; Copyright (C) 2017, Marco Craveiro, all rights reserved.
;; Version: 0.1
;; URL: https://github.com/DomainDrivenConsulting/dogen
;; Keywords: emacs dogen
;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; This file is *NOT* part of GNU Emacs.
;;
;; This program is free software; you can redistribute it and/or
;; modify it under the terms of the GNU General Public License as
;; published by the Free Software Foundation; either version 3, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;; General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; see the file COPYING.  If not, write to
;; the Free Software Foundation, Inc., 51 Franklin Street, Fifth
;; Floor, Boston, MA 02110-1301, USA.
;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(require 'polymode)

(defcustom pm-inner/stitch-standard-control-block
  (pm-hbtchunkmode "c++" :mode 'c++-mode
                   :head-reg "<#\\+"
                   :tail-reg "#>"
                   :font-lock-narrow t)
  "Template code."
  :group 'innermodes
  :type 'object)

(defcustom pm-inner/stitch-directive
  (pm-hbtchunkmode "conf" :mode 'conf-unix-mode
                   :head-reg "<#@"
                   :tail-reg "#>"
                   :font-lock-narrow t)
  "Template code."
  :group 'innermodes
  :type 'object)

(defcustom pm-inner/stitch-expansion-block
  (pm-hbtchunkmode "conf" :mode 'conf-unix-mode
                   :head-reg "<#\\$"
                   :tail-reg "#>"
                   :font-lock-narrow t)
  "Template code."
  :group 'innermodes
  :type 'object)

(defcustom pm-inner/stitch-expression-control-block
  (pm-hbtchunkmode "c++" :mode 'c++-mode
                   :head-reg "<#="
                   :tail-reg "#>"
                   :font-lock-narrow t)
  "Template code."
  :group 'innermodes
  :type 'object)

(defcustom pm-poly/stitch
  (pm-polymode-multi "stitch"
                     :hostmode 'pm-host/fundamental
                     :innermodes '(pm-inner/stitch-standard-control-block
                                   pm-inner/stitch-directive
                                   pm-inner/stitch-expression-control-block
                                   pm-inner/stitch-expansion-block))
  "Stitch typical polymode."
  :group 'polymodes
  :type 'object)

(defcustom pm-weaver/stitcher
  (pm-shell-weaver "stitcher"
                   :from-to
                   '(("stitch" "\\.\\(stitch\\|cpp\\)\\'" "stitch" "C++" "dogen.stitcher --target %i --log-directory /tmp")))
  "Dogen stitcher weaver."
  :group 'polymode-weave
  :type 'object)

(polymode-register-weaver pm-weaver/stitcher nil pm-poly/stitch)

(define-polymode poly-stitch-mode pm-poly/stitch)

;; (add-to-list 'auto-mode-alist '("\\.stitch" . poly-stitch-mode))
