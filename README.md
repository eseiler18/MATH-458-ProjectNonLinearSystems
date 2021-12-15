# MATH-458 - Programming Concepts in Scientific Computing

Project of the PSCS course at EPFL given at EPFL Fall 2021. 

## Team members

- Emilien Seiler
- Louis Le Guillouzic

## Project 3: Non-linear systems

Implementation of numerical methods for the solution of nonlinear equations.  
For a function f , find x such that : _f (x) = 0_

Mandatory: consider a scalar nonlinear problem and implement the
bisection, aitken, chord, newton and fixed point methods.

Optional: Extension to systems of nonlinear equations solved by the Newton and/or
modified Newton method.

## Sources

Sources: [here](https://onlinelibrary.wiley.com/doi/pdf/10.1002/9781118673515.app8) for the Newton’s, chord and bisection method, and [here](https://mat.iitm.ac.in/home/sryedida/public_html/caimna/transcendental/iteration%20methods/fixed-point/iteration.html) for
the fixed point method. [Here](https://en.wikipedia.org/wiki/Aitken%27s_delta-squared_process) for the Aitken acceleration to be applied to
these methods.

# How to use ... (LOUIS)
To make this project, you need to have the linux tool "cmake".
Go to the root of the git after cloning :
  	```
	cd  MATH-458-ProjectNonLinearSystems
	```
	
In order to compile it you should first install *googletest* and *eigen*.
You can run this line of code to place them in their respectif place.
	
	git submodule update --init 
	
  Then, building is done as usual, in the terminal:
	
	mkdir build
	cd build
	cmake ..
	make
	
 The Build is complet ! You can in a first time Run the Test to tcheck if everything is ok !
 	
	cd google_test
	./Google_Tests_run
	
 Normally, you should pass the 17 Test. They tcheck all the functionnality of your project. We will detay more about them below.
 We can know test the default main, to compute some function. We just need to go to the project repository :

  	
	cd ..
	cd projet
	
To better understand this project, take a look on "data.csv" file. 
(Important : the semicolon separator must be desactived, but the coma separator must be actived)
If you have "gopen" on linux you can use :
  	```
	gopen data.csv
	```
	
If you are a looser on windows like Emilien, you can go to your file and open data.csv in "MATH-458-ProjectNonLinearSystems/build/project" folder. You will see the different exemple of function our project can handle, and the parameters you can input. Now lauch the main with no argument : it will take the "data.csv" file in input by default :
	
	./main_louis

Look the Answer on the terminal :<br/>
-First the warnings : They tell missing or incoherent element in the csv <br/>
-Next the solutions find by the method. Note that the first column in the csv indicate the method you want to use, so it's normal that some function are resolved by only one method.
	
## Test your function : how to fill the csv
### first column : Choose your method 
empty -> All the method <br/>
n for newton; b for Bisection; c for Classic Chord; f for Fixed Point method <br/>
Note that the letter must be separated by a semicolon ";"
### 2nd column : Choose the function 
 #### First option (simple function)  :
 Write the function in the column. Use x as variable. You can use ^ for power. You can use external function
 	exp(..) log(..) sqrt(..) cos(..) sin(..) tan(..) atan(..)


# Implementation (EMILIEN)
## Reader
## Solver
# Validating Test ... (LOUIS)
# Limitation Perspective (EMILIEN)
