#|
 ***** Programming Assignment #4:Farmer, Wolf, Goat, Cabbage Puzzle *****
Author: Lyndon Engel
Class: CSC 461 Programming Languages
Instructor: Dr.Weiss


Description: Lisp program that uses the state space approach to solve the Farmer, 
Wolf, Goat, and Cabbage Problem.

Compilation instructions: (fwgc)


|#
;;global variables that hold the objects previous locations
(defvar *prev-farmer* nil)
(defvar *prev-wolf* nil)
(defvar *prev-goat* nil)
(defvar *prev-cabbage* nil)

; Function that starts the program and creates the header
; Also resets the global variables
(defun fwgc () (header)
               (setq *prev-farmer* 'l)
               (setq *prev-wolf* 'l)
               (setq *prev-goat* 'l)
               (setq *prev-cabbage* 'l)
               (DFS '(l l l l) '(r r r r) nil))

;Function that creates the header
(defun header () (format t "Left Bank             Right Bank     Action ~%")
                 (format t "---------             ----------     ------ ~%"))


;The DFS function runs the depth first search that finds the correct commbination
;for the fwgc problem. It does this by taking in the current location and the end
;goal location. It then takes in an empty list that used to keep track of the already
;tried moves.
(defun DFS (current-loc end-location checked)
   (cond 
    ((null current-loc) nil)
    ;;checks if the current location is equal to the end location if so it runs the last output function then ends
    ((equal current-loc  end-location) (bank-status (f-current current-loc ) (w-current current-loc ) 
     (g-current current-loc ) (c-current current-loc ) 1 current-loc))
    ;;checks to see if the current move has already been tried
    ((not (member current-loc  checked :test #'equal))
     (bank-status (f-current current-loc ) (w-current current-loc ) 
     (g-current current-loc ) (c-current current-loc ) 0 current-loc)
     ;;recurrsion statements used to find the correct move
     (or (DFS (Fleaves current-loc ) end-location (cons current-loc  checked))
         (DFS (wleaves current-loc ) end-location (cons current-loc  checked))
         (DFS (gleaves current-loc ) end-location (cons current-loc  checked))
         (DFS (cleaves current-loc ) end-location (cons current-loc  checked))
     )
    )
   )
)

;;This function checks the location of the fwgc and then places them into the 
;;correct list depending on what bank they are on. It then outputs those lists
;;in a formated order. When temp equals 1 the program will end
(defun bank-status (fs ws gs cs temp current-loc)

   (setq current-left nil)
   (setq current-right nil)
   
   (if (string= fs "L")
       (setq current-left (cons 'F current-left))
       (setq current-right (cons 'F current-right))
   )
      
   (if (string= ws "L")
       (setq current-left (cons 'W current-left))
       (setq current-right (cons 'W current-right))
   )

   (if (string= gs "L")
       (setq current-left (cons 'G current-left))
       (setq current-right (cons 'G current-right))
   )

   (if (string= cs "L")
       (setq current-left (cons 'C current-left))
       (setq current-right (cons 'C current-right))
   )

   (format t "~30<~a~;~b~>" (reverse current-left) (reverse current-right))

   (action current-loc)

    (if (= temp 1)
       (setq end "*** problem solved! ***" )
    )
)

;;this funcion checks the previous location and current location of the
;;objects and then outputs an action statement depending on who moved where
(defun action (current-loc)
  ;;does the checking of who moves
  (cond 
    ((equal *prev-farmer* (nth 0 current-loc)) (format t "       *start state* ~%"))
    ((not (equal  *prev-wolf* (nth 1 current-loc))) (format t "       Farmer takes wolf across ~%"))
    ((not (equal *prev-goat* (nth 2 current-loc))) (format t "       Farmer takes goat across ~%"))
    ((not (equal *prev-cabbage* (nth 3 current-loc))) (format t "       Farmer takes cabbage across ~%"))
    ((not (equal *prev-farmer* (nth 0 current-loc))) (format t "       Farmer returns alone ~%"))
  )
  ;;sets the global varibles to the new previous location
  (setq *prev-farmer* (nth 0 current-loc))
  (setq *prev-wolf* (nth 1 current-loc))
  (setq *prev-goat* (nth 2 current-loc))
  (setq *prev-cabbage* (nth 3 current-loc))
)


;;This function checks to see if the farmer is able to move
;;depending on the current location of the others if it is
;;nothing changes otherwise it returns nil
(defun Fleaves (current-loc )
   (valid-move (set-location  (rev (f-current current-loc ))
		(w-current current-loc )
	 	(g-current current-loc )
	 	(c-current current-loc ))
   )
)


;;This function checks to see if the cabbage is able to move
;;depending on the current location of the others if it is
;;nothing changes otherwise it returns nil
(defun cleaves (current-loc )
   (cond (
          (equal (f-current current-loc ) (c-current current-loc ))
          (valid-move (set-location  (rev (f-current current-loc ))
                            (w-current current-loc )
                            (g-current current-loc )
                            (rev (c-current current-loc )))
          )   
      
         )
         (t nil)
   )
)


;;This function checks to see if the wolf is able to move
;;depending on the current location of the others if it is
;;nothing changes otherwise it returns nil
(defun wleaves (current-loc )
   (cond (
          (equal (f-current current-loc ) (w-current current-loc ))
          (valid-move (set-location  
          (rev (f-current current-loc ))
          (rev (w-current current-loc ))
          (g-current current-loc )
          (c-current current-loc ))
          )
         )
         (t nil)
   )
)


;;This function checks to see if the goat is able to move
;;depending on the current location of the others if it is
;;nothing changes otherwise it returns nil
(defun gleaves (current-loc )
   (cond (
          (equal (f-current current-loc ) (g-current current-loc ))
          (valid-move (set-location  
          (rev (f-current current-loc ))
	  (w-current current-loc )
	  (rev (g-current current-loc ))
	  (c-current current-loc ))
          )

         ) 
         (t nil)
   )
)

;creates a sample list
(defun set-location  (f w g c) (list f w g c))

;;grabs the current location of the farmer
(defun f-current ( current-loc  )
   (nth 0 current-loc ))

;;grabs the current location of the goat
(defun g-current ( current-loc  )
   (nth 2 current-loc ))

;;grabs the current location of the cabbage
(defun c-current ( current-loc  )
   (nth 3 current-loc ))

;;grabs the current location of the wolf
(defun w-current ( current-loc  )
   (nth 1 current-loc ))

;;Checks if a move is vaild, if it is then nothing will change
;;otherwise it will return nil
(defun valid-move (current-loc )
   (cond (
          (and (equal (g-current current-loc ) (w-current current-loc ))
	  (not (equal (f-current current-loc ) (w-current current-loc ))))  nil)
          ((and (equal (g-current current-loc ) (c-current current-loc ))
          (not (equal (f-current current-loc ) (g-current current-loc )))) nil)
          (t current-loc )
   )
)
;;swaps the location where the fwgc are
(defun rev (bank)
   (cond ((equal bank 'r) 'l)
         ((equal bank 'l) 'r)
   )
)



