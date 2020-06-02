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

(define-hostmode poly-stitch-hostmode :mode 'fundamental-mode)

(define-innermode poly-stitch-directive-innermode
  :mode 'fundamental-mode
  :head-matcher "<#@"
  :tail-matcher "#>"
  :head-mode 'host
  :tail-mode 'host)

(define-innermode poly-stitch-expansion-block-innermode
  :mode 'fundamental-mode
  :head-matcher "<#\\$"
  :tail-matcher "#>"
  :head-mode 'host
  :tail-mode 'host)

(define-innermode poly-stitch-big-block-innermode
  :mode 'c++-mode
  :head-matcher "<#\\+"
  :tail-matcher "#>"
  :head-mode 'host
  :tail-mode 'host)

(define-innermode poly-stitch-expression-control-block-innermode
  :mode 'c++-mode
  :head-matcher "<#="
  :tail-matcher "#>"
  :head-mode 'host
  :tail-mode 'host)

(define-polymode stitch-mode
  :hostmode 'poly-stitch-hostmode
  :innermodes '(poly-stitch-directive-innermode
                poly-stitch-expansion-block-innermode
                poly-stitch-big-block-innermode
                poly-stitch-expression-control-block-innermode))

;; (add-to-list 'auto-mode-alist '("\\.stitch" . stitch-mode))
