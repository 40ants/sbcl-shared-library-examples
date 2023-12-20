(in-package :cl-user)


;; (require '#:asdf)

(load "~/quicklisp/setup.lisp")

(ql:quickload "slynk")

;; To make SLY contribs awailable:
(loop for file in (directory
		    (merge-pathnames
		      (make-pathname :name :wild :type "lisp")
		      (asdf:system-relative-pathname "slynk" "../contrib/")))
		    ;;(make-pathname :directory '(:relative ".." ".." "bundle" "sly" "contrib")
;; 					    :name :wild
 ;;					    :type "lisp"))
       do (load file))


;; Example of additional library:
(ql:quickload "dexador")


(sb-alien:define-alien-callable hello-world sb-alien:int ((name sb-alien:c-string))
  (format t "Hello World, ~A!~%" name)
  0)


(sb-alien:define-alien-callable start-slynk sb-alien:void ((port sb-alien:int))
  (format t "Starting Slynk on port ~A!~%" port)
  (slynk:create-server :port port
		       :interface "0.0.0.0"
		       :dont-close t)
  (loop do (format t "Waiting for connection~%")
	(sleep 10))
  (values))


(sb-ext:save-lisp-and-die "libhello.core"
		    :compression
		    #+sb-core-compression t
		    #-sb-core-compression nil
		    :callable-exports (list 'hello-world
					    'start-slynk))
