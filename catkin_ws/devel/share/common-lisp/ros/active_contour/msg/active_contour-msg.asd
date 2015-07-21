
(cl:in-package :asdf)

(defsystem "active_contour-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "snake" :depends-on ("_package_snake"))
    (:file "_package_snake" :depends-on ("_package"))
  ))